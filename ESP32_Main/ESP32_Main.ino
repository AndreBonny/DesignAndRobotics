#include <SR04.h>
//#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>
//#include <DNSServer.h>
//#include <ESPAsyncWebServer.h>

#include "SPIFFS.h"
#include "esp_camera.h"
#include "fd_forward.h"

enum State {READY, SCANNING, LOOKING, SEARCHING, SPEAKING, TRACKING, BACK, WAIT, INGAME};
State Cstate;

#define MOV "1"
#define LASER_OFF "2"
#define RES_POS "3"
#define SPEAK "4"
#define END_MOV "5"
#define ARD_READY "6"
#define END_RES_POS "7"
#define END_SPEAK "8"
#define ESP_READY "9"
#define FASE_1 "10"
#define FASE_2 "11"
#define ROCK_INT "12"
#define END_ROCK_INT "13"
#define START_GAME "14"

#define LED_BUILTIN 4
#define MAX_ERROR 10
#define SOGLIA_DIST 130


// Per Flash
int freq = 5000;
int ledChannel = 3;
int ledResolution = 12;

// Pin e Channel servo
int tilt_pin = 14;
int pan_pin = 15;
int tilt_ch = 2;
int pan_ch = 4;

int tilt_center = 130;
int pan_center = 100;

int tilt_position;
int pan_position;

WebServer server(80);
AutoConnect Portal(server);

//DNSServer dnsServer;

bool trovato = false;

int Fase;

void setup() { 
  Serial.begin(115200);
  Serial.setTimeout(1);
  //Flash
  ledcSetup(ledChannel, freq, ledResolution);
  ledcAttachPin(LED_BUILTIN, ledChannel);

  Inizializza_servo();
  Inizializza_camera();
  Inizializza_webserver();
  
  delay(100);
  serial_write(ESP_READY);
  delay(10);

  while (serial_read() != ARD_READY) {
  }
  delay(10);
  /*
    if (serial_read() == FASE_1) {
    Fase = 1;
    }
    else if (serial_read() == FASE_2) {
    Fase = 2;
    }
    else {
    //BHO
    }*/


  Cstate = INGAME;
  delay(2000);
}

int inited = 0;

void loop()
{

  String data = serial_read();
  
  if(data.length() > 0 && data == START_GAME)
    Cstate = INGAME;

  //Phase 1
  switch (Cstate)
  {
    /* Start state
       send #1 and change state
    */
    case READY:
      serial_write(MOV);
      Cstate = SCANNING;
      delay(500);
      break;

    /* Scan state
       Move head while waiting for the END_MOV
    */
    case SCANNING:
      //data = serial_read();
      if (data.length() > 0 && data == END_MOV) {
        //body has finished to move
        ledcAnalogWrite(pan_ch, pan_center);
        Cstate = LOOKING;
        //serial_write_debug("nxt LK");
        //delay(500);
      }
      else
      {
        scan();
      }
      break;


    /* Interaction with rock
    */
    case LOOKING:
      //Messaggio arduino parlare
      //ledcAnalogWrite(LED_BUILTIN, 200);
      serial_write(ROCK_INT);
      do {
        data = serial_read();
        rock();
      } while (data.length() < 0 || data != END_ROCK_INT);
      center_head();
      Cstate = SEARCHING;
      //serial_write_debug("nxt SRCH");
      //delay(500);
      break;

    /* Ultrasound search state
       Search if there is something with the US sensor
       then change state according to the result
    */
    case SEARCHING:
      delay(1000);
      for (int i = 0; i < 4 && !trovato; i++) {
        trovato = Search();
      }
      if (trovato) {
        // Serial.printf("TROVATO");
        //  serial_write_debug("Ult-F nxt TRK");
        // delay(500);
        Cstate = TRACKING;
        trovato = false;
      }
      else {
        //Serial.printf("NON TROVATO");
        //serial_write_debug("Ult-NF nxt BCK");
        //delay(500);
        Cstate = BACK;
      }

      break;

    /* Second searching state
       Start Face Trackin and cont the cycles where a face is found
    */
    case TRACKING:
      Serial.printf("Starting tracking");
      serial_write(SPEAK);
      ledcAnalogWrite(tilt_ch, 160);
      //serial_write_debug("Str TRK");
      //stop message read inside face_tracking function
      Face_tracking();
      Cstate = BACK;
      // serial_write_debug("end TRK nxt BCK");
      // delay(500);

      break;

    /* End of one complete cycle
       Send RESEt and change state
    */
    case BACK:
      center_head();
      serial_write(RES_POS);
      Cstate = WAIT;
      break;


    /* Waiting state, we wait for the end of the RESET,
      wait 1 sec and then go to START
    */
    case WAIT:
      data = serial_read();
      if (data.length() > 0 && data == END_RES_POS) {
        //restart for a new cycle
        delay(5000);
        Cstate = READY;
      }
      break;
   
    case INGAME:
      if(!inited) {
        Serial.println("Waiting for connection");   
        inited = 1;
      }
      Portal.onConnect(onConnect);
      Portal.begin();
      Portal.handleClient();
      break;
  }
}
