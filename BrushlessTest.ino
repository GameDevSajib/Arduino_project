#include <Servo.h>

Servo esc;

void setup() {
  esc.attach(5); // Attach the ESC signal wire to pin 5 on Arduino
  esc.writeMicroseconds(1000); // Set initial position
  delay(2000); // Delay to allow ESC to initialize
}

void loop() {
  esc.writeMicroseconds(1500); // Set the speed (1500 is typically the mid-point)
  delay(1000); // Run at this speed for 1 second
  esc.writeMicroseconds(2000); // Increase the speed
  delay(1000); // Run at this speed for 1 second
  esc.writeMicroseconds(1000); // Decrease the speed
  delay(1000); // Run at this speed for 1 second
}
