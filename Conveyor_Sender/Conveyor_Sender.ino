#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- NEW: Sensor Pins Define Kala ---
int sensor1Trig = 4; // Palala (Width) manina sensor eka
int sensor1Echo = 3;
int sensor2Trig = 6; // Usa (Height) manina sensor eka
int sensor2Echo = 5;

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // --- NEW: Pins Setup ---
  pinMode(sensor1Trig, OUTPUT); // Signal yawana pin eka
  pinMode(sensor1Echo, INPUT);  // Signal receive karana pin eka
  pinMode(sensor2Trig, OUTPUT);
  pinMode(sensor2Echo, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Sensors Active");
  delay(1000);
  lcd.clear();
}

void loop() {
  // --- NEW: Distance Manina Kotasa ---
  
  // Sensor 1 (Width)
  int dist1 = getDistance(sensor1Trig, sensor1Echo);
  
  // Sensor 2 (Height)
  int dist2 = getDistance(sensor2Trig, sensor2Echo);

  // Serial Monitor eke balanna (Debugging walata)
  Serial.print("Width Sensor: "); Serial.print(dist1);
  Serial.print(" cm | Height Sensor: "); Serial.println(dist2);

  // LCD eke pennanna
  lcd.setCursor(0, 0);
  lcd.print("W: "); lcd.print(dist1); lcd.print("cm   ");
  
  lcd.setCursor(0, 1);
  lcd.print("H: "); lcd.print(dist2); lcd.print("cm   ");
  
  delay(500); // 0.5 sec indala aye maninawa
}

// --- NEW: Helper Function (Code eka clean thiyaganna) ---
int getDistance(int trigPin, int echoPin) {
  // 1. Trigger pin eka reset karanawa
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // 2. Sound wave ekak yawanawa (10 microseconds)
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Wave eka wadila enna yana welawa maninawa
  long duration = pulseIn(echoPin, HIGH);
  
  // 4. Welawa dura bawata harawanawa (Time x Speed of Sound / 2)
  int distance = duration * 0.034 / 2;
  
  return distance;
}