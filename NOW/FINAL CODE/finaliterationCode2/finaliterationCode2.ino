//Include the Adafruit PWM Servo library because I am utilizing the PCA9685 Servo Shield 
#include <Adafruit_PWMServoDriver.h>
#include "pitches.h"
/* SERVO */

//Create 3 variables to be called for the servo motors
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x40);

int melody [ ] = {
   NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4
};

int melody2 [ ] = {
   NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, 0, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_A4,
};

int melody3 [ ] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
};

int melody4 [ ] = {
  NOTE_D4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, 
};

int noteDurations[] = {
  4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2
};

int noteDurations2[] = {
  4, 4, 4, 4, 3, 4, 3, 4, 4, 4, 4, 3, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 3
};

int noteDurations3[] = {
  4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
};

int noteDurations4[] = {
  4, 8, 4, 8, 4
};

//delayer
int delayer = 5;

/* Determine the Minimum and Maximum pulse length count. I played around with these numbers till I was
satisfied with the outcome */
int servoMinStateRelax = 100;
int servoMaxStateRelax = 250;

int servoMinStatePanic = 350;
int servoMaxStatePanic = 650;

//Timer Variables for the panic state
int timeAfterStatePanicServo1 = 1500;
int timeAfterStatePanicServo2 = 2000;
int timeAfterStatePanicServo3 = 2500;
int timeFinisher = 3000;

long unsigned int previousTime = 0;
long unsigned int timeTurnedLowServo1;
long unsigned int timeTurnedLowServo2;
long unsigned int timeTurnedLowServo3;
long unsigned int timeOverFinisher;

bool checkTimerActivationServo1 = false;
bool checkTimerActivationServo2 = false;
bool checkTimerActivationServo3 = false;
bool timeOver = false;

//Set the Servo Frequency
int servoFreq = 50;

//Determine the pin output for each servo on the shield
int servo1 = 0;
int servo2 = 8;
int servo3 = 15;

/*PIR SENSOR*/ 

//Set pin for PIR Sensor
int PIR_SENSOR_PIN = 12;

//Set a variable to determine if motion is detected or not

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

/*Amplifier and Surface Transducer*/

//Set the pin for the amplifier

int AMP_PIN = 11; 

/*Vibration Sensors*/

//Set the pins for the vibration sensors

int diskPin1 = A0;
int diskPin2 = A3;
int diskPin3 = A8;


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

  //SET INPUTS FOR VIBRATION SENSORS
  //pinMode(diskPin1, INPUT);
  //pinMode(diskPin2, INPUT);
  //pinMode(diskPin3, INPUT);
  //pinMode(diskPin4, INPUT);

  //Read if there is movement via digitalRead
  value = digitalRead(PIR_SENSOR_PIN);

  //PIR as input - Whats going in
  pinMode(PIR_SENSOR_PIN, INPUT);

  pinMode(AMP_PIN, OUTPUT);

  pinMode(diskPin1, INPUT);
  pinMode(diskPin2, INPUT);
  pinMode(diskPin3, INPUT);


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
  relaxed();
  checkForMovement();
  checkForVibration();
}


void relaxedAlarm() {
  
}

void areaAAlarm() {

    for (int thisNote = 0; thisNote < 15; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];

    tone(AMP_PIN, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    noTone(AMP_PIN);
  }

}

void areaBAlarm() {

    for (int thisNote = 0; thisNote < 24; thisNote++) {
    int noteDuration = 1000 / noteDurations2[thisNote];

    tone(AMP_PIN, melody2[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.10;

    delay(pauseBetweenNotes);

    noTone(AMP_PIN);
  }
  
}

void areaCAlarm(){

  for (int thisNote = 0; thisNote < 28; thisNote++) {
    int noteDuration = 1000 / noteDurations3[thisNote];

    tone(AMP_PIN, melody3[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.10;

    delay(pauseBetweenNotes);

    noTone(AMP_PIN);
  }
  
}

void panicAlarm() {

   for (int thisNote = 0; thisNote < 5; thisNote++) {
    int noteDuration = 1000 / noteDurations4[thisNote];

    tone(AMP_PIN, melody4[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.10;

    delay(pauseBetweenNotes);

    noTone(AMP_PIN);
  }
  
}

void checkForMovement() {
  //Read if there is movement via digital
  value = digitalRead(PIR_SENSOR_PIN);
  //Check to see if the input is high
  if (value == HIGH) {
    //Play the buzzer sound
    //buzzerSFX();
    panicAlarm();
    panic();
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
      relaxed();
//      resetter();

      //Check to see if enough time has passed 
   if (!currentMovementState && (millis() - timeTurnedLow) > timeAfterPIRLow) {
     Serial.println("Time High Ended");
      noTone(AMP_PIN); //Turn off the buzzer if it is playing
   }
   //delay(1000);  
  }
 }
}

void checkForVibration() {
  int vibrationCheck = analogRead(diskPin1);
  vibrationCheck = map(vibrationCheck, 0, 1023, 0, 20);
  Serial.print("Threshold: ");
  Serial.println(vibrationCheck);

  

  int vibrationCheck2 = analogRead(diskPin2);
  vibrationCheck2 = map(vibrationCheck2, 0, 1023, 21, 40);
  Serial.print("Threshold2: ");
  Serial.println(vibrationCheck2);

  

  int vibrationCheck3 = analogRead(diskPin3);
  vibrationCheck3 = map(vibrationCheck3, 0, 1023, 41, 60);
  Serial.print("Threshold3: ");
  Serial.println(vibrationCheck3);

  

  if (vibrationCheck < 2) {
     Serial.println("Area A detected");
     areaAAlarm();
     presenceFeltA();
     
 }

  if (vibrationCheck2 <= 21) {
     Serial.println("Area B detected");
     areaBAlarm();
     presenceFeltB();
  }

  if (vibrationCheck3 < 42) {
     Serial.println("Area C detected");
     areaCAlarm();
     presenceFeltC();
  } 
}

void relaxed() {

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


void presenceFeltA() {

   for (int i = servoMinStateRelax; i <= servoMaxStateRelax; i++) {
     //pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     //pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStateRelax; i >= servoMinStateRelax; i--) {  
    // pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
    // pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
}

void presenceFeltB() {

   for (int i = servoMinStateRelax; i <= servoMaxStateRelax; i++) {
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     //pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStateRelax; i >= servoMinStateRelax; i--) {  
     pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     //pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
}

void presenceFeltC() {

   for (int i = servoMinStateRelax; i <= servoMaxStateRelax; i++) {
     //pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     pwm3.setPWM(servo3, 0, i);
     delay(delayer);   
   }

   for (int i = servoMaxStateRelax; i >= servoMinStateRelax; i--) {  
     //pwm1.setPWM(servo1, 0, i);
     pwm2.setPWM(servo2, 0, i);
     pwm3.setPWM(servo3, 0, i);
     delay(delayer);
   }
}
  
  


void panic() {
  
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
    timeOver = true;

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
  
  if (timeOver == true && (timeOverFinisher - previousTime) > timeFinisher) {
    Serial.println("stop");
   checkTimerActivationServo1 = false;
   checkTimerActivationServo2 = false;
   checkTimerActivationServo3 = false; 

   previousTime = timeTurnedLowServo1;
   previousTime = timeTurnedLowServo2;
   previousTime = timeTurnedLowServo3;
   previousTime = timeOverFinisher;
  }
}


//By default have the mirrors go up and down at a constant rate [DONE]

//When motion is detected stop the mirrors to change states. A mirror at a time will translate along the Y-Axis gaining speed - When one mirror reaches the specified threshold the next mirror goes and it follows. [DONE]

//If the analog reading value of vibration reaches a specific threshold play a sound reverberating from the transducer and move the servos in a unique fashion
