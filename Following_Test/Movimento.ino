
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


void move(int mot, int speed){

  speed = max(min(speed,255),-255);
  
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
int limitatore(int speed){
  if(speed>)
}*/

void move_forward(int t) {
  avanti(MOT_R, V);
  avanti(MOT_L, V);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void move_backward(int t) {
  indietro(MOT_R, V);
  indietro(MOT_L, V);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void turn_right(int t) {
  avanti(MOT_L, Omega);
  indietro(MOT_R, Omega);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void turn_left(int t) {
  indietro(MOT_L, Omega);
  avanti(MOT_R, Omega);
  delay(t);
  fermo(MOT_R);
  fermo(MOT_L);
}

void Stop() {
  fermo(MOT_R);
  fermo(MOT_L);
}
