void handle_css() {
  server->send(200, "text/css", sendCss());
}

void handle_home_page() {
  current_question = 0;
  connected = true;
  
  serial_write(START_GAME_YES);
  center_head();
  
  initialize_random_questions();
  
  server->send(200, "text/html", sendHomePage());
}

void handle_question() {
  // if there are other questions to do
  if (current_question < num_questions) {
    current_question++;
    server->send(200, "text/html", sendQuestionPage(current_question, randomQuestions[current_question - 1]));
  } else {
    delay(50);
    serial_write(END_GAME);
    server->send(200, "text/html", sendFinalResults(num_correct, num_questions));
  }
}

void handle_false() {
  check_answer("False");
}

void handle_true() {
  check_answer("True");
}

void check_answer(String ans) {
  if (randomAnswers[current_question - 1] == ans) {
    num_correct++;
    handle_next("Correct!");
    serial_write(CORRECT_ANSWER);
  } else {
    handle_next("Wrong!");
    serial_write(WRONG_ANSWER);
  }
}

void handle_next(String res) {
  server->send(200, "text/html", sendPResults(current_question, res));
}

void handle_disconnect() {
  delay(1000);
  delay(50);
  serial_write(END_GAME);
  close_portal();
}

void handle_not_found() {
  server->send(404, "text/plain", "Not found");
}
