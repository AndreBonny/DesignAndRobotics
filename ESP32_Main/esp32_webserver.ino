const int total_questions = 10;
const int num_questions = 5;
int current_question = 0;

int num_correct;

String questions[] = {"question1", "question2", "question3", "question4", "question5", "question6", "question7", "question8", "question9", "question10"};
String answers[] = {"True", "True", "False", "True", "False", "False", "False", "True", "True", "False"};

String randomQuestions[num_questions];
String randomAnswers[num_questions];

bool currentlyConnected;
IPAddress connectedIP;

int contains(int *indexes, int num, int leng) {
  for (int i = 0; i < leng; i++) {
    if (indexes[i] == num)
      return 1;
  }
  return 0;
}

int* get_random_indexes(int length, int upper_bound) {
  int* indexes = (int*) malloc(length * sizeof(int));
  for (int i = 0; i < length; i++)
    indexes[i] = -1;
  if (length > upper_bound) {
    printf("Invalid! You are requesting more numbers than the upper_bound");
    return indexes;
  }

  int last_index = 0;
  while (contains(indexes, -1, length)) {
    //int num = (rand() % (upper_bound - 0)) + 0;
    int num = random(upper_bound);
    if (!contains(indexes, num, length)) {
      indexes[last_index] = num;
      last_index++;
    }
  }
  return indexes;
}

void initialize_random_questions() {
  int* indexes = get_random_indexes(num_questions, total_questions);
  for (int i = 0; i < num_questions; i++) {
    randomQuestions[i] = questions[indexes[i]];
    randomAnswers[i] = answers[indexes[i]];
  }
}

void onConnect(IPAddress& ipaddr) {
  Serial.print("WiFi connected with ");
  Serial.print(WiFi.SSID());
  Serial.print(", IP:");
  Serial.println(ipaddr.toString());
  connectedIP = ipaddr;
}

void Inizializza_webserver() {
  currentlyConnected = false;
  WiFi.mode(WIFI_AP);

  // Initialize SPIFFS for file system
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  num_correct = 0;

  server.on("/style.css", handle_css);
  server.on("/", handle_home_page);

  server.on("/start", handle_question);
  server.on("/false", handle_false);
  server.on("/true", handle_true);
  server.on("/question", handle_question);
  server.on("/disconnect", handle_disconnect);

  server.on("/background.jpg", []() {
    getSpiffImg("/background.jpg", "image/jpg");
  });

  server.on("/logo_footer.png", []() {
    getSpiffImg("/logo_footer.png", "image/png");
  });

  server.onNotFound(handle_NotFound);

  configure_portal();
  Serial.println("HTTP server started");
}

void configure_portal() {
  AutoConnectConfig  Config("MuseumRobot", "");

  Config.autoReconnect = true;                  // Enable auto-reconnect
  Config.autoSave = AC_SAVECREDENTIAL_NEVER;    // No save credential
  Config.boundaryOffset = 64;                   // Reserve 64 bytes for the user data in EEPROM.
  Config.portalTimeout = 60000;                 // Sets timeout value for the captive portal
  Config.retainPortal = true;                   // Retains the portal function after timed-out
  Config.homeUri = "/";                         // Sets home path of Sketch application
  Config.title = "My menu";                     // Customize the menu title

  Portal.onConnect(onConnect);
  Portal.config(Config);                        // Configure AutoConnect
}

void getSpiffImg(String path, String TyPe) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, TyPe);
    file.close();
  }
}

void handle_css() {
  handle_page("/style.css", true);
}

void handle_home_page() {
  if (!currentlyConnected) {
    currentlyConnected = true;
    current_question = 0;

    initialize_random_questions();
    for (int i = 0; i < num_questions; i++) {
      Serial.print("Question #" + String(i) + " ");
      Serial.println(randomQuestions[i]);
      Serial.print("Answer #" + String(i) + " ");
      Serial.println(randomAnswers[i]);
    }
    Serial.println("Home page");
    handle_page("/home_p.html", false);
  } else {
    handle_page("/busy.html", false);
  }
}

void handle_question() {
  if (current_question < num_questions) {
    current_question++;
    server.send(200, "text/html", sendQuestionPage(current_question, randomQuestions[current_question - 1]));
  } else {
    server.send(200, "text/html", sendFinalResults(num_correct, num_questions));
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
  } else {
    handle_next("Wrong!");
  }
}

void handle_next(String res) {
  server.send(200, "text/html", sendPResults(current_question, res));
}

void handle_disconnect() {
  if (currentlyConnected) {
    handle_page("/disconnected.html", false);
    delay(1000);
    Portal.end();
    currentlyConnected = false;
    server.close();
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    inited = 0;
    Cstate = BACK;
  }
  currentlyConnected = false;
}

void handle_page(String page_name, bool is_css) {
  File file = SPIFFS.open(page_name, "r");
  String page = "";
  if (file) {
    while (file.available()) {
      page += (char)file.read();
    }
    if (is_css)
      server.send(200, "text/css", page);
    else
      server.send(200, "text/html", page);
  } else
    Serial.println("Failed to get page");
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
