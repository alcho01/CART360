//Set pin for PIR sensor
int PIR_SENSOR_PIN = 4;

//Set a variable for if motion is detected or not
int currentMovementState = LOW;

//Pin Status
int value = 0; 


//PIEZO

//set pin for buzzer
int BUZZER = 11;

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
}

void loop() {
  //Read if there is movement via digital
  value = digitalRead(PIR_SENSOR_PIN);
  if (value == HIGH) {
    Serial.println("HIGH");
    buzzerSFX();
    if (currentMovementState == LOW) {
    currentMovementState == HIGH;
    }
  }
  else {
    Serial.println("LOW");
    currentMovementState == LOW;
  }
}
