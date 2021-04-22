#include <AFMotor.h>
#include "LedControl.h"

//define of pins
#define FASE_PIN 20
#define LASER_PIN_L 50
#define LASER_PIN_R 51
#define BUSY_PIN 5

//define for movement
#define MOT_R 1
#define MOT_L 4
#define V  200
#define Omega  240
#define T_turn 1500
#define T_straight 2000


//define for messages exchanged between arduino and ESP
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

//enum of the tracks on SD card
enum Track { A, GREETINGS, ADVERTISE, QRCODE,  BYE_GREETINGS, ROCK_SONG, SADNESS, GAME_PROPOSAL, GAME_START_INSTRUCTION, INTRODUCTION_PHRASE, CORRECT_PHRASE, WRONG_PHRASE, FACTS_1, FACTS_2, FACTS_3, FACTS_4, FACTS_5, 
            LETS_SEE, VERY_BAD, BAD, GOOD, VERY_GOOD, PERFECT};

//variable for timers
unsigned long t;
//variable for phase
int fase;

void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(1);
  Serial.begin(115200);
  Serial3.begin(115200);

  serial_write_debug("START");
  
  //wait for message from esp
  while (serial_read() != ESP_READY) {
  }
  serial_write_debug("ESP READY");

  //initialization of arduino
  Inizializza_sensori();
  Inizializza_Motori();
  Inizializza_Occhi();
  Inizializza_DFPlayer();
  pinMode(LASER_PIN_L, OUTPUT);
  digitalWrite(LASER_PIN_L, LOW);
  pinMode(LASER_PIN_R, OUTPUT);
  digitalWrite(LASER_PIN_R, LOW);

  //comunicate to ESP that initialization has finished
  serial_write(ARD_READY);
  delay(10);
  serial_write_debug("ARDUINO READY");

  //read current phase
  fase = digitalRead(FASE_PIN);
  if (fase == 1)
    serial_write(FASE_1);
  if (fase == 0)
    serial_write(FASE_2);

  //random for phase 2
  randomSeed(analogRead(31));
  
  //ready to start
  draw_openclose();
  delay(500);
}


void loop() {

  if (fase == 1) {
    fase1();
  }
  else {
    fase2();
  }

}
