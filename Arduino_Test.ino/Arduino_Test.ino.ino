#include <AFMotor.h>
//#include <PID_v1.h>
#include "LedControl.h"

//define of pins
#define PHASE_PIN 22
#define LASER_PIN_L 52
#define LASER_PIN_R 53
#define BUSY_PIN 21

//define for movement
#define MOT_R 3
#define MOT_L 4
#define V  150
#define Omega  240
#define T_turn 1500
#define T_straight 2000


//define for messages exchanged between arduino and ESP
#define ARD_READY "1"
#define ESP_READY "2"
#define PHASE_1 "3"
#define PHASE_2 "4"
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
             LETS_SEE, VERY_BAD, BAD, GOOD, VERY_GOOD, PERFECT
           };

//variable for timers
unsigned long t;
//variable for phase
int phase;



double Setpoint, Input, Output;
int Speed_R, Speed_L;

double Kp = V, Ki = 0 , Kd = 0;
//PID PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
int i = 2;
unsigned long timer;

void setup() {
  Serial1.begin(115200);
  Serial1.setTimeout(1);
  Serial.begin(115200);
  Serial3.begin(115200);

  serial_write_debug("START");
  /*
    //wait for message from esp
    while (serial_read() != ESP_READY) {
    }
    serial_write_debug("ESP READY");*/

  //initialization of arduino
  Inizializza_sensori();
  Inizializza_Motori();
  Inizializza_Occhi();
  Inizializza_DFPlayer();
  //Inizializza Laser
  pinMode(LASER_PIN_L, OUTPUT);
  digitalWrite(LASER_PIN_L, LOW);
  pinMode(LASER_PIN_R, OUTPUT);
  digitalWrite(LASER_PIN_R, LOW);
  //Inizializza Switch Phase
  pinMode(PHASE_PIN, INPUT_PULLUP);

  //comunicate to ESP that initialization has finished
  serial_write(ARD_READY);
  delay(10);
  serial_write_debug("ARDUINO READY");

  //read current phase
  phase = digitalRead(PHASE_PIN);
  if (phase == 1)
    serial_write(PHASE_1);
  if (phase == 0)
    serial_write(PHASE_2);

  //random for phase 2
  // randomSeed(analogRead(31));

  //ready to start
  //draw_openclose();
  delay(1000);
  Serial.println("Start");
  //play(1);
  timer = millis();
}

void loop() {
  /*phase = digitalRead(PHASE_PIN);
  Serial.println(phase);*/
  //follow();
  /*Serial.println("PLAY");
    play(ADVERTISE);
    delay(10000);
    Serial.println("STOP AND SLEEP");
    sleep();

    delay(3000);*/
  /*
    Serial.println("Play greetings");
    play(GREETINGS);

    delay(5000);
    Serial.println("stop greetings");
    stop_play();
    sleep();
    //Serial.println("Sleep");
    delay(5000);
    Serial.println("Play Qrcode");
    play(QRCODE);
    delay(5000);
    stop_play();
    sleep();
    //Serial.println("Sleep");
    delay(5000);*/



  /*
    bool end_sp = false;

    // Keep playing the track until the thing finishes or we recieve a STOP_SPEAK
    serial_write_debug("Ricevuto SPEAK");
    draw_openclose();
    int noPlayCount = 0;
    Track track = GREETINGS;

    play(track);
    draw_happy_start();
    draw_happy_open();
    delay(1500);
    t = millis();
    do
    {
      if (serial_read() == STOP_SPEAK_1)
      {
        //we read a stop signal from esp
        stop_play();
        play(SADNESS);
        draw_sad_start();
        noPlayCount = 0;
        while (noPlayCount < 2) //check end of track
        {
          if (dfNotPlaying())
            noPlayCount++;
          if (millis() - t > 2500)
          {
            t = millis();
            draw_sad_blink();
          }
          delay(500);
        }
        end_sp = true;
        draw_sad_end();
      }
      else
      {
        if (noPlayCount < 2) //margin is needed for false positive when a track starts
        {
          if (dfNotPlaying())
            noPlayCount++;
          if (millis() - t > 2500)
          {
            t = millis();
            if (track < 3)
              draw_happy_blink();
            else
            {
              draw_openclose();
            }
          }
          delay(500);
        }
        else //track ended
        {
          //down here it's track++;
          track = static_cast<Track>(static_cast<int>(track) + 1);
          if (track < 5)
          {
            noPlayCount = 0;
            play(track);
            if (track == 3)
            {
              draw_happy_close();
              draw_happy_end();
            }
          }
          else
          {
            end_sp = true;
          }
        }
      }
    } while (!end_sp);*/

  /*
    if (millis() - timer > 3000) {
    timer = millis();
    play(i);
    i++;//Play next mp3 every 3 second.
    }*/



  draw_happy_open();
    delay(500);
    draw_happy_blink();
    delay(500);
    draw_happy_blink();
    delay(500);
    draw_happy_blink();
    delay(500);
    draw_happy_close();
    draw_happy_end();
    delay(500);


    draw_sad_start();
    delay(500);
    draw_sad_blink();
    delay(500);
    draw_sad_blink();
    delay(500);

    draw_sad_end();

    draw_correct_eye_start();
    delay(1000);
    draw_correct_eye_end();
    draw_openclose();
    draw_wrong_eye_start();
    delay(1000);
    draw_wrong_eye_end();
    draw_openclose();
    draw_angry_start();
    delay(2000);
    draw_angry_blink();
  /* move_forward(T_straight,V);
    delay(2000);
    move_backward(T_straight,V);
    Stop();
    delay(2000);*/
  /*
    if (phase == 1) {
      phase1();
    }
    else {
      phase2();
    }*/

}
