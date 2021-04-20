const int total_questions = 10;
const int num_questions = 5;
int current_question = 0;

String questions[] = {"question1", "question2", "question3", "question4", "question5", "question6", "question7", "question8", "question9", "question10"};
String answers[] = {"answer1", "answer2", "answer3", "answer4", "answer5", "answer6", "answer7", "answer8", "answer9", "answer10"};

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

  server.on("/style.css", handle_css);
  server.on("/", handle_home_page);

  server.on("/start", handle_question);
  server.on("/next", handle_next);
  server.on("/question", handle_question);
  server.on("/disconnect", handle_disconnect);

  server.on("/background.jpg", []() {
    getSpiffImg("/background.jpg", "image/jpg");
  });

  server.on("/logo_footer.png", []() {
    getSpiffImg("/logo_footer.png", "image/png");
  } );

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
    server.send(404, "text/plain", "I am sorry, there is already someone playing.");
  }
}

void handle_question() {
  current_question++;
  server.send(200, "text/html", sendQuestionPage(current_question, randomQuestions[current_question - 1]));
}

void handle_next() {
  if (current_question < num_questions) {
    server.send(200, "text/html", sendPResults(current_question, "Correct!"));
  } else {
    currentlyConnected = false;
    handle_home_page();
  }
}

void handle_disconnect() {
  if (currentlyConnected) {
    currentlyConnected = false;
    server.send(200, "text/plain", "Disconnected");
    server.close();
    WiFi.disconnect();
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

String sendPResults(int quest_num, String result) {
  String ptr = "";
  ptr += "<!DOCTYPE html>";
  ptr += "<html>";
  ptr += "    <head>";
  ptr += "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\", user-scalable=no>";
  ptr += "        <title>Welcome page</title>";
  ptr += "        <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">";
  ptr += "    </head>";
  ptr += "    <body>";
  ptr += "        <img class=\"background\" src=\"/background.jpg\"/>";
  ptr += "        <main>";
  ptr += "            <div class=\"cover cover-header\">";
  ptr += "                <h2>" + String(quest_num) + ". Question</h3>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-main\">";
  ptr += "                <div class=\"cover__text-blur\">";
  ptr += "                    <div class=\"cover__text\">";
  ptr += "                        <h4>" + result + "</h4>";
  ptr += "                    </div>";
  ptr += "                </div>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-footer\">";
  ptr += "                <a href=\"/question\" class=\"button\"> Next </a>";
  ptr += "            </div>";
  ptr += "        </main>";
  ptr += "    </body>";
  ptr += "    <script type=\"text/javascript\">";
  ptr += "        if(window.innerHeight <= 600) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"10px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"15px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "        if(window.innerHeight >= 1000) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"30px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"45px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "    </script>";
  ptr += "</html>";

  return ptr;

}

String sendQuestionPage(int quest_num, String question) {
  String ptr = "";
  ptr += "<!DOCTYPE html>";
  ptr += "<html>";
  ptr += "    <head>";
  ptr += "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\", user-scalable=no>";
  ptr += "        <title>Welcome page</title>";
  ptr += "        <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">";
  ptr += "    </head>";
  ptr += "    <body>";
  ptr += "        <img class=\"background\" src=\"/background.jpg\"/>";
  ptr += "        <main>";
  ptr += "            <div class=\"cover cover-header\">";
  ptr += "                <h2>" + String(quest_num) + ". Question</h3>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-main\">";
  ptr += "                <div class=\"cover__text-blur\">";
  ptr += "                    <div class=\"cover__text\">";
  ptr += "                        <h4>" + question + "</h4>";
  ptr += "                    </div>";
  ptr += "                </div>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-footer\">";
  ptr += "                <a href=\"/disconnect\" class=\"button\"> False </a>";
  ptr += "                <a href=\"/next\" class=\"button\"> True </a>";
  ptr += "            </div>";
  ptr += "        </main>";
  ptr += "    </body>";
  ptr += "    <script type=\"text/javascript\">";
  ptr += "        if(window.innerHeight <= 600) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"10px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"15px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "        if(window.innerHeight >= 1000) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"30px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"45px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "    </script>";
  ptr += "</html>";

  return ptr;
}

String SendHTML(uint8_t led1stat, uint8_t led2stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Web Server</h1>\n";
  ptr += "<h3>Using Access Point(AP) Mode</h3>\n";

  if (led1stat)
  {
    ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
  }

  if (led2stat)
  {
    ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
