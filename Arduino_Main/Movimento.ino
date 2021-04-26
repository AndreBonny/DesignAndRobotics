AF_DCMotor motoreR(3);
AF_DCMotor motoreL(4);

void motor_setup() {
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

void moveRandom() {
  while (!checkLine()) {
    avanti(MOT_L, V);
    avanti(MOT_R, V);
  }
  Stop();
}

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
