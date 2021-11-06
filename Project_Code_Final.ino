#include <LiquidCrystal.h>
#include <Servo.h>

const int LM35 = A0;
const int motor = 13;
const int LedRed = 12;
const int LedGreen = 11;
float sensorValue;
//float distance,duration;
//const int echoPin = A2;

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("SMART PLANT");
  lcd.setCursor(0,1);
  lcd.print("MONITOR SYSTEM !");
  //pinMode(echoPin,INPUT); 
  pinMode(motor, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  delay(2000);
  lcd.clear();
  /*lcd.print("Temp= ");
  lcd.setCursor(0,1);
  lcd.print("WaterPump= ");*/
}

void loop() 
{
  //duration = pulseIn(echoPin, HIGH);
  //distance = (duration*.0343)/2;
  int value = analogRead(LM35);
  float Temperature = value * 500.0 / 1023.0;
  //lcd.setCursor(6,0);
  //lcd.print(Temperature); 
  //lcd.setCursor(11,1);
   // measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(A2, A2);
  Serial.print(cm);
  Serial.println("cm");
  //delay(100); // Wait for 100 millisecond(s)
  //Serial.print("Distance: ");
  //Serial.println(distance);
  //delay(100);
  lcd.clear();
  if(cm < 250)
  {
  	//lcd.clear();
  	lcd.print("T=");
  	lcd.setCursor(0,1);
  	lcd.print("WP=");
  	lcd.setCursor(2,0);
  	lcd.print(Temperature); 
  	lcd.setCursor(3,1);
    
  	if (Temperature > 50)
    {
    	digitalWrite(motor, HIGH);
    	digitalWrite(LedRed, HIGH);
    	digitalWrite(LedGreen, LOW);
    	lcd.print("ON ");
  	}
  	else 
    {
    	digitalWrite(motor, LOW);
    	digitalWrite(LedRed, LOW);
    	digitalWrite(LedGreen, HIGH);
    	lcd.print("OFF");
  	}
    delay(1000);
  	sensorValue = analogRead(A1); // read analog input pin 0
  	if(sensorValue >= 100)
    {
    	//digitalWrite(LED,LOW);
    	Serial.print(sensorValue);
    	Serial.println(" |SMOKE DETECTED");
    	lcd.setCursor(7,1);
    	lcd.print("GAS DETCD");
  	}
 	else
    {
  		//digitalWrite(LED,HIGH);
    	Serial.println("Sensor Value: ");
    	Serial.println(sensorValue);
   		lcd.setCursor(7,1);
    	lcd.print("GAS=");
    	lcd.print(sensorValue);
    	
  	} 
    delay(1500);
  }
  else
  {
	
    lcd.clear();
    lcd.print("Out of Range");
    delay(1000);
  }
}