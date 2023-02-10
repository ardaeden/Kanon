/*  SERIAL COMMANDS
 * COMMAND              Cmd   arg1          arg2          arg3                  arg4        arg5
 * ---------------------------------------------------------------------------------------------
 * Move Slide           m     steps         speed         dir (t-top, b-bottom) -           -
 * Home                 h     -             -             -                     -           -
 * Goto Position        g     position      speed
 * report               r
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

    if (args[0] != NULL) {

      // MOVE THE SLIDER
      if (args[0] == "m") {
        byte dir;
        long steps = args[1].toInt();
        int speed = args[2].toInt();
        if (args[3] == "b") dir = BOTTOM;
        if (args[3] == "t") dir = TOP;
        String msg = "Moving slider " + args[3] + ", Steps=" + args[1] + ", Speed=" + args[2];
        Serial.println(msg);
        Serial.println();
        moveSlider(steps, speed, dir);
      }

      // HOME SLIDER
      else if (args[0] == "h") {
        moveSlider(100000, 100, BOTTOM);
        Serial.println(sliderPos);
        Serial.println();
      }

      // GO TO POSITION
      else if (args[0] == "g") {
        long targetPos = args[1].toInt();
        long distance = targetPos - sliderPos;
        byte dir = (distance > 0) ? TOP : BOTTOM;
        String msg = "Moving slider to Pos: " + args[1] + ", Steps=" + abs(distance) + ", Speed=" + args[2] + ", Direction=" + ((dir == TOP) ? "TOP" : "BOTTOM");
        Serial.println(msg);
        Serial.println();
        moveSlider(abs(distance), args[2].toInt(), dir);
      }
      
      else if (args[0] == "gr") {
        float tp = 192000 * (1.0 - (float)args[2].toInt() / (float)args[1].toInt());
        Serial.print("Target Position: ");
        Serial.println(tp);
        long targetPos = (long)tp;
        long distance = targetPos - sliderPos;
        byte dir = (distance > 0) ? TOP : BOTTOM;
        //String msg = "Steps=" + abs(distance) + ", Speed=" + args[2] + ", Direction=" + ((dir == TOP) ? "TOP" : "BOTTOM");
        //Serial.println(msg);
        //Serial.println();
        moveSlider(abs(distance), args[3].toInt(), dir);
      }

      //SHOW REPORT
      else if (args[0] == "r") {
        Serial.println("KANON SYSTEM REPORT");
        Serial.println("-------------------");
        Serial.print("BOTTOM is defined as: ");
        Serial.println((BOTTOM == 1) ? "HIGH" : "LOW");
        Serial.print("TOP is defined as: ");
        Serial.println((TOP == 1) ? "HIGH" : "LOW");
        Serial.print("Current slider position is: ");
        Serial.println(sliderPos);
        Serial.println();
      }

      else {
        Serial.println("Unrecognized command!");
        Serial.println();
      }

      // CLEAR ALL ARGUMENTS
      for (int i = 0; i < 5; i++) {
        args[i] = "";
      }
    }
  }
}