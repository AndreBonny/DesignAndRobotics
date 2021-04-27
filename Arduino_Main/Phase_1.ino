

void phase1() {
  int no_play_count = 0;
  String str = serial_read();
  if (str.length() > 0) {
    serial_write_debug("MSG = ");
    serial_write_debug(str);
  }

  /* The ESP has sent the MOV_1 command.
     Arduino will command the motors to move the robot
     following the black line.
     When the movement has ended, send END_MOV_1 to the ESP
  */
  if (str == MOV_1) {
    serial_write_debug("Ricevuto MOV");
    delay(20); //sicurezza per  Laser??
    digitalWrite(LASER_PIN_L, HIGH); //Laser ON
    digitalWrite(LASER_PIN_R, HIGH); //Laser ON
    draw_scanning_R();
    draw_scanning_L();
    t = millis();
    move_forward(400, V);// forward movement to pass the stop line
    while (!following_forward2()) {
      //Follow the line
    }
    Stop();
    delay(200);
    serial_write(END_MOV_1);
    serial_write_debug("Invio END_MOV");
    draw_openclose();
  }


  /* The robot has reached a "point of interest" namenely a rock.
     The ESP has recievd END_MOV_1 and responded with ROCK_INT
     which signals the start of the interaction.
     The interaction now consists in "scanning" the rock with
     the laser ponters and reproducing a track.
     Once the interaction has finished, send END_ROCK_INT to the ESP
  */
  if (str == ROCK_INT) {
    serial_write_debug("Ricevuto ROCK_INT");
    play(ROCK_SONG);
    draw_surprised_start();
    no_play_count = 0;
    while (no_play_count < 2) //check end of track
    {
      if (df_not_playing())
        no_play_count++;
      delay(500);
    }
    digitalWrite(LASER_PIN_L, LOW); //Laser OFF
    digitalWrite(LASER_PIN_R, LOW); //Laser OFF
    draw_surprised_end();
    serial_write(END_ROCK_INT);
    serial_write_debug("Invio END_ROCK_INT");
  }

  /* The ESP has found a person, the robot now needs to speak
     and promote the exibition. If the person leaves the ESP will
     send STOP_SPEAK. In that case the robot will have to show
     sadness. Regardless of any message recieved, at the end of the
     interaction Arduino will have to send END_SPEAK_1
  */
  if (str == SPEAK_1) {
    bool end_sp = false;

    // Keep playing the track until the thing finishes or we recieve a STOP_SPEAK
    serial_write_debug("Ricevuto SPEAK");
    draw_openclose();
    Track track = GREETINGS;
    no_play_count = 0;
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
        Serial.println("Ricevuto stop speak");
        stop_play();
        no_play_count = 0;
        play(SADNESS);
        Serial.println(SADNESS);
        draw_sad_start();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          if (millis() - t > 4000) //timer for blink
          {
            t = millis();
            draw_sad_blink();
          }
          delay(500);
        }
        Serial.println(no_play_count);
        end_sp = true;
        draw_sad_end();
      }
      else
      {
        if (no_play_count < 2) //margin is needed for false positive when a track starts
        {
          if (df_not_playing())
            no_play_count++;
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
          //down here it's track++;
          track = static_cast<Track>(static_cast<int>(track) + 1);
          if (track < 5)
          {
            no_play_count = 0;
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

  /* The ESP has finished tracking the person, now it's required that the robot
     resets (it should be a small movemnt to move past the stopping point).
     Once the movement has ended notify the ESP with the END_RES_POS message.
  */
  if (str == RES_POS_1) {
    serial_write_debug("Riccevuto RES_POS");
    draw_openclose();
    //move_forward(400, V);
    Stop();
    delay(200);
    draw_openclose();
    serial_write(END_RES_POS_1);
    serial_write_debug("Invio END_RES_POS");
  }

  //default blinking
  draw_openclose();
}
