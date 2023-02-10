/*   
 *   Kanon v0.1
 */

#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define stepPin 22
#define dirPin 24
#define lowEndStopPin 26
#define BOTTOM HIGH
#define TOP LOW

bool sliderBusy = false;
long sliderPos;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);

  pinMode (BACKLIGHT_PIN, OUTPUT);
  digitalWrite (BACKLIGHT_PIN, LOW);
  lcd.begin(16,2);
  lcd.home();
  lcd.print("KANON v0.1");

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(lowEndStopPin, INPUT_PULLUP);
}

void loop() {
  doSerialCommand();
}