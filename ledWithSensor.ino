 #define WAIT_TIME 500 // 측정주기 1초
#define DISTANCE 10 // 초음파 거리 10cm

#define trigPin 9 // 초음파센서 출력 
#define echoPin 10 // 초음파센서 입력
#define ledPin 7 // LED 
#define pirPin 5 // 동작센서

long duration, distance; // 거리 측정을 위한 변수
int pirValue;
int hour, min, sec;
long second;
bool ledStatus = false;
char szBuff[80];

void setup() {
  // 핀 모드 설정
  pinMode(trigPin, OUTPUT); // 출력 모드
  pinMode(echoPin, INPUT); // 입력 모드
  pinMode(ledPin, OUTPUT); // 출력 모드
  pinMode(pirPin, INPUT); // 입력 모드
  Serial.begin(9600); // 시리얼 통신 시작
}

void loop() {
  // 초음파 센서 거리 측정

  second = millis()/1000;
  sec = second % 60;
  min = (second/60) % 60;
  hour = (second/3600) % 24;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 'echoPin에서 초음파가 돌아오는 시간 측정
  duration = pulseIn(echoPin, HIGH); 
  // 측정한 시간으로 거리 계산(왕복거리이므로 / 2, 초음파 속도 초당 29.1cm)
  distance = (duration / 2) / 29.1; 

  pirValue = digitalRead(pirPin);

  // 시리얼 모니터에 거리 출력
  sprintf(szBuff, "%02d:%02d:%02d 거리: %ld cm, PIR: %d", hour, min, sec, distance, pirValue);
  Serial.println(szBuff);
  // Serial.print("거리: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  //거리와 모션에 따른 LED 켜기/끄기
  ledStatus = false;
  if (distance <= DISTANCE) { // 거리가 10cm 이내이거나
    ledStatus = true;
    sprintf(szBuff, "TURN ON - DIST");
    Serial.println(szBuff);
  }
  if (pirValue == HIGH) { // 움직임이 있으면(10초정도)
    ledStatus = true;
    sprintf(szBuff, "TURN ON - MOTION");
    Serial.println(szBuff);
  }
  if (ledStatus) {
    digitalWrite(ledPin, HIGH); // LED 켜기
  } else {
    digitalWrite(ledPin, LOW); //LED 끄기
  }
 
  // 다음 측정을 위한 딜레이
  delay(WAIT_TIME);
}
