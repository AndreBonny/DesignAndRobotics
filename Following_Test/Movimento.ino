
#define T_turn 1500
#define T_straight 2000


AF_DCMotor motoreR(4);
AF_DCMotor motoreL(1);

void Inizializza_Motori() {
  motoreR.run(RELEASE);
  motoreL.run(RELEASE);
}


void fermo(int mot) {
  switch (mot) {
    case MOT_R:
      motoreR.run(RELEASE);
      break;
    case MOT_L:
      motoreL.run(RELEASE);
      break;
  }
};

void avanti(int mot, int speed) {
  switch (mot) {
    case MOT_R:
      motoreR.setSpeed(speed);
      motoreR.run(FORWARD);
      break;
    case MOT_L:
      motoreL.setSpeed(speed);
      motoreL.run(FORWARD);
      break;

  }
};

void indietro(int mot, int speed) {
  switch (mot) {
    case MOT_R:
      motoreR.setSpeed(speed);
      motoreR.run(BACKWARD);
      break;
    case MOT_L:
      motoreL.setSpeed(speed);
      motoreL.run(BACKWARD);
      break;
  }
};


void move(int mot, int speed) {

  speed = max(min(speed, 255), -255);

  if (speed > 0) {
    avanti(mot, speed);
  }
  else if (speed < 0) {
    indietro(mot, -speed);
  }
  else {
    fermo(mot);
  }

}


/*
  int limitatore(int speed) {
  if (speed > 0)
    speed =  max(min(255, speed), 80);
  if (speed < 0)
    speed =  min(max(-255, speed), -80);
  }*/

void move_forward(int t, int speed) {
  avanti(MOT_R, speed);
  avanti(MOT_L, speed);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void move_backward(int t, int speed) {
  indietro(MOT_R, speed);
  indietro(MOT_L, speed);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void turn_right(int t, int speed) {
  avanti(MOT_L, speed);
  indietro(MOT_R, speed);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void turn_left(int t, int speed) {
  indietro(MOT_L, speed);
  avanti(MOT_R, speed);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void Stop() {
  fermo(MOT_R);
  fermo(MOT_L);
}
