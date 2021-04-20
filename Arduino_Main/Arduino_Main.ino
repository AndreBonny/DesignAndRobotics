#include <AFMotor.h>
#include "LedControl.h"

#define FASE_PIN 20
#define LASER_PIN_L 50
#define LASER_PIN_R 51

#define BUSY_PIN 5

#define MOT_R 1
#define MOT_L 4
#define V  200
#define Omega  240
#define T_turn 1500
#define T_straight 2000


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

enum Track { A, GREETINGS, ADVERTISE, QRCODE,  BYE_GREETINGS, ROCK_SONG, SADNESS};

unsigned long t;



void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(1);
  Serial.begin(115200);
  Serial3.begin(115200);

  serial_write_debug("START");
  while (serial_read() != ESP_READY) {
  }
  serial_write_debug("ESP READY");
  // Controllo Fase


  Inizializza_sensori();
  Inizializza_Motori();
  Inizializza_Occhi();
  Inizializza_DFPlayer();
  pinMode(LASER_PIN_L, OUTPUT);
  digitalWrite(LASER_PIN_L, LOW);
  pinMode(LASER_PIN_R, OUTPUT);
  digitalWrite(LASER_PIN_R, LOW);

  serial_write(ARD_READY);
  delay(10);
  serial_write_debug("ARDUINO READY");
  draw_openclose();

  delay(500);
  if (digitalRead(FASE_PIN) == 1)
    serial_write(FASE_1);
  if (digitalRead(FASE_PIN) == 0)
    serial_write(FASE_2);

}


void loop() {
  
  if(Fase==1){
    fase1();
  }
  else{
    fase2();
  }
  
}
