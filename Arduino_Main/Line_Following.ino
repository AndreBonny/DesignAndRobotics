#define RRS_PIN 49
#define RS_PIN 48
#define LS_PIN 47
#define LLS_PIN 46

#define e1 1
#define e2 2
#define e3 3

double RRS;
double RS;
double LS;
double LLS;


void sensor_setup() {
  pinMode(RRS_PIN, INPUT);
  pinMode(RS_PIN, INPUT);
  pinMode(LS_PIN, INPUT);
  pinMode(LLS_PIN, INPUT);
}

bool following_forward() {

  if (!digitalRead(LS_PIN) && !digitalRead(RS_PIN)) // Move Forward
  {
    avanti(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (!(digitalRead(LS_PIN)) && digitalRead(RS_PIN)) // Turn right
  {
    indietro(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (digitalRead(LS_PIN) && !(digitalRead(RS_PIN))) // turn left
  {
    avanti(MOT_R, V);
    indietro(MOT_L, V);
  }

  if (digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(LLS_PIN) && digitalRead(RRS_PIN)) // stop
  {
    Stop();
    return true;
  }
  return false;
}


bool following_forward2() {

  int Input = readSens();

  if (Input == 0) // Move Forward
  {
    avanti(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (Input == 1) // Turn right
  {
    indietro(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (Input == 2 || Input == 3) // Turn right
  {
    indietro(MOT_R, int(V * 1.2));
    avanti(MOT_L, int(V * 1.2));
  }

  if (Input == -1) // turn left
  {
    avanti(MOT_R, V);
    indietro(MOT_L, V);
  }


  if (Input == -2 || Input == -3) // Turn right
  {
    avanti(MOT_R, int(V * 1.2));
    indietro(MOT_L, int(V * 1.2));
  }

  if (Input == 10) // stop
  {
    Stop();
    return true;
  }

  return false;
}


void following_backward() {

  if (!digitalRead(LS_PIN) && !digitalRead(RS_PIN)) // Move Forward
  {
    indietro(MOT_R, V);
    indietro(MOT_L, V);
  }

  if (!(digitalRead(LS_PIN)) && digitalRead(RS_PIN)) // Turn right
  {
    indietro(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (digitalRead(LS_PIN) && !(digitalRead(RS_PIN))) // turn left
  {
    avanti(MOT_R, V);
    indietro(MOT_L, V);
  }

  if ((digitalRead(LS_PIN)) && (digitalRead(RS_PIN))) // stop
  {
    Stop();
  }
}

void follow() {

  while (!following_forward()) {
  }
  delay(3000);
  move_forward(200, V);
}


int readSens() {

  LLS = 0;
  LS = 0;
  RS = 0;
  RRS = 0;
  double x;

  if (digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = -e3;
  }
  if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = -e2;
  }
  if (!digitalRead(LLS_PIN) && digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = -e1;
  }
  if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = 0;
  }
  if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = e1;
  }
  if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) {
    x = e2;
  }
  if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && digitalRead(RRS_PIN)) {
    x = e2;
  }
  if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) {
    x = 10;
  }

  Serial.println(x);

  return x;
}

bool checkLine() {
  if (digitalRead(LLS_PIN) || digitalRead(LS_PIN) || digitalRead(RS_PIN) || digitalRead(RRS_PIN))
    return true;
  else
    return false;
}
