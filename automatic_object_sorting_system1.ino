#include <Servo.h>
Servo myservo;
int sensorPin = 7;
int servoPin = 9;

int enablePin = 5;
int input1 = 4;
int input2 = 3;


bool objectCounted = false;

int shortCount = 0;
int mediumCount = 0;
int longCount = 0;

void setup() {
  
  
   pinMode(enablePin, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  digitalWrite(enablePin, HIGH);
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  
  Serial.begin(9600);
  pinMode(sensorPin, OUTPUT);
  myservo.attach(servoPin);
  
  startMotor();
}

void loop() {
  
  

  
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorPin, LOW);

 
  pinMode(sensorPin, INPUT);
  long duration = pulseIn(sensorPin, HIGH, 30000);

  
  if (duration > 0) {
    
    float distance = duration * 0.0343 / 2.0;
    
    float reference_distance = 100.0;
    float height = reference_distance - distance;
    
    if(distance >= reference_distance - 1.0){
      objectCounted = false;
    }
    
    if(height <= 20 && height > 0 &&!objectCounted){
      
      Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" cm");
    
    Serial.print("height");
    Serial.print(height);
    Serial.print(" cm");
    
    Serial.println("----------------");
      
      stopMotor();
      Serial.println("Category: SHORT");
      myservo.write(30);
      
      shortCount++;
      Serial.print("Short count: ");
      Serial.println(shortCount);
      
      objectCounted = true;
      
       delay(1000);
      myservo.write(90);
      delay(500);
      startMotor();
    }
    
    if(height > 20 && height <= 50 &&!objectCounted){
      
      Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" cm");
    
    Serial.print("height");
    Serial.print(height);
    Serial.print(" cm");
    
    Serial.println("----------------");
      
      stopMotor();
      Serial.println("Category: MEDIUM");
      myservo.write(90);
      
      mediumCount++;
      Serial.print("Medium count: ");
      Serial.println(mediumCount);
      
      objectCounted = true;
      
      
       delay(1000);
      
      delay(500);
      startMotor();
    }
    
    if(height > 50 &&!objectCounted){
      
      Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" cm");
    
    Serial.print("height");
    Serial.print(height);
    Serial.print(" cm");
    
    Serial.println("----------------");
      
      stopMotor();
      Serial.println("Category: LONG");
      myservo.write(150);
      
      longCount++;
      Serial.print("Long count: ");
      Serial.println(longCount);
      
      objectCounted = true;
      delay(1000);
      myservo.write(90);
      delay(500);
      startMotor();
    }
    
  } else {
    Serial.println("No echo detected");
  }

  delay(300);
}

void startMotor(){
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  digitalWrite(enablePin, HIGH);
}

void stopMotor(){
  digitalWrite(enablePin, LOW);
}
