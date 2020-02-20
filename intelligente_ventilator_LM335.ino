int sensorPin = A0;
int sensorVal;
int ventilator = 11;
int ledgroen = 10;
int ledoranje = 9;
int ledrood = 8;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ventilator, OUTPUT);
  pinMode(ledgroen, OUTPUT);
  pinMode(ledoranje, OUTPUT);
  pinMode(ledrood, OUTPUT);
  Serial.begin(9600);

}

void loop() {
int rawvoltage= analogRead(sensorPin);
Serial.println(sensorVal);
sensorVal = analogRead(sensorPin);
float millivolts= (rawvoltage/1024.0) * 5000;
float kelvin= (millivolts/10);

float celsius= kelvin - 273.15;
Serial.print(celsius);
Serial.println(" degrees Celsius");

delay(1000);
if(celsius < 25){
  digitalWrite(ledgroen, HIGH);
  digitalWrite(ledoranje, LOW);
  digitalWrite(ledrood, LOW);
  digitalWrite(ventilator, LOW);
  
}
if(celsius > 25 && celsius < 30){
  digitalWrite(ledoranje, HIGH);
  digitalWrite(ledgroen, LOW);
  digitalWrite(ledrood, LOW);
  analogWrite(ventilator, 155);
  
}
if(celsius > 30){
  digitalWrite(ledrood, HIGH);
  digitalWrite(ledgroen, LOW);
  digitalWrite(ledoranje, LOW);
  digitalWrite(ventilator, HIGH);
  
 
}
}
