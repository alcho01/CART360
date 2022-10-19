//Include servo library
#include <Servo.h> 

//Set pin for PIR sensor
int PIR_SENSOR_PIN = 2;

//Set pin for Sound sensor
int SOUND_SENSOR_PIN = 10;

//Set pin for Buzzer
int BUZZER = 11;

//Set pins for servos
int SERVO_PIN1 = 3;
int SERVO_PIN2 = 5;
int SERVO_PIN3 = 8;
int SERVO_PIN4 = 13;

//Initialize the servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//Angle of servo for each seperate 
int angleServo1 = 90;
int angleServo2 = 90;
int angleServo3 = 90;
int angleServo4 = 90;

//Delay 
int delaying = 0;

//State of movement 
int currentMovementState;

//Sound Value currently off
boolean soundVal = 0;

//Buzzer Sounds
void buzzerSFX() {
//Play the buzzer sound B note
  tone(BUZZER, 493);
  //Delay 
  delay(300);
  //Stop the buzzer 
  noTone(BUZZER);

//Play the buzzer sound 
  tone(BUZZER, 293);
  //Delay 
  delay(300);
  //Stop the buzzer 
  noTone(BUZZER);

//Play the buzzer sound
  tone(BUZZER, 329);
  //Delay 
  delay(300);
  //Stop the buzzer 
  noTone(BUZZER);
}



//Setup the pins to the servos | Set inputs & Outputs | Determine the current movement status

void setup() {
  Serial.begin(57600);
  
 //Assign what pin goes with what servo
 servo1.attach(SERVO_PIN1);
 servo2.attach(SERVO_PIN2);
 servo3.attach(SERVO_PIN3);
 servo4.attach(SERVO_PIN4);

 //PIR sensor acts as input
  pinMode(PIR_SENSOR_PIN, INPUT);
  
 //sound sensor acts as input/whats going in
  pinMode(SOUND_SENSOR_PIN, INPUT);
  
 //buzzer acts as output
  pinMode(BUZZER, OUTPUT);

 //Tell if there is movement or not
  currentMovementState = digitalRead(PIR_SENSOR_PIN);
}

//

void loop() {
  //Tell if there is movement or not
  currentMovementState = digitalRead(PIR_SENSOR_PIN);

  //MOVEMENT TO BUZZER COMMUNICATION

  //Check if the motion sensor is activated
  if (currentMovementState == HIGH) { 
    Serial.println("ON");
    //Call buzzerSFX function
     buzzerSFX();
    }
    else {
      //The buzzer turns off
      digitalWrite(BUZZER, LOW);
      Serial.println("OFF");
      //Add another delay
      delay(1000);
    }

  //BUZZER TO SOUND SENSOR TO SERVO COMMUNICATION

  //Get value of current sound
  soundVal = digitalRead(SOUND_SENSOR_PIN);
  Serial.println(soundVal);
  //
  if (soundVal == HIGH ) {
    Serial.println("PANIC");
    //Rotate the servos randomly
    angleServo1 = random(10,180);
    angleServo2 = random(10,180);
    angleServo3 = random(10,180);
    angleServo4 = random(10,180);

    //Delay set to random int between two parameters
    delaying = random(100, 500);

    //Make the servos function
    servo1.write(angleServo1);
    servo2.write(angleServo2);
    servo3.write(angleServo3);
    servo4.write(angleServo4);
    //Add the delay
    delay(delaying);
  }
  else {
    Serial.println("RELAX");
    //Set servos angles to 0 degrees
    angleServo1 = (0);
    angleServo2 = (0);
    angleServo3 = (0);
    angleServo4 = (0);

    //Turn the servos back to an angle at 0 degrees
    servo1.write(angleServo1);
    servo2.write(angleServo2);
    servo3.write(angleServo3);
    servo4.write(angleServo4);

    //Add the delay
    delay(delaying);
  }

  //
}
