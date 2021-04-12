#include <SR04.h>
#include "esp_camera.h"
#include "fd_forward.h"

enum State {READY, SCANNING, LOOKING, SEARCHING, SPEAKING, TRACKING, BACK, WAIT};
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

#define LED_BUILTIN 4
#define MAX_ERROR 5
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
int pan_center = 87;

int tilt_position;
int pan_position;

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


  Cstate = READY;
  delay(100);
}



void loop()
{

  String data;

  //Phase 1
  switch (Cstate)
  {
    /* Start state
       send #1 and change state
    */
    case READY:
      serial_write(MOV);
      delay(10);
      Cstate = SCANNING;
      break;

    /* Scan state
       Move head while waiting for the END_MOV
    */
    case SCANNING:
      data = serial_read();
      if (data.length() > 0 && data == END_MOV) {
        //body has finished to move
        ledcAnalogWrite(pan_ch, pan_center);
        Cstate = LOOKING;
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
      break;

    /* Ultrasound search state
       Search if there is something with the US sensor
       then change state according to the result
    */
    case SEARCHING:
      for (int i = 0; i < 4 && !trovato; i++) {
        trovato = Search();
        if (trovato)
        {
          serial_write_debug("TROVATO");
          delay(100);
          Cstate = TRACKING;
        }
      }
      if (!trovato)
        Cstate = BACK;
      break;

    /* Second searching state
       Start Face Trackin and cont the cycles where a face is found
    */
    case TRACKING:
      serial_write(SPEAK);
      ledcAnalogWrite(tilt_ch, tilt_center);
      serial_write_debug("Starting TRACKING");
      Face_tracking();
      Cstate = BACK;
      center_head();
      break;

    /* End of one complete cycle
       Send RESEt and change state
    */
    case BACK:
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
  }
}
