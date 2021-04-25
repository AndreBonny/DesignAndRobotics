#include <SR04.h>
#include <WebServer.h>
#include <AutoConnect.h>

#include "SPIFFS.h"
#include "esp_camera.h"
#include "fd_forward.h"

enum State {READY, SCANNING, LOOKING, SEARCHING , TRACKING, BACK, WAIT, INGAME, SAD, MOVEMENT, EXPLAINING };
State c_state;

#define ARD_READY "1"
#define ESP_READY "2"
#define phase_1 "3"
#define phase_2 "4"
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
int pan_center = 105;
int tilt_tracking = 90;

int tilt_position;
int pan_position;


bool founded = false;
bool connected = false;

int phase;
int end_t;
String msg = "";
String data;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);

  initialize_servo();
  initialize_camera();

  // Initialize SPIFFS for file system
  if (!SPIFFS.begin(true))
    return;

  delay(100);
  serial_write(ESP_READY);
  delay(10);

  while (serial_read() != ARD_READY) {
  }

  delay(10);

  do {
    msg = serial_read();

    if (msg == phase_1) {
      phase = 1;
    }
    else if (msg == phase_2) {
      phase = 2;
    }
  } while (msg.length() <= 0 );

  c_state = READY;

  delay(2000);
}



void loop()
{
  if (phase == 1) {
    phase1();
  }
  else if (phase == 2) {
    phase2();
  }
  else {

  }
}
