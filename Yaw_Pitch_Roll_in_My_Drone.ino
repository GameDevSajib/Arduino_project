#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>

const char* ssid = "rubixcube";           // Replace with your WiFi SSID
const char* password = "@!kaliHacker2021";   // Replace with your WiFi password

AsyncWebServer server(80);

// Create servo objects for ESCs controlling pitch, yaw, and roll
Servo esc_pitch;
Servo esc_yaw;
Servo esc_roll;

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
  esc_pitch.attach(5);  // Attach pitch ESC signal wire to GPIO5 (D1)
  esc_yaw.attach(5);    // Attach yaw ESC signal wire to GPIO5 (D1)
  esc_roll.attach(5);   // Attach roll ESC signal wire to GPIO5 (D1)
  
  esc_pitch.writeMicroseconds(1000);  // Set initial position for pitch
  esc_yaw.writeMicroseconds(1000);    // Set initial position for yaw
  esc_roll.writeMicroseconds(1000);   // Set initial position for roll

  delay(2000);  // Delay to allow ESCs to initialize

  // Set up web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = "<html><body>";
    html += "<h1>Drone Control</h1>";
    html += "<form action=\"/control\" method=\"post\">";
    html += "<label>Pitch:</label><input type=\"range\" min=\"1000\" max=\"2000\" name=\"pitch\" onchange=\"this.form.submit()\"><br>";
    html += "<label>Yaw:</label><input type=\"range\" min=\"1000\" max=\"2000\" name=\"yaw\" onchange=\"this.form.submit()\"><br>";
    html += "<label>Roll:</label><input type=\"range\" min=\"1000\" max=\"2000\" name=\"roll\" onchange=\"this.form.submit()\"><br>";
    html += "</form>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/control", HTTP_POST, [](AsyncWebServerRequest *request) {
    String pitch = request->getParam("pitch", true)->value();
    String yaw = request->getParam("yaw", true)->value();
    String roll = request->getParam("roll", true)->value();
    
    esc_pitch.writeMicroseconds(pitch.toInt());
    esc_yaw.writeMicroseconds(yaw.toInt());
    esc_roll.writeMicroseconds(roll.toInt());
    
    String response = "Pitch set to " + pitch + "<br>Yaw set to " + yaw + "<br>Roll set to " + roll;
    request->send(200, "text/html", response);
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Nothing needed here
}
