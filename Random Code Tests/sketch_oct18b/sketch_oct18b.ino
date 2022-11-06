//Include servo library
#include <Servo.h> 

//Set pin for PIR sensor
int PIR_SENSOR_PIN = 4;

//Set pins for servos
int SERVO_PIN1 = 3;
int SERVO_PIN2 = 6;
int SERVO_PIN3 = 8;
int SERVO_PIN4 = 13;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int delaying = 0;

//State of movement 
int currentMovementState;

//Angle of servo for each seperate 
int angleServo1 = 90;
int angleServo2 = 90;
int angleServo3 = 90;
int angleServo4 = 90;

void setup() {

  Serial.begin(57600);
  servo1.attach(SERVO_PIN1);
  servo2.attach(SERVO_PIN2);
  servo3.attach(SERVO_PIN3);
  servo4.attach(SERVO_PIN4);
  //PIR sensor acts as input
  pinMode(PIR_SENSOR_PIN, INPUT);

   //Tell if there is movement or not
  currentMovementState = digitalRead(PIR_SENSOR_PIN);

}

void loop() {
   currentMovementState = digitalRead(PIR_SENSOR_PIN);

   if (currentMovementState == HIGH) { 
    Serial.println("Hey I got you!!!");
     angleServo1 = random(10,180);
     angleServo2 = random(10,180);
     angleServo3 = random(10,180);
     angleServo4 = random(10,180);
    //Delay set to random int between two parameters
    delaying = random(100, 500);

     servo1.write(angleServo1);
     servo2.write(angleServo2);
     servo3.write(angleServo3);
     servo4.write(angleServo4);

    //Add the delay
    delay(delaying);
   }
     else {
  Serial.println("RELAX");
      angleServo1 = (0);
    angleServo2 = (0);
      angleServo3 = (0);
      angleServo4 = (0);
       
      servo1.write(angleServo1);
      servo2.write(angleServo2);
      servo3.write(angleServo3);
      servo4.write(angleServo4);
       
      delay(delaying);
     }
}
