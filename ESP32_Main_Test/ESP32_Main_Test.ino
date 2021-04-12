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
#define SOGLIA_DIST 150


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
  delay(500);
}



void loop()
{
  for (int i = 0; i < 4 && !trovato; i++) {
    trovato = Search();

  }
  if (trovato)
  {
    Serial.println("TROVATO");
    ledcAnalogWrite(tilt_ch, 150);
    Face_tracking();
    Serial.println("FINE TRACKING");
  }
  if (!trovato) {
    Serial.println("NON TROVATO");
    center_head();

  }

  delay(5000);




}
