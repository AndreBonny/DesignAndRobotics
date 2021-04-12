#define LS 53
#define RS 52

void Inizializza_sensori() {
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
}

void following_forward() {

  if (!digitalRead(LS) && !digitalRead(RS))    // Move Forward
  {
    avanti(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (!(digitalRead(LS)) && digitalRead(RS))    // Turn right
  {
    indietro(MOT_R, V);
    avanti(MOT_L, V);

  }

  if (digitalRead(LS) && !(digitalRead(RS)))    // turn left
  {
    avanti(MOT_R, V);
    indietro(MOT_L, V);
  }

  if ((digitalRead(LS)) && (digitalRead(RS)))    // stop
  {
    fermo(MOT_R);
    fermo(MOT_L);
  }


}

void following_backward() {

  if (!digitalRead(LS) && !digitalRead(RS))    // Move Forward
  {
    indietro(MOT_R, V);
    indietro(MOT_L, V);
  }

  if (!(digitalRead(LS)) && digitalRead(RS))    // Turn right
  {
    indietro(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (digitalRead(LS) && !(digitalRead(RS)))    // turn left
  {
    avanti(MOT_R, V);
    indietro(MOT_L, V);
  }

  if ((digitalRead(LS)) && (digitalRead(RS)))    // stop
  {
    fermo(MOT_R);
    fermo(MOT_L);
  }


}
