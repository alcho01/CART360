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

//Angle of servo
int angleServo = 0;

//State of movement 
int currentMovementState;

//Sound Value currently off
boolean soundVal = 0;
//Start the Servos off
boolean SERVOStatus = false;
//Have buzzer turned off at start
boolean buzzerStatus = false;


//Setup the pins to the servos | Set inputs & Outputs | Determine the current movement status

void setup() {
  Serial.begin(9600);
  
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
  //if the buzzer is off when the motion is active
    if(buzzerStatus == false) {
      //Turn the buzzer on
      buzzerStatus = true;
      //Play the buzzer sound
      digitalWrite(BUZZER,HIGH);
      //Delay for a second
      delay(1000);
    }
    else {
      //If no movement buzzer status goes back to false
      buzzerStatus = false;
      //The buzzer turns off
      digitalWrite(BUZZER, LOW);
      //Add another delay
      delay(1000);
    }
  }

  //BUZZER TO SOUND SENSOR TO SERVO COMMUNICATION

  //Get value of current sound
  soundVal = digitalRead(SOUND_SENSOR_PIN);
  Serial.println(soundVal);
  //
  if (soundVal == HIGH && SERVOStatus == false) {
    SERVOStatus = true;
    //Rotate the servos randomly
    angleServo = random(10,180);
    servo1.write(angleServo);
    servo2.write(angleServo);
    servo3.write(angleServo);
    servo4.write(angleServo);
    delay(10);
  }
  else {
    SERVOStatus = false;
    angleServo = (0);
    servo1.write(angleServo);
    servo2.write(angleServo);
    servo3.write(angleServo);
    servo4.write(angleServo);
    delay(10);
  }
}
