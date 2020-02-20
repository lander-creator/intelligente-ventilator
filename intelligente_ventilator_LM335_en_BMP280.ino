#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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
                                                                                      // Oled display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
  delay(2000);

  
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
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("temperatuur LM335: ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println(celsius);
  

 sensors_event_t temp_event, pressure_event;   // digitale sensor BMP
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");
  
  Serial.println();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.println("temperatuur BMP280: ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 40);
  display.println(temp_event.temperature);
  display.display();
}
