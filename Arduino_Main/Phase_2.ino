void phase2() {

  int no_play_count;
  Track track;
  bool end_sp;

  String str = serial_read();
  if (str.length() > 0) {
    serial_write_debug("MSG = ");
    serial_write_debug(str);
  }

  /* Once the ESP sends the MOV_2 commnad the robot should start moving randomly in the
     designed space. Once a border has been reached the robot will stop and
     Arduino will send the END_MOV_2 message
  */
  if (str == MOV_2) {
    serial_write_debug("Ricevuto MOV");
    //Movimento Random
    moveRandom();
    /* while (!following_forward()) {
       //Follow the line
      }*/
    Stop();
    delay(200);
    serial_write(END_MOV_2);
    serial_write_debug("Invio END_MOV");
    draw_openclose();
  }

  /* The ESP has found someone, the robot has to propose the game and comunicate how
     to start it once the explenation has finished send START_GAME to the ESP
  */
  if (str == SPEAK_2) {

    track = GAME_PROPOSAL;
    no_play_count = 0;
    //PLAY GAME_PROPOSAL

    play(track);

    draw_question_start();
    t = millis();
    while (no_play_count < 2) //check end of track
    {
      if (df_not_playing())
        no_play_count++;
      delay(50);
    }
    draw_question_end();

    serial_write(START_GAME);
    track = GAME_START_INSTRUCTION;
    no_play_count = 0;
    //PLAY GAME_START_INSTRUCTION
    play(track);
    draw_openclose();


    while (no_play_count < 2) //check end of track
    {
      if (df_not_playing())
        no_play_count++;
      if (millis() - t > 4000) //timer between each blink
      {
        t = millis();
        draw_openclose();
      }
      delay(50);
    }

    //send START_GAME to ESP to move to next phases

  }

  /* In a similar way as in phase 1, once all the interactions have ended
     prepare for a new cycle.
     Once it's finished send END_RES_POS_2
  */
  if (str == RES_POS_2) {
    serial_write_debug("Riccevuto RES_POS");
    draw_openclose();
    move_backward(T_back,V);
    //move_forward(400, V);
    Stop();
    delay(200);
    draw_openclose();
    serial_write(END_RES_POS_2);
    serial_write_debug("Invio END_RES_POS");
  }

  /* Someone has connected to the ESP to play the game.
     Arduino now has to react (with voice and eyes) to the
     each wrong (ESP sends WRONG_ANSWER) and correct answer (ESP sends CORRECT_ANSWER).
     Once the game has finished the ESP sends END_GAME.
     The robot now has to evaluate the performance on the quiz.
     Once the interaction has finished Arduino sends END_SPEAK_2 to the ESP
  */

  if (str == START_GAME_YES) {

    double correct_answers = 0;
    double wrong_answers = 0;
    double tot_answers;

    track = INTRODUCTION_PHRASE;
    no_play_count = 0;
    //PLAY INTRODUCTION_PHRASE

    play(track);
    while (no_play_count < 2) //check end of track
    {
      if (df_not_playing())
        no_play_count++;
      if (millis() - t > 4000) //timer between each blink
      {
        t = millis();
        draw_openclose();
      }
      delay(50);
    }

    do
    {
      str = serial_read();
      Serial.println(str);
      if (str == CORRECT_ANSWER)
      {
        track = CORRECT_PHRASE;
        no_play_count = 0;
        //PLAY CORRECT_PHRASE
        play(track);
        draw_correct_eye_start();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          delay(50);
        }
        correct_answers++;
        draw_correct_eye_end();
      }

      if (str == WRONG_ANSWER)
      {
        track = WRONG_PHRASE;
        no_play_count = 0;
        //PLAY WRONG_PHRASE
        play(track);
        draw_wrong_eye_start();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          delay(50);
        }
        wrong_answers++;
        draw_wrong_eye_end();
      }

    } while (str != END_GAME);
    Serial.println("ricevuto end game");
    Serial.println(correct_answers + wrong_answers);
    if (correct_answers + wrong_answers == 0)
    {
      //recieved END_GAME before any answer was submitted
      Serial.println("recieved END_GAME before any answer was submitted");

    }
    else
    {
      tot_answers = (correct_answers / (correct_answers + wrong_answers)) * 100;
      Serial.println(tot_answers);
      track = LETS_SEE;
      no_play_count = 0;
      // PLAY LETS_SEE
      play(track);
      while (no_play_count < 2) //check end of track
      {
        if (df_not_playing())
          no_play_count++;
        if (millis() - t > 4000) //timer between each blink
        {
          t = millis();
          draw_openclose();
        }
        delay(50);
      }

      if (tot_answers <= 25) //very bad
      {
        track = VERY_BAD;
        no_play_count = 0;
        //PLAY VERY_BAD
        play(track);
        draw_angry_start();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_angry_blink();
          }
          delay(50);
        }
        draw_angry_end();

      }
      else if (tot_answers > 25 && tot_answers < 50) //bad
      {

        track = BAD;
        no_play_count = 0;
        //PLAY BAD
        play(track);
        draw_sad_start();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_sad_blink();
          }
          delay(50);
        }
        draw_sad_end();
      }
      else if (tot_answers >= 50 && tot_answers < 75)//good
      {
        track = GOOD;
        no_play_count = 0;
        //PLAY GOOD
        play(track);
        draw_happy_start();
        draw_happy_open();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_happy_blink();
          }
          delay(50);
        }
        draw_happy_close();
        draw_happy_end();
      }
      else if (tot_answers >= 75 && tot_answers < 95) //very good
      {

        track = VERY_GOOD;
        no_play_count = 0;
        //PLAY VERY_GOOD
        play(track);
        draw_happy_start();
        draw_happy_open();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_happy_blink();
          }
          delay(50);
        }
        draw_happy_close();
        draw_happy_end();
      }
      else //perfect
      {
        track = PERFECT;
        no_play_count = 0;
        //PLAY PERFECT
        play(track);
        draw_happy_start();
        draw_happy_open();
        while (no_play_count < 2) //check end of track
        {
          if (df_not_playing())
            no_play_count++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_happy_blink();
          }
          delay(50);
        }
        draw_happy_close();
        draw_happy_end();
      }
    }

    //notify the ESP that arduino has finished speaking
    serial_write(END_SPEAK_2);
  }


  /* The visitor will not play the game but it's still in the proximity of the robot.
     The robot will then play a random "space fact" tacken from a pool of tracks.
     As in phase 1, if the visitor gets away from the robot the ESP will send
     STOP_SPEAK to the Arduino.
  */

  if (str == START_GAME_NO) {
    //Play informazioni sul museo
    //controlla STOP_SPEAK_2
    //Finisce con END_SPEAK_2

    no_play_count = 0;
    end_sp = false;
    //prepare a new random fact (between 0011 and  0015)
    track = static_cast<Track>(random(11, 15));

    play(track);
    draw_happy_start();
    draw_happy_open();
    delay(100);
    do
    {
      if (serial_read() == STOP_SPEAK_2) //the person has moved
      {
        //we read a stop signal from esp
        stop_play();
        play(SADNESS);
        draw_sad_start();
        no_play_count = 0;
        while (no_play_count < 2) //wait for the ende of the track
        {
          if (df_not_playing())
            no_play_count++;
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
        if (no_play_count < 2) //margin is needed for false positive when a track starts
        {
          if (df_not_playing())
            no_play_count++;
          draw_happy_blink();
          delay(500);
        }
        else //track ended
        {
          end_sp = true;
          draw_happy_close();
          draw_happy_end();
        }
      }
    } while (!end_sp);

    serial_write(END_SPEAK_2);
    serial_write_debug("Invio END_SPEAK");
  }

}
