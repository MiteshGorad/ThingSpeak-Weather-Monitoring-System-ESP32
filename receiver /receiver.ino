#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//================ LCD =================//
LiquidCrystal_I2C lcd(0x27, 16, 2);

//============== Wi-Fi =================//
const char* ssid = "MITESH";
const char* password = "Mitesh_22062004";

//=========== ThingSpeak ===============//
String channelID = "3429353";
String readAPIKey = "Q59HZ28HAMMED4AI";

//============== Timer =================//
unsigned long previousMillis = 0;
const unsigned long interval = 20000;   //20 seconds

void setup()
{
  Serial.begin(115200);

  // Initialize LCD
  lcd.begin();//(16, 2);
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Connecting...");
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(2000);
}

void loop()
{
  if (millis() - previousMillis >= interval)
  {
    previousMillis = millis();

    if (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
      }
    }

    HTTPClient http;

    // Read latest JSON data
    String url =
      "https://api.thingspeak.com/channels/" +
      channelID +
      "/feeds/last.json?api_key=" +
      readAPIKey;

    http.begin(url);

    int httpCode = http.GET();

    if (httpCode == 200)
    {
      String payload = http.getString();

      JsonDocument doc;
      deserializeJson(doc, payload);

      float temperature = doc["field1"];
      float humidity    = doc["field2"];
      int mq9           = doc["field3"];

      // Print on Serial Monitor
      Serial.println("----------------------");
      Serial.print("Temperature : ");
      Serial.println(temperature);

      Serial.print("Humidity    : ");
      Serial.println(humidity);

      Serial.print("MQ9         : ");
      Serial.println(mq9);

      // Display on LCD
      lcd.clear();

      // First Row
      lcd.setCursor(0,0);
      lcd.print("T:");
      lcd.print(temperature,1);
      lcd.print((char)223);    // Degree Symbol
      lcd.print("C");

      // Second Row
      lcd.setCursor(0,1);
      lcd.print("H:");
      lcd.print(humidity,0);
      lcd.print("%");

      lcd.setCursor(9,1);
      lcd.print("G:");
      lcd.print(mq9);
    }
    else
    {
      lcd.clear();
      lcd.print("HTTP Error");
      Serial.println(httpCode);
    }

    http.end();
  }
}
