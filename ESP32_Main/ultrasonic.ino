int trig_pin = 13;
int echo_pin = 12;

SR04 HCSR04 = SR04(echo_pin, trig_pin);

long get_distance() {
  long  d = HCSR04.Distance();
  if ( d == 0)
    d = -1;
  return d;
}

bool check_person(int angle, int t_stop) {
  long distance = 0;
  unsigned long timer = millis();
  int n = 1;
  while (millis() - timer < t_stop) {
    if (n == 1) {
      distance = get_distance();
      Serial.printf("l: %li cm Angle = %d \n", distance, angle);
      n = 2;
    }
    if (distance <= SOGLIA_DIST && distance > 0) {
      distance = get_distance();
      Serial.printf("l2: %li cm Angle = %d \n", distance, angle);
      if (distance <= SOGLIA_DIST && distance > 0) {
        ledcAnalogWrite(tilt_ch, tilt_center);
        return true;
      }
    }
  }
  return false;
}
