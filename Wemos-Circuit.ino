#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int buttonPin = D2;
const char* toggleURL = "http://192.168.1.210:5000/toggle";

WiFiClient client;
int prevPotValue = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  WiFi.begin("BT-F9AH7T", "x");  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {

  int potValue = analogRead(A0);

  if (abs(potValue - prevPotValue) > 30) {
    int hue = map(potValue, 0, 1023, 0, 360);
    int saturation = map(potValue, 0, 1023, 0, 100);

    String url = "http://192.168.1.210:5000/set_colour?hue=" + String(hue) + "&saturation=" + String(saturation);
    const char* colourURL = url.c_str();
    sendRequest(colourURL);

    prevPotValue = potValue;
  }

  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
      Serial.println("Button pressed");
      sendRequest(toggleURL);
  }
  
  delay(100);
}

void sendRequest(const char* url) {
  HTTPClient http;
  http.begin(client, url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.print("HTTP GET request sent to ");
    Serial.print(url);
    Serial.print(", response code: ");
    Serial.println(httpCode);
  } else {
    Serial.print("HTTP GET request failed, error: ");
    Serial.println(http.errorToString(httpCode).c_str());
  }

  http.end();
}
