void ledcAnalogWrite(uint8_t channel, uint32_t value) {
  uint32_t valueMax = 180;
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}

void Inizializza_servo() {

  ledcSetup(tilt_ch, 50, 16);
  ledcAttachPin(tilt_pin, tilt_ch);

  ledcSetup(pan_ch, 50, 16);
  ledcAttachPin(pan_pin, pan_ch);

  ledcAnalogWrite(tilt_ch, tilt_center);
  delay(100);
  ledcAnalogWrite(pan_ch, pan_center);
  delay(100);

  tilt_position = tilt_center;
  pan_position = pan_center;
}


void move_servos() {
  int randX = random(pan_center - 20, pan_center + 20);
  int randY = random(tilt_center - 20, tilt_center + 20);
  //Serial.printf("Pan = %d , Tilt = %d ", randX, randY);
  ledcAnalogWrite(pan_ch, randX);
  delay(100);
  ledcAnalogWrite(tilt_ch, randY);
  delay(100);
}

void center_head() {
  ledcAnalogWrite(tilt_ch, tilt_center);
  ledcAnalogWrite(pan_ch, pan_center);
}

void scan() {

  tilt_position = 100;
  ledcAnalogWrite(tilt_ch, tilt_position);


  int    pan_start = 60;
  int    pan_end = 140;
  int    t_stop = 25;
  int    passo = 2;

  for (int i = pan_start; i <= pan_end; i += passo) {
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
  }
  delay(300);
  for (int i = pan_end; i >= pan_start; i -= passo) {
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
  }
  delay(300);

}

bool Search() {

  int pan_start = 70;
  int pan_end = 130;
  int t_stop = 40;
  int passo = 2;
  tilt_position = tilt_center;
  ledcAnalogWrite(tilt_ch, tilt_position);
  ledcAnalogWrite(pan_ch, pan_start);
  delay(10);
  for (int angle = pan_start; angle <= pan_end; angle += passo) {
    ledcAnalogWrite(pan_ch, angle);
    if (checkPerson(angle, t_stop))
      return true;
  }
  for (int angle = pan_end; angle >= pan_start; angle -= passo) {
    ledcAnalogWrite(pan_ch, angle);
    if (checkPerson(angle, t_stop))
      return true;
  }
  return false;
}

void adjust_tilt() {
  ledcAnalogWrite(tilt_ch, 150);
}

void rock() {

  int tilt_start = 90;
  int tilt_end = 110;
  int t_stop = 40;
  int passo = 2;

  ledcAnalogWrite(pan_ch, pan_position);

  for (int i = tilt_start; i <= tilt_end; i += passo) {
    ledcAnalogWrite(tilt_ch, i);
    delay(t_stop);
  }
  for (int i = tilt_end; i >= tilt_start; i -= passo) {
    ledcAnalogWrite(tilt_ch, i);
    delay(t_stop);
  }
}
