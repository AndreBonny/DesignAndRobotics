int trig_pin = 13;
int echo_pin = 12;

SR04 HCSR04 = SR04(echo_pin, trig_pin);

long get_distance() {
  long  d = HCSR04.Distance();
  if ( d == 0)
    d = -1;
  return d;
}

// check if the sonar sensor finds something in the current direction
bool check_person(int angle, int t_stop) {
  long distance = 0;
  unsigned long timer = millis();
  int n = 1;
  while (millis() - timer < t_stop) {
    if (n == 1) {
      distance = get_distance();
      n = 2;
    }
    // do a double mesurament to have move resiliance
    if (distance <= SOGLIA_DIST && distance > 0) {
      distance = get_distance();
      if (distance <= SOGLIA_DIST && distance > 0) {
        return true;
      }
    }
  }
  return false;
}
