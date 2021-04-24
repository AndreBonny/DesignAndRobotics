String data;



void fase1() {
  //Phase 1
  switch (Cstate)
  {
    /* Start state
       send #1 and change state
    */
    case READY:
      serial_write(MOV_1);
      Cstate = SCANNING;
      delay(500);
      break;

    /* Scan state
       Move head while waiting for the END_MOV
    */
    case SCANNING:
      //data = serial_read();
      if (data.length() > 0 && data == END_MOV_1) {
        //body has finished to move
        ledcAnalogWrite(pan_ch, pan_center);
        Cstate = LOOKING;
        //delay(500);
      }
      else
      {
        scan();
      }
      break;


    /* Interaction with rock
    */
    case LOOKING:
      //Messaggio arduino parlare
      serial_write(ROCK_INT);
      do {
        data = serial_read();
        rock();
      } while (data.length() <= 0 || data != END_ROCK_INT);
      center_head();
      Cstate = SEARCHING;
      break;

    /* Ultrasound search state
       Search if there is something with the US sensor
       then change state according to the result
    */
    case SEARCHING:
      delay(1000);
      for (int i = 0; i < 4 && !trovato; i++) {
        trovato = Search();
      }
      if (trovato) {
        // Serial.printf("TROVATO");
        Cstate = TRACKING;
        trovato = false;
      }
      else {
        //Serial.printf("NON TROVATO");
        Cstate = BACK;
      }

      break;

    /* Second searching state
       Start Face Trackin and cont the cycles where a face is found
    */
    case TRACKING:
      //Serial.printf("Starting tracking");
      serial_write(SPEAK_1);
      ledcAnalogWrite(tilt_ch, 160);
      //stop message read inside face_tracking function
      fine = Face_tracking();
      if (fine == 1) {
        Cstate = BACK;
        delay(200);
      }
      else if (fine == 0) {
        serial_write(STOP_SPEAK_1);
        Cstate = SAD;
      }
      else {
        Cstate = BACK;
      }
      break;

    /* End of one complete cycle
       Send RESEt and change state
    */
    case BACK:
      center_head();
      serial_write(RES_POS_1);
      Cstate = WAIT;
      break;

    /* Sad because person go away while it's talking

    */
    case SAD:
      ledcAnalogWrite(tilt_ch, 110);
      while (serial_read() != END_SPEAK_1) {
        //Wait
      }
      Cstate = BACK;
      break;



    /* Waiting state, we wait for the end of the RESET,
      wait 1 sec and then go to START
    */
    case WAIT:
      data = serial_read();
      if (data.length() > 0 && data == END_RES_POS_1) {
        //restart for a new cycle
        delay(10000);
        Cstate = READY;
      }
      break;

    default:
      break;
  }
}
