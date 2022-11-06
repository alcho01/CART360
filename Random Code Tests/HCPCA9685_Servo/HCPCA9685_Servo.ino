/* Include the HCPCA9685 library */
#include <HCPCA9685.h>

/* Create an instance of the library and set the address */
#define  I2CAdd 0x40

//PIR SENSOR
//Set pin for PIR SENSOR
int PIR_SENSOR_PIN = 12;

//Set a variable for if motion is detected or not
int currentMovementState = LOW;

//Pin Status
int value = 0; 

//PIEZO
int BUZZERStatus = LOW;
//set pin for buzzer
int BUZZER = 11;

//set initial delay
int delayer = 15;

/* Create an instance of the library */
HCPCA9685 HCPCA9685(I2CAdd);

//Define the servo minimum and maximum positions
int servoMin = 0;
int servoMax = 180;

void setup() {
  //Testing purposes
  Serial.begin(57600);

  //Read if there is movement via digital
  value = digitalRead(PIR_SENSOR_PIN);

  //Set inputs and outputs

  //PIR as input - Whats going in
  pinMode(PIR_SENSOR_PIN, INPUT);
  //Buzzer as output - Whats going out
  pinMode(BUZZER, OUTPUT);
  
  /* Initialise the library and set it to 'servo mode' */ 
  HCPCA9685.Init(SERVO_MODE);

  /* Wake the device up */
  HCPCA9685.Sleep(false);
}

//Buzzer function to produce "Panic Sound"
void buzzerSFX() {
  
//Play the buzzer sound
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

void loop() {
   //Make a variable for servo position
   //unsigned int Pos;

  //Read if there is movement via digital
  value = digitalRead(PIR_SENSOR_PIN);
  //If motion is detected...
  if (value == HIGH) {
    //Play the buzzer sound
    buzzerSFX();
    //If the motion is detected set the delay speed to 5, to make the rotation speed faster
    delayer = 5;
    //Check if motion is equal to low 
  if (currentMovementState == LOW) {
    //If it is state this in the serial monitor
    Serial.println("DETECTED");
    //Convert the movement state to high
    currentMovementState == HIGH;
    }
  }
  else {
    //Otherwise print this 
    Serial.println("STOPPED");
    //Return the movement state to low
    currentMovementState == LOW;
    //If no movement keep the delayer at 15 
    delayer = 15;
   }

  // 
  for(int i= 0; i < 180; i++) {
    //Call each servo by denoting the pin position on the shield, then call the position 
    HCPCA9685.Servo(5, i);
    HCPCA9685.Servo(7, i);
    HCPCA9685.Servo(15, i);
    //Delay is based on if human movement was detected
    delay(delayer);
  }
  //Call each servo by denoting the pin position on the shield, then call the position 
  for(int i = 180; i >= 0; i--) {
    HCPCA9685.Servo(5, i);
    HCPCA9685.Servo(7, i);
    HCPCA9685.Servo(15, i);
    //Delay is based on if human movement was detected
    delay(delayer);
  }
}
