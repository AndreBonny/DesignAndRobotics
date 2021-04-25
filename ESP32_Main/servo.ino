void ledcAnalogWrite(uint8_t channel, uint32_t value) {
  if (channel == tilt_ch && value <= 50)
    value = 50;

  uint32_t valueMax = 180;
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  ledcWrite(channel, duty);
}

void initialize_servo() {

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

void center_head() {
  ledcAnalogWrite(tilt_ch, tilt_center);
  ledcAnalogWrite(pan_ch, pan_center);
}

void scan() {
  tilt_position = 130;
  ledcAnalogWrite(tilt_ch, tilt_position);

  int    pan_start = 60;
  int    pan_end = 140;
  int    t_stop = 15;
  int    passo = 1;

  ledcAnalogWrite(pan_ch, pan_start);

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

bool search_person() {

  int pan_start = 70;
  int pan_end = 130;
  int t_stop = 40;
  int passo = 2;
  tilt_position = tilt_center;
  ledcAnalogWrite(tilt_ch, tilt_position);
  ledcAnalogWrite(pan_ch, pan_start);

  delay(100);
  for (int angle = pan_start; angle <= pan_end; angle += passo) {
    ledcAnalogWrite(pan_ch, angle);
    if (check_person(angle, t_stop))
      return true;
  }
  for (int angle = pan_end; angle >= pan_start; angle -= passo) {
    ledcAnalogWrite(pan_ch, angle);
    if (check_person(angle, t_stop))
      return true;
  }
  return false;
}

void rock_interaction() {

  int tilt_start = 110;
  int tilt_end = 130;
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
