#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Setup (Address 0x27 is common)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Show Start Message
  lcd.setCursor(0, 0);
  lcd.print("System Booting..");
  delay(2000);
  
  lcd.clear();
  lcd.print("Conveyor Ready");
}

void loop() {
  // LCD On Only Nothing Display
}