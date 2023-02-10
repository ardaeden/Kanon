/*
* All actions of sliders are coded here
*/

void moveSlider(long steps, int speed, byte direction) {
  if (sliderBusy == false) {
    sliderBusy = true;
    sliderPos += (steps * (direction ? -1 : 1));
    steps = steps * 0.995;
    //Serial.println(steps);
    digitalWrite(dirPin, direction);
    for (long x = 0; x < steps; x++) {
      if (digitalRead(lowEndStopPin) != LOW) {
        //sliderPos += (direction ? -1 : 1);
        //speed = sliderPos < 0 ? 1000 : speed; //Override speed for negative sliderPos values
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      } else {
        //If endstop is reached, stop, wait and set slider to home position
        delay(100);
        sliderSetHomePos();
        break;
      }
    }
  }

  sliderBusy = false;
  // Serial.print("Slider position: ");
  // Serial.println(sliderPos);
  // Serial.println();
}

void sliderSetHomePos() {
  digitalWrite(dirPin, TOP);
  for (long x = 0; x < 600; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1500);
  }
  sliderPos = 0;
}