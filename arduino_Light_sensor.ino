//Arduino: UUGear Light Sensor Module
//************************************
//Code by: https://github.com/odolezal

//Based on:
//https://create.arduino.cc/projecthub/kiranpaul/light-magic-using-lm393-and-arduino-uno-14eadc
//https://www.instructables.com/id/LDR-Sensor-Module-Users-Manual-V10/

//Vendor site:
//http://www.uugear.com/product/uugear-light-sensor-module-4-wire-with-both-digital-and-analog-output/

//Wires:
// G -> GND.
// V -> 3.3V
// D -> GPIO 8
// A -> A0

// Red LED is power indicator.
//************************************
//Define pins:
const int D = 8; // set digital on GPIO 8
const int A = A0; //set analog on A0

unsigned int analog;
int digital;

void setup() {
  Serial.begin(9600); //initialise serial monitor
  pinMode(D, INPUT); // initialise digital input
  pinMode(A, INPUT); // initialise analog input
}

void loop() {
  analog = analogRead(A); 
  digital = digitalRead(D);      
  Serial.println("Light intensity (digital detection):"); 
  Serial.println(digital); // 1 = "dark", 0 = "light" and blue LED on module shine         
  Serial.println("Light intensity (analog value):");
  Serial.println(analog); // higher value = "dark", lower value = "light" 
  delay(500);
}
