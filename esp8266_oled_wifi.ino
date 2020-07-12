// ESP8266 + OLED 128x64 1.3" I2C display
//***************************************
//
// This example draw text lines which contains WiFi SSID and IP address.
// Code by:
// https://github.com/odolezal
//
// OLED display datasheet:
// https://drive.google.com/file/d/19hxmIwuuTNxKzC-OcNMQJkltGV3B0DgB/view
//
// Libraries needed:
// SSD1306.h & SSD1306Wire.h:  https://github.com/squix78/esp8266-oled-ssd1306
//
// Pinout (as labeled):
// OLED ---> ESP8266
// -----------------
// GND ---> GND
// VDD (VCC) ---> 3V3
// SDA (Data) ---> D2 (GPIO 4, I2C SDA pin by default)
// SCK(Clk) ---> D1 (GPIO 5, I2C SCL pin by default)

#include <ESP8266WiFi.h>
#include <Wire.h>
#include "SH1106.h"
#include "SH1106Wire.h"

// Create a display object
SH1106 display(0x3c, SDA, SCL);

// WiFi setting 
const char* ssid = "***********";   // insert your own ssid 
const char* password = "*******";  // and password
 
void setup () {
  Serial.begin(115200);

  // Start I2C bus
  Wire.pins(0, 2);  
  Wire.begin(0, 2); 

  // Display setting  
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.drawString(35, 25, "Hello :)");
  display.display();
  delay(1500);
  display.clear();   

  // Connect to WiFi
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.print(ssid);
  display.drawString(0, 10, "Connecting to WiFi...");
  display.display();
  display.clear();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi at ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  display.drawString(0, 10, "Connected to SSID: ");
  display.display();
  display.drawString(0, 24, ssid);
  display.display();
  display.drawString(0, 38, "IP address: ");
  display.display();
  display.drawString(0, 52 , WiFi.localIP().toString());
  display.display();
    
  delay(1000);
}

void loop() {
}
