  // 심박수 측정(심장박동 센서) 

/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks the builtin LED with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {

 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
}

  delay(20);                    // considered best practice in a simple sketch.

}

    //심박수 특정 임계치 초과하는 경우 led 켜기(led)
      void setup(){
        pinMode(4, OUTPUT); // 핀 4번을 출력으로
        Serial.begin(9600); // 시리얼통신설정
      }
      void loop(){

        int pulse = analogRead(A0); //data변수에 조도센서 측정값 저장

        delay(200);
        if(pulse>300 || pulse<40)digitalWrite(4,HIGH); // 심박수가 300이 넘거나 40 이하면 4번핀에 HIGH값
        else digitalWrite(4, LOW); // a가 300이 안넘으면 4번핀에 LOW값

        Serial.println(pulse);

      }
        // 일정 시간 지나도 계속 임계치 초과하는 경우 경보음 발생(스피커)

 
          //버튼 상태 감지(스위치)
          #define LED 8
          #define BURRON 7

          bool bFlag = false; // LED 상태값을 저장

          void setup()
          {
            pinMode(BUTTON, INPUT);
            pinMode(LED, OUTPUT);
          }

          void loop()
          {
            if (digitalRead(BUTTON) == HIGH) // 버튼이 눌려진 상태인가?
            {
              bFlag = true; // 상태값을 반대로 변경
            }
            else // 버튼이 눌려졌다가 떨어진 상태인가?
            {
              if (bFlag == true) // 상태값이 on인지 확인
              {
                if(digitalRead(LED) == HIGH) // LED가 꺼져 있으면 켜주고 반대로 켜져 있으면 꺼준다
                {
                  digitalWrite(LED, LOW);
                }
                else
                {
                  digitalWrite(LED, HIGH);
                }

                bFlag = false; //상태값 변경
              }
            }

            delay(100); // 딜레이
          }

            // 버튼을 누른 경우
              //led 끄기, 경보음 끄기

            // 버튼을 누르지 않은 경우
              // 전화 걸기(블루투스 모듈 HC-06)
