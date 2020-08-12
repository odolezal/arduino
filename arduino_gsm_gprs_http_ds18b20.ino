// Arduino SIM800L + DS18B20 Temperature Sensor 
// Logging with GPRS HTTP GET requests

#include <SoftwareSerial.h>
#include <String.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// Define Software Serial object
SoftwareSerial gprsSerial(2, 3); //RX, TX pins
 
void setup()
{
  gprsSerial.begin(9600); // the GPRS baud rate  
  Serial.begin(9600);    // the Serial console monitoring baud rate
  delay(100);
  Serial.println("Arduino SIM800L + DS18B20 Temperature sensor."); 
  Serial.println("Software Serial initialized. Ready for \"AT\" commands.");
}
 
void loop()
{
//GPRS internet handler  
  if (gprsSerial.available())
    Serial.write(gprsSerial.read());
 
  gprsSerial.println("AT"); //basic test
  Serial.println(" ");
  Serial.println("Is GSM module ready?");
  delay(1000);
  ShowSerialData();
 
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); //start GPRS mode
  Serial.println(" ");
  Serial.println("Start GPRS mode:");
  delay(1000);
  ShowSerialData();
 
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"internet.t-mobile.cz\""); //set APN
  Serial.println(" ");
  Serial.println("Set APN:");
  delay(1000);
  ShowSerialData();
 
  gprsSerial.println("AT+SAPBR=1,1"); //activate bearer profile
  Serial.println(" ");
  Serial.println("Activate bearer profile:");
  delay(1000);
  ShowSerialData();
 
  gprsSerial.println("AT+SAPBR=2,1"); //check IP address
  Serial.println(" ");
  Serial.println("Assigned IP address:");
  delay(1000);
  ShowSerialData();

  gprsSerial.println("AT+HTTPINIT"); //start HTTP service
  Serial.println(" ");
  Serial.println("Start HTTP service:");
  delay(1000);
  ShowSerialData();

  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.println(" ");
  Serial.print("Requesting temperature... ");
  sensors.requestTemperatures(); // Send the command to get temperatures
  delay(100);
  Serial.println("Done");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature is: ");
  float t = sensors.getTempCByIndex(0); // Read temperature in "t" variable
  if (t == -127.00) {                   // If you have connected it wrong, Dallas read this temperature! :)
    Serial.println("Error!");
    return;
  }
  Serial.print(t);
  Serial.println(" °C");
  
  //set URL
  String stringurl1 = String("AT+HTTPPARA=\"URL\",\"http://odolezal.cz/teplomer2/?tx810he5pw=");
  String stringurl2 = String("\"");
  String urlfinal = String(String(stringurl1) + String(t) + String(stringurl2));
  gprsSerial.println(urlfinal);
  Serial.println(" ");
  Serial.print("Set URL: ");
  Serial.println(urlfinal);
  delay(1000);
  ShowSerialData();
 
  gprsSerial.println("AT+HTTPACTION=0"); //perform GET request
  Serial.println(" ");
  Serial.println("Perform GET request:");
  delay(1000);
  ShowSerialData();

  gprsSerial.println("AT+HTTPTERM"); //terminate HTTP service
  Serial.println(" ");
  delay(2000);
  ShowSerialData();

  Serial.println("Connection closed, data has been sended.");
  Serial.println("****************************************");

  //Next temperature reading in 5 min
  delay(300000);
} 

void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(1000); 
  
}
