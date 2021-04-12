#include <AFMotor.h>
#include "LedControl.h"

#define FASE_PIN 20
#define LASER_PIN_L 50
#define LASER_PIN_R 51

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

enum Track { A, GREETINGS, ADVERTISE, QRCODE,  BYE_GREETINGS, ROCK_SONG };

unsigned long t;



void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(1);
  Serial.begin(115200);
  Serial3.begin(9600);

  serial_write_debug("START");
  while (serial_read() != ESP_READY) {
  }
  serial_write_debug("ESP READY");
  // Controllo Fase
  /*   if (digitalRead(FASE_PIN) == 1)
     serial_write(FASE_1);
     if (digitalRead(FASE_PIN) == 0)
     serial_write(FASE_2);
  */
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
}


void loop() {

  String str = serial_read();
  if (str.length() > 0) {
    serial_write_debug("MSG = ");
    serial_write_debug(str);
  }

  if (str == MOV) {
    serial_write_debug("Ricevuto MOV");
    delay(20); //sicurezza per  Laser??
    digitalWrite(LASER_PIN_L, HIGH); //Laser ON
    digitalWrite(LASER_PIN_R, HIGH); //Laser ON
    //Suoni??
    draw_scanning();
    
    t = millis();
    while (millis() - t < T_straight) {
      following_forward();
    }
    Stop();
    delay(200);
    serial_write(END_MOV);

    draw_openclose();

    // Dopo END_MOV decidere la fase di looking Parlare? e spegnere laser
    //Frase trovato roccia
    //Occhi Felici??
    //digitalWrite(LASER_PIN, LOW); //Laser OFF
  }

  if (str == ROCK_INT) {
    draw_scanning();
    play(ROCK_SONG);
    delay(5000);
    digitalWrite(LASER_PIN_L, LOW);
    digitalWrite(LASER_PIN_R, LOW);
    serial_write(END_ROCK_INT);
  }

  if (str == SPEAK) {
    draw_openclose();
    
    play(GREETINGS);
    for(int i=0; i<4; i++) {
      draw_openclose();
      delay(3250);
    }
    
    play(ADVERTISE);
    for(int i=0; i<6; i++) {
      draw_openclose();
      delay(3250);
    }
    
    play(QRCODE);
    for(int i=0; i<4; i++) {
      draw_openclose();
      delay(3250);
    }
    
    play(BYE_GREETINGS);
    for(int i=0; i<4; i++) {
      draw_openclose();
      delay(3250);
    }
    
    serial_write(END_SPEAK);
  }

  if (str == RES_POS) {
    draw_openclose();
    t = millis();
    while (millis() - t < T_straight) {
      draw_openclose();
      following_backward();
    }
    Stop();
    delay(200);
    draw_openclose();
    serial_write(END_RES_POS);
  }

}
