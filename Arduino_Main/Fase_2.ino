void fase2() {

  int noPlayCount;
  Track track;
  bool end_sp;

  String str = serial_read();
  if (str.length() > 0) {
    serial_write_debug("MSG = ");
    serial_write_debug(str);
  }
  //----------------------------------------------
  if (str == MOV_2) {
    serial_write_debug("Ricevuto MOV");
    delay(20); //sicurezza per  Laser??
    //Movimento Random
    delay(200);
    serial_write(END_MOV_2);
    serial_write_debug("Invio END_MOV");
    draw_openclose();
  }
  //----------------------------------------------
  if (str == SPEAK_2) {

    track = GAME_PROPOSAL;
    noPlayCount = 0;
    //PLAY GAME_PROPOSAL

    play(track);

    draw_question_start();

    t = millis();
    while (noPlayCount < 2) //check end of track
    {
      if (dfNotPlaying())
        noPlayCount++;
      delay(50);
    }
    draw_question_end();


    track = GAME_START_INSTRUCTION;
    noPlayCount = 0;
    //PLAY GAME_START_INSTRUCTION
    play(track);
    draw_openclose();


    while (noPlayCount < 2) //check end of track
    {
      if (dfNotPlaying())
        noPlayCount++;
      if (millis() - t > 4000) //timer between each blink
      {
        t = millis();
        draw_openclose();
      }
      delay(50);
    }

    //send START_GAME to ESP to move to next phases
    serial_write(START_GAME);
  }

  //----------------------------------------------
  if (str == RES_POS_2) {
    serial_write_debug("Riccevuto RES_POS");
    draw_openclose();
    //FARE MOVIMENTO INDIETRO??
    delay(200);
    draw_openclose();
    serial_write(END_RES_POS_2);
    serial_write_debug("Invio END_RES_POS");
  }

  //----------------------------------------------
  if (str == START_GAME_YES) {

    int correct_answers = 0;
    int wrong_answers = 0;
    int tot_answers;

    track = INTRODUCTION_PHRASE;
    noPlayCount = 0;
    //PLAY INTRODUCTION_PHRASE
    play(track);
    while (noPlayCount < 2) //check end of track
    {
      if (dfNotPlaying())
        noPlayCount++;
      if (millis() - t > 4000) //timer between each blink
      {
        t = millis();
        draw_openclose();
      }
      delay(50);
    }

    do {

      str = serial_read();
      if (str == CORRECT_ANSWER)
      {
        track = CORRECT_PHRASE;
        noPlayCount = 0;
        //PLAY CORRECT_PHRASE
        play(track);
        draw_correct_eye_start();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
          delay(50);
        }
        correct_answers++;
        draw_correct_eye_end();
      }

      if (str == WRONG_ANSWER)
      {
        track = WRONG_PHRASE;
        noPlayCount = 0;
        //PLAY WRONG_PHRASE
        play(track);
        draw_wrong_eye_start();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
          delay(50);
        }
        wrong_answers++;
        draw_wrong_eye_end();
      }

    } while (str != END_GAME);

    if (correct_answers + wrong_answers == 0)
    {
      //recieved END_GAME before any answer was submitted
      Serial.println("recieved END_GAME before any answer was submitted");

    }
    else
    {
      tot_answers = (correct_answers / (correct_answers + wrong_answers)) * 100;

      track = LETS_SEE;
      noPlayCount = 0;
      // PLAY LETS_SEE
      play(track);
      while (noPlayCount < 2) //check end of track
      {
        if (dfNotPlaying())
          noPlayCount++;
        if (millis() - t > 4000) //timer between each blink
        {
          t = millis();
          draw_openclose();
        }
        delay(50);
      }

      if (tot_answers <= 25) //very bad  //NEEDS ANGRY EYES ________________________________________________
      {
        track = VERY_BAD;
        noPlayCount = 0;
        //PLAY VERY_BAD
        play(track);
        draw_angry_start();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_angry_blink();
          }
          delay(50);
        }
        draw_angry_end();

      }
      else if (tot_answers > 25) //bad
      {

        track = BAD;
        noPlayCount = 0;
        //PLAY BAD
        play(track);
        draw_sad_start();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
          if (millis() - t > 4000) //timer between each blink
          {
            t = millis();
            draw_sad_blink();
          }
          delay(50);
        }
        draw_sad_end();
      }
      else if (tot_answers > 50)//good
      {
        track = GOOD;
        noPlayCount = 0;
        //PLAY GOOD
        play(track);
        draw_happy_start();
        draw_happy_open();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
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
      else if (tot_answers > 75 || tot_answers < 95) //very good // NEED EYES_____________________________________________
      {

        track = VERY_GOOD;
        noPlayCount = 0;
        //PLAY VERY_GOOD
        play(track);
        draw_happy_start();
        draw_happy_open();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
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
        noPlayCount = 0;
        //PLAY PERFECT
        play(track);
        draw_happy_start();
        draw_happy_open();
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
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

  //----------------------------------------------

  if (str == START_GAME_NO) {
    //Play informazioni sul museo
    //controlla STOP_SPEAK_2
    //Finisce con END_SPEAK_2

    noPlayCount = 0;
    track = FACTS_1;
    end_sp = false;
    //prepare a new random fact

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
        noPlayCount = 0;
        while (noPlayCount < 2) //wait for the ende of the track
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
