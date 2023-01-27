void moveSlider(long steps, int speed, byte direction) {
  if (!sliderBusy) {
    sliderBusy = true;
    digitalWrite(dirPin, direction);
    for (long x = 0; x < steps; x++) {
      if (digitalRead(lowEndStopPin) != LOW) {
        sliderPos += (direction ? 1 : -1);
        //speed = sliderPos < 0 ? 1000 : speed; //Override speed for negative sliderPos values
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(speed);
      } else {
        delay(500);
        sliderSetHomePos();
        break;
      }
    }
  }

  sliderBusy = false;
  Serial.print("Slider position: ");
  Serial.println(sliderPos);
}

void sliderSetHomePos() {
  digitalWrite(dirPin, HIGH);
  for (long x = 0; x < 600; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1500);
  }

  sliderPos = 0;
}