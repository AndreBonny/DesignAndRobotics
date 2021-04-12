#define TRIG_PIN 13
#define ECHO_PIN 12

SR04 HCSR04 = SR04(ECHO_PIN, TRIG_PIN);

long Distanza() {
  long  d = HCSR04.Distance();
  if ( d == 0)
    d = -1;
  return d;
}
