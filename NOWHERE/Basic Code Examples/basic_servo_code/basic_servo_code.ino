//Include servo Library
#include <Servo.h> 

//Initialize the servos
Servo servo1;
// Servo servo2;
//Servo servo3;
//Servo servo4;

void setup() {
//Assign what pin to attach the servo to
  servo1.attach(2);
//servo2.attach(5);
//servo3.attach(8);
//servo4.attach(13);
}

void loop() {
//Rotate the servo to 180 degree and then from 180 to 0
for (int i = 0; i < 180; i++) {
  servo1.write(i);
//servo2.write(i);
//servo3.write(i);
//servo4.write(i);
  delay(10);
  }
  for (int i = 180; i > 0; i--) {
  servo1.write(i);
//servo2.write(i);
//servo3.write(i);
//servo4.write(i);
  delay(10);
  }
}
