WebServer* server;
AutoConnect* Portal;

const int total_questions = 13;
const int num_questions = 7;
int current_question = 0;

int num_correct;

String questions[] = {
  "The first U.S. space shuttle has been launched in 1975?",                            // 1
  "Was Sputnik the first artificial satellite?",                                        // 2
  "Was Neil Armstrong the first to go on a spacewalk?",                                 // 3
  "Do astronauts \"grow\" of few inches in space?",                                     // 4
  "Was Apollo 1 the first of NASA's manned flights into space?",                        // 5
  "Was the first person in space from the United States?",                              // 6
  "NASA was founded in 1958?",                                                          // 7
  "NASA stands for the National Aeronautics and Space Administration?",                 // 8
  "Was Yuri Gagarin the first human to orbit Earth?",                                   // 9
  "Was Neil Diamond the first human on the moon?",                                      // 10
  "If you step on the Moon, those footprints will be there more or less indefinitely",  // 11
  "In the space there are not any sounds that can be heard by humans.",                 // 12
  "The nearest galaxy to Milky Way is Andromeda?",                                      // 13
};

String answers[] = {
  "False",  // 1
  "True",   // 2
  "False",  // 3
  "True",   // 4
  "False",  // 5
  "False",  // 6
  "True",   // 7
  "True",   // 8
  "True",   // 9
  "False",  // 10
  "True",   // 11
  "False",  // 12
  "True",   // 13
};

String randomQuestions[num_questions];
String randomAnswers[num_questions];

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

int initialize_webserver() {

  // Serial.println("Entering webserver");
  
  connected = false;
  server = new WebServer(80);
  Portal = new AutoConnect(*server);
  
  //WiFi.mode(WIFI_AP);
  
  // Serial.println("Initializing webserver");

  num_correct = 0;

  server->on("/style.css", handle_css);
  server->on("/", handle_home_page);
  server->on("/start", handle_question);
  server->on("/false", handle_false);
  server->on("/true", handle_true);
  server->on("/question", handle_question);
  server->on("/disconnect", handle_disconnect);

  server->on("/background.jpg", []() {
    getSpiffImg("/background.jpg", "image/jpg");
  });

  server->on("/logo_footer.png", []() {
    getSpiffImg("/logo_footer.png", "image/png");
  });

  server->onNotFound(handle_not_found);

  configure_portal();
  
  return Portal->begin();
}

void configure_portal() {
  AutoConnectConfig  Config("Steeve", "");

  Config.portalTimeout = 20000;
  Config.immediateStart = true;
  Config.autoRise = true;
  Config.autoReset = true;
  Config.bootUri = AC_ONBOOTURI_ROOT;
  Portal->config(Config);                        // Configure AutoConnect
}

void getSpiffImg(String path, String TyPe) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    server->streamFile(file, TyPe);
    file.close();
  }
}

void close_portal() {
  Portal->end();
  server->close();

  //delete Portal;
  //delete server;
  
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}
