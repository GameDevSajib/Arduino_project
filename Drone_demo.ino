
#include <Servo.h>
Servo m1;
Servo m2;
Servo m3;
Servo m4;

void setup() {
  
   
m1.attach(5);
m2.attach(6);
m3.attach(9);
m4.attach(10);

  m1.write(180);
  delay(2000);
  m1.write(0);
  delay(2000);

  m2.write(180);
  delay(2000);
  m2.write(0);
  delay(2000);

  m3.write(180);
  delay(2000);
  m3.write(0);
  delay(2000);

  m4.write(180);
  delay(2000);
  m4.write(0);
  delay(2000);
 

}

void loop() {
  
 m1.write(10);
 m2.write(10);
 m3.write(10);
 m4.write(10);
}
