
int inited = 0;

void fase2() {
  //Phase 2
  switch (Cstate)
  {
    /* Start state
       send #1 and change state
    */
    case READY:
      serial_write(MOV_2);
      Cstate = MOVEMENT;
      delay(500);
      break;

    /* Movement state
       Move head while waiting for the END_MOV
    */
    case MOVEMENT:
      //data = serial_read();
      if (data.length() > 0 && data == END_MOV_2) {
        //body has finished to move
        ledcAnalogWrite(pan_ch, pan_center);
        Cstate = SEARCHING;
        //delay(500);
      }
      else
      {
        /*ledcAnalogWrite(pan_ch,70);
          delay(200);
          ledcAnalogWrite(pan_ch,pan_center);
          delay(200);
          ledcAnalogWrite(pan_ch,130);
          delay(200);*/
      }
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
       Start Face Tracking and cont the cycles where a face is found
    */
    case TRACKING:
      //Serial.printf("Starting tracking");
      serial_write(SPEAK_2);
      ledcAnalogWrite(tilt_ch, 160);
      //stop message read inside face_tracking function
      fine = Face_tracking();
      if (fine == 0) {
        serial_write(STOP_SPEAK_2);
        Cstate = SAD;
      }
      else if ( fine == 2) {
        Cstate = INGAME;
      }
      else {
        Cstate = BACK;
      }

      break;

    case EXPLAINING:
      ledcAnalogWrite(tilt_ch, 160);
      //stop message read inside face_tracking function
      fine = Face_tracking();
      if (fine == 0) {
        serial_write(STOP_SPEAK_2);
        Cstate = SAD;
      }
      else if ( fine == 1) {
        Cstate = BACK;
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
      serial_write(RES_POS_2);
      Cstate = WAIT;
      break;


    /* Waiting state, we wait for the end of the RESET,
      wait 1 sec and then go to START
    */
    case WAIT:
      data = serial_read();
      if (data.length() > 0 && data == END_RES_POS_2) {
        //restart for a new cycle
        delay(5000);
        Cstate = READY;
      }
      break;

    case SAD:
      ledcAnalogWrite(tilt_ch, 110);
      while (serial_read() != END_SPEAK_2) {
        //Wait
      }
      Cstate = BACK;
      break;

    case INGAME:
      if (!inited) {
        Inizializza_webserver();
        //Serial.println("Waiting for connection");
        inited = 1;
      }
      Portal.begin();
      Portal.handleClient();
      break;

    default:
      break;
  }


}
