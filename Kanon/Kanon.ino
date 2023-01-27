/*   
 *   Kanon v0.1
 */

#define stepPin 22
#define dirPin 24
#define lowEndStopPin 26

bool sliderBusy = false;
long sliderPos;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(lowEndStopPin, INPUT_PULLUP);
}

void loop() {
  doSerialCommand();
}