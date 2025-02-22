#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char* ssid = "rubixcube";           // Replace with your WiFi SSID
const char* password = "@!kaliHacker2021";   // Replace with your WiFi password

AsyncWebServer server(80);
Servo esc1, esc2, esc3, esc4;

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address

  // Initialize ESCs
  esc1.attach(D1);  // Attach the first ESC signal wire to GPIO5 (D1) on the ESP8266
  esc2.attach(D2);  // Attach the second ESC signal wire to GPIO4 (D2) on the ESP8266
  esc3.attach(D5);  // Attach the third ESC signal wire to GPIO14 (D5) on the ESP8266
  esc4.attach(D6);  // Attach the fourth ESC signal wire to GPIO12 (D6) on the ESP8266

  esc1.writeMicroseconds(1000);  // Set initial position for ESC1
  esc2.writeMicroseconds(1000);  // Set initial position for ESC2
  esc3.writeMicroseconds(1000);  // Set initial position for ESC3
  esc4.writeMicroseconds(1000);  // Set initial position for ESC4

  delay(2000);  // Delay to allow ESCs to initialize

  // Set up web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><body>";
    html += "<h1>BLDC Motor Control</h1>";
    html += "<form action=\"/control\" method=\"post\">";
    html += "<input type=\"range\" min=\"1000\" max=\"2000\" name=\"speed\" onchange=\"this.form.submit()\">";
    html += "</form>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/control", HTTP_POST, [](AsyncWebServerRequest *request) {
    String speed = request->getParam("speed", true)->value();
    int speedValue = speed.toInt();
    esc1.writeMicroseconds(speedValue);
    esc2.writeMicroseconds(speedValue);
    esc3.writeMicroseconds(speedValue);
    esc4.writeMicroseconds(speedValue);
    request->send(200, "text/plain", "Speed set to " + speed);
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Nothing needed here
}
