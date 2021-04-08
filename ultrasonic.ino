
long Distanza() {
  long  d = HCSR04.Distance();
  if ( d == 0)
    d = -1;
  return d;
}
