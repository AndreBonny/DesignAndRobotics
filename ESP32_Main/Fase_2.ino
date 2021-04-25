
void phase2() {
  //Phase 2
  switch (c_state)
  {
    /* Start state
       send #1 and change state
    */
    case READY:
      serial_write(MOV_2);
      c_state = MOVEMENT;
      delay(500);
      break;

    /* Movement state
       Move head while waiting for the END_MOV
    */
    case MOVEMENT:
      data = serial_read();
      if (data.length() > 0 && data == END_MOV_2) {
        //body has finished to move
        ledcAnalogWrite(pan_ch, pan_center);
        
        c_state = SEARCHING;

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
      for (int i = 0; i < 4 && !founded; i++) {
        founded = search_person();
      }

      if (founded) {
        //Serial.printf("founded");
        c_state = TRACKING;
        founded = false;
      }
      else {
        //Serial.printf("NON founded");
        c_state = BACK;
      }

      break;

    /* Second searching state
       Start Face Tracking and cont the cycles where a face is found
    */
    case TRACKING:
      //Serial.printf("Starting tracking");
      serial_write(SPEAK_2);
      ledcAnalogWrite(tilt_ch, tilt_tracking);
      //stop message read inside face_tracking function
      end_t = face_tracking();
      if (end_t == 0) {
        serial_write(STOP_SPEAK_2);
        c_state = SAD;
      }
      else if (end_t == 2) {
        c_state = INGAME;
      }
      else {
        c_state = BACK;
      }

      break;

    case EXPLAINING:
      //Serial.println("EXPLAINING");
      ledcAnalogWrite(tilt_ch, tilt_tracking);
      //stop message read inside face_tracking function
      end_t = face_tracking();
      if (end_t == 0) {
        serial_write(STOP_SPEAK_2);
        c_state = SAD;
      }
      else if ( end_t == 1) {
        c_state = BACK;
      }
      else {
        c_state = BACK;
      }

      break;

    /* End of one complete cycle
       Send RESEt and change state
    */
    case BACK:
      //Serial.println("BACK");
      center_head();
      serial_write(RES_POS_2);
      c_state = WAIT;
      break;


    /* Waiting state, we wait for the end of the RESET,
      wait 1 sec and then go to START
    */
    case WAIT:
      //Serial.println("Wait");
      data = serial_read();
      if (data.length() > 0 && data == END_RES_POS_2) {
        //restart for a new cycle
        delay(5000);
        c_state = READY;
      }
      break;

    case SAD:
      //Serial.println("Sad");
      ledcAnalogWrite(tilt_ch, 110);
      while (serial_read() != END_SPEAK_2) {
        //Wait
      }
      c_state = BACK;
      break;

    case INGAME:
      if(!Inizializza_webserver() && !connected) {
        close_portal();
        serial_write(START_GAME_NO);
        c_state = EXPLAINING;
      } else {
        connected = false;
        serial_write(END_GAME);
        c_state = BACK;
      }
      
      break;

    default:
      break;
  }


}
