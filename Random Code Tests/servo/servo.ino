//#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x40);

int SERVOMIN = 100; // This is the 'minimum' pulse length count (out of 4096)
int SERVOMAX = 250; // This is the 'maximum' pulse length count (out of 4096)
int SERVO_FREQ = 50; // Analog servos run at ~50 Hz updates

int servo1 = 0;
int servo2 = 8;
int servo3 = 15;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm1.begin();
  pwm2.begin();
  pwm3.begin();
  
  pwm1.setOscillatorFrequency(27000000);
  pwm2.setOscillatorFrequency(27000000);
  pwm3.setOscillatorFrequency(27000000);

  pwm1.setPWMFreq(SERVO_FREQ);
  pwm2.setPWMFreq(SERVO_FREQ);
  pwm3.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void loop() {
  // Drive each servo one at a time using setPWM()
  Serial.println(servo1);
  for (int pulselen = SERVOMIN; pulselen <= SERVOMAX; pulselen++) {
    pwm1.setPWM(servo1, 0, pulselen);
    pwm2.setPWM(servo2, 0, pulselen);
    pwm3.setPWM(servo3, 0, pulselen);
    delay(5);
  }
  for (int pulselen = SERVOMAX; pulselen >= SERVOMIN; pulselen--) {
    pwm1.setPWM(servo1, 0, pulselen);
    pwm2.setPWM(servo2, 0, pulselen);
    pwm3.setPWM(servo3, 0, pulselen);
    delay(5);
  }
}
