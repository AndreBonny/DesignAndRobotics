// function to move servos with the esp
void ledcAnalogWrite(uint8_t channel, uint32_t value) {
  if (channel == tilt_ch && value < 85)
    value = 85;
  if (channel == tilt_ch && value > 155)
    value = 155;
    
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

// moves the head right and left, while looking on the bottom
bool scan() {
  tilt_position = 145;
  ledcAnalogWrite(tilt_ch, tilt_position);

  int    pan_start = 60;
  int    pan_end = 140;
  int    t_stop = 15;
  int    pan_passo = 1;

  ledcAnalogWrite(pan_ch, pan_start);

  for (int i = pan_start; i <= pan_end; i += pan_passo) {
    if (serial_read() == END_MOV_1)
      return false;
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
  }
  delay(300);
  for (int i = pan_end; i >= pan_start; i -= pan_passo) {
    if (serial_read() == END_MOV_1)
      return false;
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
  }
  delay(300);
  return true;
}

// search if there is someone in some position
bool search_person() {

  int pan_start = 70;
  int pan_end = 130;
  int t_stop = 40;
  int pan_passo = 2;

  // set the right initial positions
  tilt_position = tilt_center;
  ledcAnalogWrite(tilt_ch, tilt_position);
  ledcAnalogWrite(pan_ch, pan_start);

  // move the head looking for someone
  delay(300);
  for (int angle = pan_start; angle <= pan_end; angle += pan_passo) {
    ledcAnalogWrite(pan_ch, angle);
    if (check_person(angle, t_stop))
      return true;
  }
  delay(100);
  for (int angle = pan_end; angle >= pan_start; angle -= pan_passo) {
    ledcAnalogWrite(pan_ch, angle);
    if (check_person(angle, t_stop))
      return true;
  }
  return false;
}

// movement of the head when the robot is looking to the rock
bool rock_interaction() {

  int pan_start = pan_center - 15;
  int pan_end = pan_center + 15;
  int tilt_start = 135;

  int t_stop = 100;
  int pan_passo = 7;
  int tilt_passo = 2;

  ledcAnalogWrite(tilt_ch, tilt_start);

  int tilt_pos = 0;
  int pan_pos = 0;

  // move the head horizontally and randomly vertically
  for (int i = pan_start; i <= pan_end; i += pan_passo) {
    if (serial_read() == END_ROCK_INT) {
      return false;
    }
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
    ledcAnalogWrite(tilt_ch, random(-1, 1) * (tilt_passo) + tilt_start);
    delay(t_stop);
  }
  delay(200);
  for (int i = pan_end; i >= pan_start; i -= pan_passo) {
    if (serial_read() == END_ROCK_INT) {
      return false;
    }
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
    ledcAnalogWrite(tilt_ch, random(-1, 1) * (tilt_passo) + tilt_start);
    delay(t_stop);
  }
  return true;
}
