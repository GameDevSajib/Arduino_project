#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char* ssid = "rubixcube";           // Replace with your WiFi SSID
const char* password = "@!kaliHacker2021";   // Replace with your WiFi password

AsyncWebServer server(80);
Servo esc;

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

  // Initialize ESC
  esc.attach(5);  // Attach the ESC signal wire to pin 5 on the ESP8266
  esc.writeMicroseconds(1000);  // Set initial position
  delay(2000);  // Delay to allow ESC to initialize

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
    esc.writeMicroseconds(speed.toInt());
    request->send(200, "text/plain", "Speed set to " + speed);
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Nothing needed here
}