/*  SERIAL COMMANDS
 *                      Cmd   arg1          arg2          arg3                  arg4        arg5
 * Move Slide           m     steps         speed         dir (h-high, l-low)   -           -
 * Home                 h     -             -             -                     -           -
 */

String args[5];

void doSerialCommand() {
  if (Serial.available()) {
    String message = "";
    byte argIndex = 0;
    message = Serial.readString();
    message.trim();
    for (int i = 0; i < message.length(); i++) {
      if (message[i] == ' ') {
        argIndex++;
        i++;
      }
      args[argIndex] += message[i];
    }

    // Serial.print(args[0]);
    // Serial.print(" ");
    // Serial.print(args[1]);
    // Serial.print(" ");
    // Serial.print(args[2]);
    // Serial.print(" ");
    // Serial.print(args[3]);
    // Serial.print(" ");
    // Serial.println(args[4]);
    // Serial.println();

    if (args[0] != NULL) {

      // MOVE THE SLIDER
      if (args[0] == "m") {
        byte dir;
        long steps = args[1].toInt();
        int speed = args[2].toInt();
        if (args[3] == "h") dir = HIGH;
        if (args[3] == "l") dir = LOW;
        String msg = "Moving slider " + args[3] + ", Steps=" + args[1] + ", speed=" + args[2];
        Serial.println(msg);
        moveSlider(steps, speed, dir);
      }

      // HOME SLIDER
      else if (args[0] == "h") {
        moveSlider(50000, 500, LOW);
      }


      else {
        Serial.println("Unrecognized command!");
      }


      // CLEAR ALL ARGUMENTS
      for (int i = 0; i < 5; i++) {
        args[i] = "";
      }
    }
  }
}