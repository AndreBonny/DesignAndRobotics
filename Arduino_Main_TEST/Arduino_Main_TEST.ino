#include <AFMotor.h>
#include "LedControl.h"

#define FASE_PIN 20
#define LASER_PIN_L 48
#define LASER_PIN_R 49

#define MOT_R 1
#define MOT_L 4
#define V  200
#define Omega  240
#define T_turn 1500
#define T_straight 2000


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

enum Track {  A , GREETINGS, ADVERTISE, QRCODE, BYE_GREETINGS, ROCK_SONG };

unsigned long t;



void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(1);
  Serial.begin(9600);
  Serial3.begin(9600);

  //Inizializza_sensori();
  //Inizializza_Motori();
  Inizializza_Occhi();
  //Inizializza_DFPlayer();
  pinMode(LASER_PIN_L, OUTPUT);
  digitalWrite(LASER_PIN_L, LOW);
  pinMode(LASER_PIN_R, OUTPUT);
  digitalWrite(LASER_PIN_R, LOW);

  delay(1000);
  serial_write(ARD_READY);
  delay(10);
  serial_write_debug("ARDUINO READY");

  delay(5000);
}


void loop() {
  /*
    draw_openclose();

    play(GREETINGS);
    delay(16000);
    play(ADVERTISE);
    delay(23000);
    play(QRCODE);
    delay(16000);
    play(BYE_GREETINGS);
    delay(15000);
    play(ROCK_SONG);
    delay(5000);
  */
  /*
  draw_correct_eye_start();
  delay(1000);
  draw_correct_eye_end();
  draw_openclose();
  draw_wrong_eye_start();
  delay(1000);
  draw_wrong_eye_end();
  draw_openclose();
  */
  //draw_angry();
  draw_question();


}
