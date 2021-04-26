
void phase1() {
  //Phase 1
  switch (c_state)
  {
    /* Start state
       send #1 and change state
    */
    case READY:
      serial_write(MOV_1);
      c_state = SCANNING;
      delay(500);
      break;

    /* Scan state
       Move head while waiting for the END_MOV
    */
    case SCANNING:
      while (scan()) {}
      ledcAnalogWrite(pan_ch, pan_center);
      c_state = LOOKING;
      /*data = serial_read();
      if (data.length() > 0 && data == END_MOV_1) {
        //body has finished to move
        ledcAnalogWrite(pan_ch, pan_center);
        c_state = LOOKING;
        //delay(500);
      }
      else
      {
        scan();
      }*/
      break;

    /* Interaction with rock
    */
    case LOOKING:
      //Messaggio arduino parlare
      serial_write(ROCK_INT);
      while (rock_interaction()) {}
      center_head();
      c_state = SEARCHING;
      break;

    /* Ultrasound search state
       Search if there is something with the US sensor
       then change state according to the result
    */
    case SEARCHING:
      delay(2000);
      for (int i = 0; i < 4 && !founded; i++) {
        founded = search_person();
      }
      if (founded) {
        c_state = TRACKING;
        founded = false;
      }
      else {
        c_state = BACK;
      }

      break;

    /* Second searching state
       Start Face Trackin and cont the cycles where a face is found
    */
    case TRACKING:
      serial_write(SPEAK_1);
      ledcAnalogWrite(tilt_ch, tilt_tracking);
      //stop message read inside face_tracking function
      end_t = face_tracking();

      if (end_t == 1) {
        c_state = BACK;
        delay(200);
      }
      else if (end_t == 0) {
        serial_write(STOP_SPEAK_1);
        c_state = SAD;
      }
      else {
        c_state = BACK;
      }
      break;

    /* End of one complete cycle
       Send RESEt and change state
    */
    case BACK:
      center_head();
      serial_write(RES_POS_1);
      c_state = WAIT;
      break;

    /* Sad because person go away while it's talking

    */
    case SAD:
      ledcAnalogWrite(tilt_ch, 110);
      while (serial_read() != END_SPEAK_1) {
        //Wait
      }
      c_state = BACK;
      break;

    /* Waiting state, we wait for the end of the RESET,
      wait 1 sec and then go to START
    */
    case WAIT:
      data = serial_read();
      if (data.length() > 0 && data == END_RES_POS_1) {
        //restart for a new cycle
        delay(10000);
        c_state = READY;
      }
      break;

    default:
      break;
  }
}
