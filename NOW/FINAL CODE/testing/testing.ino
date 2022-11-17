//Include the Adafruit PWM Servo library because I am utilizing the PCA9685 Servo Shield 
#include <Adafruit_PWMServoDriver.h>

//Create 3 variables to be called for the servo motors
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x40);

/* Determine the Minimum and Maximum pulse length count. I played around with these numbers till I was
satisfied with the outcome */
int servoMinStateRelax = 100;
int servoMaxStateRelax = 250;

int servoMinStatePanic = 350;
int servoMaxStatePanic = 650;

int timeAfterStatePanicServo1 = 1500;
int timeAfterStatePanicServo2 = 2000;
int timeAfterStatePanicServo3 = 2500;
int timeFinisher = 5000;

long unsigned int timeTurnedLowServo1;
long unsigned int timeTurnedLowServo2;
long unsigned int timeTurnedLowServo3;
long unsigned int timeOverFinisher;

bool checkTimerActivationServo1 = false;
bool checkTimerActivationServo2 = false;
bool checkTimerActivationServo3 = false;

//Set the Servo Frequency
int servoFreq = 50;

//Determine the pin output for each servo on the shield
int servo1 = 0;
int servo2 = 8;
int servo3 = 15;

//PIR SENSOR

//Set pin for PIR Sensor
int PIR_SENSOR_PIN = 12;

//Set a variable to determine if motion is detected or not
//int currentMovementState = LOW;
//No motion at the start of the program
int currentMovementState = true;

//Sensor Status 
int value = 0;

// When the sensor is low, it stays high for this duration
int timeAfterPIRLow = 5000;

long unsigned int timeTurnedLow;

//read when the sensor turns off
boolean readLowTime; 

//I researched that it takes roughly 10 to 60 seconds to calibrate the sensor.
int calibratePIR = 30;


//Pins for vibration sensors
//int vibrationSensor = A0;
//int vibrationSensor2 = ;


//PIEZO

//set pin for the buzzer
//int BUZZER_PIN = 11;

//Amplifier pin

int AMP_PIN = 11;


//Set initial delay 
int delayer = 5;

//Buzzer function to produce "Panic Sound"
void buzzerSFX() {
  
//Play the buzzer sound
  tone(AMP_PIN, 493);
  //Delay 
  delay(300);
  //Stop the buzzer 
  noTone(AMP_PIN);
  
//Play the buzzer sound 
  tone(AMP_PIN, 293);
  //Delay 
  delay(300);
  //Stop the buzzer 
  noTone(AMP_PIN);

//Play the buzzer sound
  tone(AMP_PIN, 329);
  //Delay 
  delay(300);
  //Stop the buzzer 
  noTone(AMP_PIN);
}

//
//void vibrationSoundCue() { }

void setup() {
  //Testing purposes
  Serial.begin(57600);

  //Start each board
  pwm1.begin();
  pwm2.begin();
  pwm3.begin();

  //Set the oscillator frequency 
  pwm1.setOscillatorFrequency(27000000);
  pwm2.setOscillatorFrequency(27000000);
  pwm3.setOscillatorFrequency(27000000);

  //Set the servo frequency
  pwm1.setPWMFreq(servoFreq);
  pwm2.setPWMFreq(servoFreq);
  pwm3.setPWMFreq(servoFreq);
  
  //Read if there is movement via digitalRead
  value = digitalRead(PIR_SENSOR_PIN);

  //Set inputs and outputs

  //PIR as input - Whats going in
  pinMode(PIR_SENSOR_PIN, INPUT);

  //Buzzer as output - Whats going out
  pinMode(AMP_PIN, OUTPUT);

  //Sensor is off
  readLowTime = LOW;

  //For testing to see when calibration is complete
  Serial.println("Calibrating Sensor");
  //Convert time to milliseconds
  delay(calibratePIR * 1000);
  //For testing to see when calibration is complete
  Serial.println("Calibration Complete");
}

void loop() {

  //Read if there is movement via digital
  value = digitalRead(PIR_SENSOR_PIN);
  //Check to see if the input is high
  if (value == HIGH) {
    //Play the buzzer sound
    buzzerSFX();
    panicState();
    //If the motion is detected set the delay speed to 1, to make the rotation speed faster
     delayer = 1;
   //Count the millis when the panic state activates
   timeTurnedLowServo1 = millis();
   checkTimerActivationServo1 = true;
   //timeTurnedLowServo2 = millis();
   //timeTurnedLowServo3 = millis();
    //Change the currentmovement state to high if it is low
  if (currentMovementState == LOW) {
    //Read the given line for testing purposes to see if it works
    Serial.println("DETECTED");
    currentMovementState = HIGH;
    }
  }
  
  else {
    //Read the given line for testing purposes to see if it works
   // Serial.println("STOPPED");
    //turning it off 
    if (currentMovementState == HIGH) {
      Serial.println("STOPPED");
      currentMovementState = LOW;
      //If no movement keep the delayer at 5 seconds
      delayer = 5;
      //Count the millis when the PIR goes low
      timeTurnedLow = millis();

//      resetter();

      //Check to see if enough time has passed 
   if (!currentMovementState && (millis() - timeTurnedLow) > timeAfterPIRLow) {
     Serial.println("Time High Ended");
     noTone(AMP_PIN); //Turn off the buzzer if it is playing
   }
   //delay(1000);  
 }
    }
   // currentMovementState == LOW;
    //If no movement keep the delayer at 5 seconds
   // delayer = 5;

   
 //CALM OR RELAXED STATE

   for (int i = servoMinStateRelax; i <= servoMaxStateRelax; i++) {
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStateRelax; i >= servoMinStateRelax; i--) {  
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
  }


void panicState() {
  if (checkTimerActivationServo1 == true && (millis() - timeTurnedLowServo1) > timeAfterStatePanicServo1) {
    Serial.println("Activate Panic Servo1");

    timeTurnedLowServo2 = millis();
    checkTimerActivationServo2 = true;

   for (int i = servoMinStatePanic; i <= servoMaxStatePanic ; i++) {
     pwm1.setPWM(servo1, 0, i);
    // pwm2.setPWM(servo2, 0, i);
    // pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStatePanic ; i >= servoMinStatePanic; i--) {  
     pwm1.setPWM(servo1, 0, i);
    // pwm2.setPWM(servo2, 0, i);
    // pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
  }

    if (checkTimerActivationServo2 == true && (millis() - timeTurnedLowServo2) > timeAfterStatePanicServo2) {
    Serial.println("Activate Panic Servo2");

    timeTurnedLowServo3 = millis();
    checkTimerActivationServo3 = true;

   for (int i = servoMinStatePanic; i <= servoMaxStatePanic ; i++) {
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
    // pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStatePanic ; i >= servoMinStatePanic; i--) {  
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
   //  pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
  }

    if (checkTimerActivationServo3 == true && (millis() - timeTurnedLowServo3) > timeAfterStatePanicServo3) {
    Serial.println("Activate Panic Servo3");

    timeOverFinisher = millis();

   for (int i = servoMinStatePanic; i <= servoMaxStatePanic ; i++) {
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStatePanic ; i >= servoMinStatePanic; i--) {  
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
  }
 }

//Play a different tone to notify vibrations.
 void panicVerge() {
  
 }

//void resetter() {
  //if (millis() - timeOverFinisher > timeFinisher) {
   // checkTimerActivationServo1 = false;
   // checkTimerActivationServo2 = false;
   // checkTimerActivationServo3 = false;

 //   delay(delayer);
 //// }
//}
