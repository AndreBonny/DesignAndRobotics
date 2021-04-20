

/* Put your SSID & Password */
const char* ssid = "esp32ap";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

const byte DNS_PORT = 53;

/* Put IP Address details */
//IPAddress local_ip(192,168,1,1);
IPAddress local_ip(8, 8, 4, 4);
//IPAddress gateway(192,168,1,1);
IPAddress gateway(8, 8, 4, 4);
IPAddress subnet(255, 255, 255, 0);

uint8_t LED1pin = 4;
bool LED1status = LOW;

uint8_t LED2pin = 5;
bool LED2status = LOW;

String prova(const String& var) {
  return "ciao";
}

void Inizializza_webserver() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);//, 0, 0, 1); // ssid, password, channel, ssid_hidden, max_connection
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  // Initialize SPIFFS for file system
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  server.on("/style.css", handle_css);
  server.on("/", handle_home_page);
  server.on("/start", handle_first_question);

  server.on("/background.jpg", []() { getSpiffImg("/background.jpg", "image/jpg"); });
  server.on("/logo_footer.png", []() { getSpiffImg("/logo_footer.png", "image/png"); } );

  /*server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/home_page.html", "text/html", false, prova);
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css", false, NULL);
  });

  server.on("/begin", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/first_question.html", "text/html", false, NULL);
  }

  server.on("/background", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/background.jpg", "image/jpeg");
  });*/
  
  server.onNotFound(handle_NotFound);

  //dnsServer.start(DNS_PORT, "*", local_ip);
  configure_portal();
  //Portal.begin();
  //server.begin();
  Serial.println("HTTP server started");
}

void configure_portal() {
  // esp32ap
  AutoConnectConfig  Config("", "");    // SoftAp name is determined at runtime

  Config.autoReconnect = true;                  // Enable auto-reconnect
  Config.autoSave = AC_SAVECREDENTIAL_NEVER;    // No save credential
  Config.boundaryOffset = 64;                   // Reserve 64 bytes for the user data in EEPROM.
  Config.portalTimeout = 60000;                 // Sets timeout value for the captive portal
  Config.retainPortal = true;                   // Retains the portal function after timed-out
  Config.homeUri = "/";               // Sets home path of Sketch application
  Config.title = "My menu";                     // Customize the menu title

  //AutoConnectAux aux("/mqtt_settings", "MQTT_SETTINGS");
  //ACText(header, "MQTT broker settings");
  //ACText(caption, "Publishing the wifi");

  //aux.add({header, caption});
  //Portal.join(aux);
  Config.menuItems = AC_MENUITEM_HOME | AC_MENUITEM_DISCONNECT;

  //Portal.disableMenu(AC_MENUITEM_CONFIGNEW | AC_MENUITEM_OPENSSIDS | AC_MENUITEM_RESET);
  Portal.config(Config);                        // Configure AutoConnect
}

void getSpiffImg(String path, String TyPe) { 
 if(SPIFFS.exists(path)){ 
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, TyPe);
    file.close();
  }
}

void handle_css() {
  handle_page("/style.css", true);
}
void handle_first_question() {
  Serial.println("First question");
  handle_page("/first_q.html", false);
}

void handle_home_page() {
  Serial.println("Home page");
  handle_page("/home_p.html", false);
}

void handle_page(String page_name, bool is_css) {
  File file = SPIFFS.open(page_name, "r");
  String page = "";
  if (file) {
    while (file.available()) {
      page += (char)file.read();
    }
    if(is_css)
      server.send(200, "text/css", page);
    else
      server.send(200, "text/html", page);
  } else
      Serial.println("Failed to get page"); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(false, LED2status));
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status, true));
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status, false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
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
