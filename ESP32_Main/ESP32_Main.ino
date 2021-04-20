#include <SR04.h>
//#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

#include "SPIFFS.h"
#include "esp_camera.h"
#include "fd_forward.h"

enum State {READY, SCANNING, LOOKING, SEARCHING , TRACKING, BACK, WAIT, INGAME, SAD, MOVEMENT, EXPLAINING };
State Cstate;

#define ARD_READY "1"
#define ESP_READY "2"
#define FASE_1 "3"
#define FASE_2 "4"
#define MOV_1 "5"
#define END_MOV_1 "6"
#define RES_POS_1 "7"
#define END_RES_POS_1 "8"
#define SPEAK_1 "9"
#define END_SPEAK_1 "10"
#define STOP_SPEAK_1 "11"
#define ROCK_INT "12"
#define END_ROCK_INT "13"
#define MOV_2 "14"
#define END_MOV_2 "15"
#define SPEAK_2 "16"
#define END_SPEAK_2 "17"
#define STOP_SPEAK_2 "18"
#define RES_POS_2 "19"
#define END_RES_POS_2 "20"
#define START_GAME "21"
#define START_GAME_YES "22"
#define START_GAME_NO "23"
#define END_GAME "24"
#define CORRECT_ANSWER "25"
#define WRONG_ANSWER "26"



#define MAX_ERROR 10
#define SOGLIA_DIST 130

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


bool trovato = false;

int Fase;
int fine;
String msg = "";

void setup() { 
  Serial.begin(115200);
  Serial.setTimeout(1);

  Inizializza_servo();
  Inizializza_camera();
  Inizializza_webserver();

  delay(100);
  serial_write(ESP_READY);
  delay(10);

  while (serial_read() != ARD_READY) {
  }
  delay(10);


  do {
    msg = serial_read();

    if (msg == FASE_1) {
      Fase = 1;
    }
    else if (msg == FASE_2) {
      Fase = 2;
    }

  } while (msg.length() <= 0 );
  Cstate = READY;
  delay(2000);
}



void loop()
{

<<<<<<< HEAD
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
=======
  if (Fase == 1) {
    fase1();
  }
  else if (Fase == 2) {
    fase2();
>>>>>>> 5360d92e4463b89001e92a504e0199ad704d1ccf
  }
  else {
    //BHO
  }

}
