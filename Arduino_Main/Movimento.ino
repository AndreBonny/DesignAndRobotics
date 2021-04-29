AF_DCMotor motoreR(3);
AF_DCMotor motoreL(4);

void motor_setup() {
  motoreR.run(RELEASE);
  motoreL.run(RELEASE);
}

void stop(int mot) {
  switch (mot) {
    case MOT_R:
      motoreR.run(RELEASE);
      break;
    case MOT_L:
      motoreL.run(RELEASE);
      break;
  }
};

void forward(int mot, int speed) {
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

void backward(int mot, int speed) {
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

void move_random() {
  while (!checkLine()) {
    forward(MOT_L, V);
    forward(MOT_R, V);
  }
  Stop();
}

void move_forward(int t, int speed) {
  forward(MOT_R, speed);
  forward(MOT_L, speed);
  delay(t);
  stop(MOT_R);
  stop(MOT_L);
}

void move_backward(int t, int speed) {
  backward(MOT_R, speed);
  backward(MOT_L, speed);
  delay(t);
  stop(MOT_R);
  stop(MOT_L);
}

void turn_right(int t, int speed) {
  forward(MOT_L, speed);
  backward(MOT_R, speed);
  delay(t);
  stop(MOT_R);
  stop(MOT_L);
}

void turn_left(int t, int speed) {
  backward(MOT_L, speed);
  forward(MOT_R, speed);
  delay(t);
  stop(MOT_R);
  stop(MOT_L);
}

void Stop() {
  stop(MOT_R);
  stop(MOT_L);
}
