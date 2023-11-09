
/*  ********************************************************************************
 *  Monitor Heart Rate using Pulse sensor and Distance Detector using ultrasonic
 *
*/

#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>        


// defines variables for ultrasonic sensor
long duration;
int distance;
const int trigPin = 9;
const int echoPin = 10;

const int pulse_LED = 2;
const int ultrasonic_LED = 3;


// Define Variables for pulse sensor
const int PulseWire = 0;       
const int LED = LED_BUILTIN;          

int Threshold = 500;           
                           
PulseSensorPlayground pulseSensor;  

void init_ultrasonic()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(pulse_LED, OUTPUT);   // PIN 2 is LED for pulse sensor
  pinMode(3, OUTPUT);   // PIN 3 is LED for ultrasonic sensor

}


void init_pulse_sensor()
{
    // Configure PulseSensor 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       
  pulseSensor.setThreshold(Threshold);   
  digitalWrite(pulse_LED, LOW); // turn the LED on (HIGH is the voltage level)
  digitalWrite(3, LOW);   
  pulseSensor.begin();
    
}
//Configure Serial Monitor
void setup() {   
 
  init_ultrasonic();
  Serial.begin(9600);    //start serial communication
  init_pulse_sensor();

}

void loop() {

// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the 340 m/s to 0.034 cm/micro seconds
  distance = duration * 0.034 / 2;
  
  //if distance is less than 4 cm, turn on LED
  if (distance<4){
  digitalWrite(ultrasonic_LED, HIGH); 
  delay(500);
     
  } else
  {
    digitalWrite(ultrasonic_LED, LOW);  
  }
if (pulseSensor.sawStartOfBeat()) {            
 int myBPM = pulseSensor.getBeatsPerMinute();  
 Serial.println(myBPM);   
// If the average heart rate is higher than 100, it turns the LED on 
 if (myBPM>100){
  digitalWrite(pulse_LED, HIGH); 
  delay(500);
  }
  else 
  {
  digitalWrite(pulse_LED, LOW); 
  }
}
delay(20);    

}  
