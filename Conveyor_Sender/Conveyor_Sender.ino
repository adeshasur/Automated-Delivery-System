#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Sensors
int sensor1Trig = 4;
int sensor1Echo = 3;
int sensor2Trig = 6;
int sensor2Echo = 5;
int irSensor = 2; // NEW: IR sensor pin

// Motor Pins (Conveyor Belt)
int ENB = 9;   // Speed Control
int IN3 = 10;  // Direction 1
int IN4 = A0;  // Direction 2

// Settings
int motorSpeed = 130;    
int emptySpaceWidth = 9;   // Calibration: Wall eka thiyena dura (cm)
int emptySpaceHeight = 12; // Calibration: Uda thiyena dura (cm)

// Box Sizes (Thresholds)
int smallBox = 3;   
int mediumBox = 6;   
int largeBox = 8;    

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Setup Pins
  pinMode(sensor1Trig, OUTPUT); pinMode(sensor1Echo, INPUT);
  pinMode(sensor2Trig, OUTPUT); pinMode(sensor2Echo, INPUT);
  pinMode(irSensor, INPUT);

  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Conveyor System");
  delay(1000);
}

void loop() {
  // 1. IR Sensor Check (Box ekak awada?)
  int irValue = digitalRead(irSensor);

  if (irValue == HIGH) { // Box ekak na (No Obstacle)
    runMotor();          // Belt eka duwanna
    lcd.setCursor(0, 0);
    lcd.print("Waiting for box");
    return;              // Loop eka methanin iwarai
  }

  // 2. Box ekak awa! (IR Low)
  stopMotor();           // Belt eka nawaththanna
  lcd.clear();
  lcd.print("Measuring...");
  delay(1000);           // Box eka nawathina kan inna

  // 3. Measure & Calculate
  int d1 = getDistance(sensor1Trig, sensor1Echo);
  delay(50);
  int d2 = getDistance(sensor2Trig, sensor2Echo);

  int boxWidth = emptySpaceWidth - d1;
  int boxHeight = emptySpaceHeight - d2;
  int maxDim = max(boxWidth, boxHeight); // Loku ma paththa ganna

  // 4. Decision Making (Logic)
  String boxType = "Unknown";
  if (maxDim <= smallBox) { boxType = "Small (A)"; }
  else if (maxDim <= mediumBox) { boxType = "Medium (B)"; }
  else if (maxDim <= largeBox) { boxType = "Large (C)"; }
  else { boxType = "Too Big!"; }

  // 5. Show Result
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Size: "); lcd.print(maxDim); lcd.print("cm");
  lcd.setCursor(0, 1); lcd.print(boxType);
  
  delay(3000); // Result eka balanna 3 seconds denawa
  
  // 6. Box eka ain karanna (Move forward)
  runMotor();
  delay(2000);
}

// --- Helpers ---
void runMotor() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}

void stopMotor() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}