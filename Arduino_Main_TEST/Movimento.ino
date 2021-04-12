AF_DCMotor motoreR(1);
AF_DCMotor motoreL(4);

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

void indietro(char mot, int speed) {
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


void go() {
  avanti(MOT_R, V);
  avanti(MOT_L, V);
  delay(T_straight);
  fermo(MOT_R);
  fermo(MOT_L);
}

void back() {
  indietro(MOT_R, V);
  indietro(MOT_L, V);
  delay(T_straight);
  fermo(MOT_R);
  fermo(MOT_L);
}

void turn_right() {
  avanti(MOT_L, Omega);
  indietro(MOT_R, Omega);
  delay(T_turn);
  fermo(MOT_R);
  fermo(MOT_L);
}

void turn_left() {
  indietro(MOT_L, Omega);
  avanti(MOT_R, Omega);
  delay(T_turn);
  fermo(MOT_R);
  fermo(MOT_L);
}

void Stop() {
  fermo(MOT_R);
  fermo(MOT_L);
}
