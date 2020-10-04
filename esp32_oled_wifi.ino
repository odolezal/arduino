/*********
LilyGO TTGO ESP32 0.96" OLED V2.0 WiFi Module
www.lilygo.cn/prod_view.aspx?TypeId=50032&Id=1152

This example draw text lines which contains WiFi SSID and IP address.

Code by:
https://github.com/odolezal
based on: https://randomnerdtutorials.com/ttgo-lora32-sx1276-arduino-ide/
*********/
#include "WiFi.h"
//Libraries for OLED Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// WiFi setting 
const char* ssid = "***********";   // insert your own ssid
const char* password = "***********";  // and password

void setup() {
  Serial.begin(115200);
  
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Display setting  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(35,25);
  display.print("Hello!");
  display.display();
  delay(2000);
  display.clearDisplay();   

  // Connect to WiFi
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.print(ssid);
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("Connecting to WiFi...");
  display.display();
  display.clearDisplay();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi at ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("Connected to SSID: ");
  display.display();
  
  display.setTextSize(1);
  display.setCursor(0,24);
  display.print(ssid); 
  display.display();
  
  display.setTextSize(1);
  display.setCursor(0,38);
  display.print("IP address: "); 
  display.display();
  
  display.setTextSize(1);
  display.setCursor(0,52);
  display.print(WiFi.localIP().toString());
  display.display();
    
  delay(2000);
}

void loop() {
  
}
