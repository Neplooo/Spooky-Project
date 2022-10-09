#include <Arduino.h>
#include <ezButton.h>

//Ultrasonic Sensor
const int trigPin = 11;
const int echoPin = 10;

//Priming and Unpriming system
const int rLed = 4;
const int gLed = 5;
ezButton button(6);

//Piezo
const int piezo = 9;

//Ultrasonic Sensor Data Storage
long duration;
int distance;

//Button variables
int buttonState;
long buttonCount;

void setup() {
  // put your setup code here, to run once:

  //Declares Input and Output:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezo, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);

  //Button Parameters:
  button.setDebounceTime(50);

  //Serial Monitor
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  //Starts Button:
  button.loop();

  buttonState = button.getState();
  buttonCount = button.getCount();

  digitalWrite(gLed, LOW);
  digitalWrite(rLed, LOW);

  Serial.print(buttonCount);
  Serial.print(buttonState);

  if ((buttonCount % 2) == 0){


    digitalWrite(gLed, HIGH);
  

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    Serial.println(distance);

    if (distance < 70){

      tone(piezo, 1000);
      delay(2000);

    }
    else
    {

      noTone(piezo);

    }

  }
  else
  {

    digitalWrite(rLed, HIGH);

  }

}