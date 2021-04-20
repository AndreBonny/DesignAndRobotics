void fase2(){

String str = serial_read();
  if (str.length() > 0) {
    serial_write_debug("MSG = ");
    serial_write_debug(str);
  }

  if (str == MOV_2) {
    serial_write_debug("Ricevuto MOV");
    delay(20); //sicurezza per  Laser??
    //Movimento Random
    delay(200);
    serial_write(END_MOV_1);
    serial_write_debug("Invio END_MOV");
    draw_openclose();
  }

  if (str == SPEAK_2) {
    //TODO
    //dopo le prime frasi inviare START_GAME
  }


  if (str == RES_POS_2) {
    serial_write_debug("Riccevuto RES_POS");
    draw_openclose();
   //FARE MOVIMENTO INDIETRO??
    delay(200);
    draw_openclose();
    serial_write(END_RES_POS_2);
    serial_write_debug("Invio END_RES_POS");
  }

  if(str == START_GAME_YES){
    //TODO
    //Play Qualcosa

    do{
      str = serial_read();

      if(str == CORRECT_ANSWER){
        //TODO + occhi
      }
      
      if(str == WRONG_ANSWER){
        //TODO + occhi
      }

    }while(str != END_GAME)

    //frase end game + varianti risposte (conta domande giuste e sbagliate)
  }

  if(str == START_GAME_NO){
    //Play informazioni sul museo
    //controlla STOP_SPEAK_2
    //Finisce con END_SPEAK_2
  }

}