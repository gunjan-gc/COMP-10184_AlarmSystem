// COMP-10184 – Mohawk College 
// PIR Sensor Test Application 
// Turn on the blue LED with motion is detected. 
 

//  I Gunjan Chaudhary, 000831804 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else.
 //Stage 4 completed
#include <Arduino.h> 
 
// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6 
 
 int buttonState =0;                //initially the led is set to off
 //this is the division of 125 ms for all blinks in 10s with 4 blinks per sec
 const int quarterBlinkSec = 125;  
 bool alarmState = true;        //to keep a track of the state of alarm at any point
//this state is used to keep a track if the PIR sensor has already sensed motion before, then it has to remain turned on and not detect any motion 2nd time
int lightState = HIGH; 



void setup() { 
  Serial.begin(115200);           // configure the USB serial monitor 
  
  pinMode(LED_BUILTIN, OUTPUT);          // configure the LED output 
 
  pinMode(PIN_PIR, INPUT);               // PIR sensor is an INPUT 
 
  pinMode(PIN_BUTTON, INPUT_PULLUP);        // Button is an INPUT 
  
  digitalWrite(LED_BUILTIN, HIGH);   //keeping led off in the beginning
} 

void loop() { 
  bool bPIR; 
  
  bPIR = digitalRead(PIN_PIR);    //reading the motion sensor
  buttonState = digitalRead(D5);   //Reading button state
  bool finalState =false;           // to keep strack of the finalState of alarm
//if motion detected and it is the first time when motion is gtting detected, then start blinking
  if(bPIR == HIGH && lightState == HIGH && alarmState== true){
 
  for(int i =0; i< 40; i++)     //loop till 40 because 4 times per sec * 10 sec
  {
//if the button is pressed, break the loop in whatever state it is i.e., if it is blnking, even then break it
    if(digitalRead(D6) == 0){
      finalState = true;
      break;
    }
    //otherwise finish blink cycle
    digitalWrite(LED_BUILTIN, !bPIR);     //turn on led
    delay(quarterBlinkSec);               //delay for 125 ms because we have to blink 4 times per second
    digitalWrite(LED_BUILTIN, bPIR);      //turn off led
    delay(quarterBlinkSec);               //delay of 125 ms
  }
  
  if(finalState == true){
  lightState = LOW;                     //state to keep a record that motion has already been detected 1 time
  digitalWrite(LED_BUILTIN, !bPIR);   //keep it on after blink is over
  alarmState = false;
  }
  //if motion has been detected before, then keep light turned on
  else {
    digitalWrite(LED_BUILTIN, !bPIR);
    alarmState = false;
    }
  
//if button is clikced to turn on the alarm, again, then break 
  if(digitalRead(D6) ==0){
    alarmState = true;
  }
}
