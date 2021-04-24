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

int tilt_center = 100;
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

  delay(100);
  serial_write(ESP_READY);
  delay(10);

  //Cstate = READY;
  //Cstate = INGAME;
  delay(2000);
}



void loop()
{
    

  Serial.println("Test Search");
  for (int i = 0; i < 2; i++) {
    scan();
  }
  
  delay(1000);
  center_head();
  delay(2000);

  /*
    if (Fase == 1) {
    fase1();
    }
    else if (Fase == 2) {
    fase2();
    }
    else {
    //BHO
    }*/

}
