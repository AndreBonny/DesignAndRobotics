#define TRIG_PIN 13
#define ECHO_PIN 12

SR04 HCSR04 = SR04(ECHO_PIN, TRIG_PIN);

long Distanza() {
  long  d = HCSR04.Distance();
  if ( d == 0)
    d = -1;
  return d;
}

bool checkPerson(int angle, int t_stop) {
  long distance = 0;
  unsigned long timer = millis();
  int n = 1;
  while (millis() - timer < t_stop) {
    if (n == 1) {
      distance = Distanza();
      //Serial.printf("l: %li cm Angle = %d \n", distance, angle);
      n = 2;
    }
    if (distance <= SOGLIA_DIST && distance > 0) {
      distance = Distanza();
      //Serial.printf("l2: %li cm Angle = %d \n", distance, angle);
      if (distance <= SOGLIA_DIST && distance > 0) {
        ledcAnalogWrite(tilt_ch, tilt_center);
        return true;
      }
    }
  }
  return false;
}
