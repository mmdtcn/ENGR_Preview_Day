/*  ********************************************************************************
 *  Monitor Heart Rate using Pulse sensor 
 *
*/
/***Set up interrupts and relevant library*/

#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>        


// Define Variables
const int PulseWire = 0;       
const int LED = LED_BUILTIN;          
int Threshold = 500;           
                            
PulseSensorPlayground pulseSensor;  

//Configure Serial Monitor
void setup() {   

  Serial.begin(9600);    
  
  pinMode(2, OUTPUT);

  // Configure PulseSensor 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       
  pulseSensor.setThreshold(Threshold);   
  digitalWrite(2, LOW); // turn the LED on (HIGH is the voltage level)
  if (pulseSensor.begin()){

    
  }
 
}


void loop() {


if (pulseSensor.sawStartOfBeat()) {            
 int myBPM = pulseSensor.getBeatsPerMinute();  
                 
 Serial.println(myBPM);       
 if (myBPM>100)
  digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level) 
  delay(20);
  digitalWrite(2, LOW); // turn the LED on (HIGH is the voltage level)      
   
}
 
  delay(20);    
       

}
