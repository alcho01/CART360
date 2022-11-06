const int RUNNING_SAMPLES = 16;
int runningAverageBuffer[RUNNING_SAMPLES];
int nextCount = 0;

//Set sensor to pin 2
int soundSensor = A5;

//Set led to pin 4
int LED = 4;

int threshold = 510;

//Start the LED off
boolean LEDStatus = false;



void setup() {
  Serial.begin(57600);
  //Behave as the input/whats going in
  pinMode(soundSensor,INPUT);
  //Behave as the output/the result
  pinMode(LED, OUTPUT);
}

void loop() {
  int sensorData = analogRead(soundSensor);
      Serial.println(sensorData);
  runningAverageBuffer[nextCount] = sensorData;
  nextCount++;
  if (nextCount >= RUNNING_SAMPLES) {
    nextCount = 0;
  }

  int currentSum = 0;
  for (int i = 0; i < RUNNING_SAMPLES; i++) {
    currentSum += runningAverageBuffer[i];
  }
  
  int averageVal = currentSum / RUNNING_SAMPLES;
  delay(100);

  //Read the value of the sound sensor
   //int SensorData = digitalRead(soundSensor);
   //If sensorData is equal to 1
   if(sensorData >= threshold) {
    //when the status is equal to false
    if(LEDStatus == false) {
      //Change it to true
      LEDStatus = true;
      //Turns the led on
      digitalWrite(LED,HIGH);
      Serial.println("ON");
    }
    else {
      //Else the led is off
      LEDStatus = false;
      digitalWrite(LED, LOW);
      Serial.println("OFF");
     }
    }
   }
