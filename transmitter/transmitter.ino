#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

//-------------------- Wi-Fi Credentials --------------------//
const char* ssid = "MITESH";
const char* password = "Mitesh_22062004";

//-------------------- ThingSpeak ---------------------------//
unsigned long channelID = 3429353;       
const char* writeAPIKey = "4K5ZPJRF6OLUPOWI";

//-------------------- DHT11 -------------------------------//
#define DHTPIN 32       //GPIO_#% 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//-------------------- MQ9 -------------------------------//
#define MQ9_PIN 34     //GPIO_#$

WiFiClient client;

// Timer variables
unsigned long previousMillis = 0;
const unsigned long interval = 22000;   // 22 seconds

//----------------------------------------------------------//
// Setup
void setup()
{
  Serial.begin(115200);

  dht.begin();

  WiFi.mode(WIFI_STA);

  Serial.println("Connecting to Wi-Fi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

//----------------------------------------------------------//
// Loop
void loop()
{
  // Reconnect if Wi-Fi disconnects
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wi-Fi Lost! Reconnecting...");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }

    Serial.println("\nReconnected!");
  }

  // Upload every 22 seconds
  if (millis() - previousMillis >= interval)
  {
    previousMillis = millis();

    // Read DHT1
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Raed MQ9
    int mq9Value = analogRead(MQ9_PIN);

    // Check DHT11 reading
    if (isnan(temperature) || isnan(humidity))
    {
      Serial.println("Failed to read DHT11!");
      return;
    }

    // Display sensor 
    Serial.println("----------------------------");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity    : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("MQ9 Value   : ");
    Serial.println(mq9Value);

    // Set ThingSpeak field
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, mq9Value);

    // Upload all fields
    int response = ThingSpeak.writeFields(channelID, writeAPIKey);

    if (response == 200)
    {
      Serial.println("Data Uploaded Successfully");
    }
    else
    {
      Serial.print("Upload Failed. Error Code: ");
      Serial.println(response);
    }

    Serial.println("----------------------------");
  }
}
