// Replaced actual Blynk Template ID for security reasons
#define BLYNK_TEMPLATE_ID "YourTemplateID"
// Template name retained as it does not expose any credentials
#define BLYNK_TEMPLATE_NAME "Smart Room Monitoring"
// Replaced actual Blynk Auth Token for security reasons
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Replaced actual token for security reasons
char auth[] = "YourAuthToken";
// Replaced actual WiFi SSID for security reasons
char ssid[] = "YourWiFiSSID";
// Replaced actual WiFi password for security reasons
char pass[] = "YourWiFiPassword";

#define DHTPIN 2  // Use GPIO number, not D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t); // Send temp to app
  Blynk.virtualWrite(V1, h); // Send humidity to app

  if (t > 33.0) {
    Blynk.logEvent("temp_alert", "Room temperature is above 33°C!");
  }

  if (h > 70.0) {
    Blynk.logEvent("humidity_alert", "Humidity level is above 70%!");
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(2000L, sendSensor); // every 2 sec
}

void loop() {
  Blynk.run();
  timer.run();
}
