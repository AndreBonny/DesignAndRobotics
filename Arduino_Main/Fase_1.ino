 void fase1(){

  String str = serial_read();
  if (str.length() > 0) {
    serial_write_debug("MSG = ");
    serial_write_debug(str);
  }
  //----------------------------------------------
  if (str == MOV_1) {
    serial_write_debug("Ricevuto MOV");
    delay(20); //sicurezza per  Laser??
    digitalWrite(LASER_PIN_L, HIGH); //Laser ON
    digitalWrite(LASER_PIN_R, HIGH); //Laser ON
    //Suoni??
    draw_scanning_R();
    draw_scanning_L();
    t = millis();
    while (millis() - t < T_straight) {
      following_forward();
    }
    Stop();
    delay(200);
    serial_write(END_MOV_1);
    serial_write_debug("Invio END_MOV");
    draw_openclose();
  }

  //----------------------------------------------
  if (str == ROCK_INT) {
    serial_write_debug("Ricevuto ROCK_INT");
    play(ROCK_SONG);
    draw_surprised_start();
    delay(5000);
    digitalWrite(LASER_PIN_L, LOW);
    digitalWrite(LASER_PIN_R, LOW);
    draw_surprised_end();
    serial_write_debug("Invio END_ROCK_INT");
  }

  //----------------------------------------------
  if (str == SPEAK_1) {
    bool end_sp = false;

    // Keep playing the track until the thing finishes or we recieve a STOP_SPEAK
    serial_write_debug("Ricevuto SPEAK");
    draw_openclose();
    int noPlayCount = 0;
    Track track = GREETINGS;

    play(track);
    draw_happy_start();
    draw_happy_open();
    delay(1500);
    t = millis();
    do
    {
      if (serial_read() == STOP_SPEAK_1)
      {
        //we read a stop signal from esp
        stop_play();
        play(SADNESS);
        draw_sad_start();
        noPlayCount = 0;
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
          if (millis() - t > 4000)
          {
            t = millis();
            draw_sad_blink();
          }
          delay(500);
        }
        end_sp = true;
        draw_sad_end();
      }
      else
      {
        if (noPlayCount < 2) //margin is needed for false positive when a track starts
        {
          if (dfNotPlaying())
            noPlayCount++;
          if (millis() - t > 4000)
          {
            t = millis();
            if (track < 3)
              draw_happy_blink();
            else
            {
              draw_openclose();
            }
          }
          delay(500);
        }
        else //track ended
        {
          Serial.println("track ended");
          //down here it's track++;
          track = static_cast<Track>(static_cast<int>(track) + 1);
          Serial.print("current track: ");
          Serial.println(track);
          if (track < 5)
          {
            noPlayCount = 0;
            play(track);
            if (track == 3)
            {
              draw_happy_close();
              draw_happy_end();
            }      
          }
          else
          {
            end_sp = true;
          }
        }
      }
    } while (!end_sp);
    
    serial_write(END_SPEAK_1);
    serial_write_debug("Invio END_SPEAK");
  }

  //----------------------------------------------
  if (str == RES_POS_1) {
    serial_write_debug("Riccevuto RES_POS");
    draw_openclose();
    t = millis();
    while (millis() - t < T_straight) {
      following_backward();
    }
    Stop();
    delay(200);
    draw_openclose();
    serial_write(END_RES_POS_1);
    serial_write_debug("Invio END_RES_POS");
  }
  
  //default blinking
  draw_openclose();
}
