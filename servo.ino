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
  Serial.printf("Pan = %d , Tilt = %d ", randX, randY);
  ledcAnalogWrite(pan_ch, randX);
  delay(100);
  ledcAnalogWrite(tilt_ch, randY);
  delay(100);
}



void scan() {

  tilt_position = 100;
  ledcAnalogWrite(tilt_ch, tilt_position);

  int    pan_start = 70;
  int    pan_end = 130;
  int    t_stop = 90;
  int    passo = 15;

  for (int i = pan_start; i <= pan_end; i += passo) {
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
  }
  for (int i = pan_end; i >= pan_start; i -= passo) {
    ledcAnalogWrite(pan_ch, i);
    delay(t_stop);
  }
}

bool Search() {

  int pan_start = 70;
  int pan_end = 130;
  int t_stop = 40;
  int passo = 2;
  long distance = 0;
  tilt_position = 140;
  ledcAnalogWrite(tilt_ch, tilt_position);

  for (int i = pan_start; i <= pan_end; i += passo) {
    ledcAnalogWrite(pan_ch, i);

    unsigned long timer = millis();
    int n = 1;
    while (millis() - timer < t_stop) {
      if (n == 1) {
        distance = Distanza();
        Serial.printf("l: %li cm Angle = %d \n", distance, i);
        n = 2;
      }
      if (distance <= 50 && distance > 0) {
        tilt_position = 150;
        ledcAnalogWrite(tilt_ch, tilt_position);
        return true;
      }
    }
  }
  for (int i = pan_end; i >= pan_start; i -= passo) {
    ledcAnalogWrite(pan_ch, i);
    unsigned long timer = millis();
    int n = 1;
    while (millis() - timer < t_stop) {
      if (n == 1) {
        distance = Distanza();
        Serial.printf("l: %li cm Angle = %d \n", distance, i);
        n = 2;
      }
      if (distance <= 50 && distance > 0) {
        tilt_position = 150;
        ledcAnalogWrite(tilt_ch, tilt_position);
        return true;
      }
    }
  }
  return false;
}
