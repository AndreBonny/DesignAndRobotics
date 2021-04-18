#define RRS_PIN 22
#define RS_PIN 24
#define LS_PIN 26
#define LLS_PIN 28

#define e1 1
#define e2 2
#define e3 3

double RRS;
double RS;
double LS;
double LLS;


void Inizializza_sensori() {
  pinMode(RRS_PIN, INPUT);
  pinMode(RS_PIN, INPUT);
  pinMode(LS_PIN, INPUT);
  pinMode(LLS_PIN, INPUT);
}

void following_PID() {

  Input = double(readSens());
  Setpoint = 0;

  if (Input != 10) {

    PID.Compute();
    //errore negativo -> Output negativo -> giro a destra

    if (Output > 0) {
      Speed_L = V - int(Output);
      Speed_R = V  ;
    }
    else if (Output < 0) {
      Speed_R = V + int(Output);
      Speed_L = V ;
    }
    else {
      Speed_R = V;
      Speed_L = V;
    }

    /*Speed_L = V - int(Output);
      Speed_R = V + int(Output);*/

    Speed_R = max(min(Speed_R, 255), -255);
    Speed_L = max(min(Speed_L, 255), -255);

    Serial3.print("Input =");
    Serial3.print(Input);
    Serial3.print("  Speed_R = ");
    Serial3.print(Speed_R);
    Serial3.print("  Speed_L = ");
    Serial3.println(Speed_L);


    move(MOT_L, Speed_L);
    move(MOT_R, Speed_R);
  }
  else {
    Stop();
  }
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

  if ((digitalRead(LS_PIN)) && (digitalRead(RS_PIN))) // stop
  {
    fermo(MOT_R);
    fermo(MOT_L);
    return true;
  }
  return false;
}

/*
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
    fermo(MOT_R);
    fermo(MOT_L);
  }
  }

  void follow() {

  Serial3.println("Seguo Linea");
  while (!following_forward()) {
  }
  Serial3.println("Arrivato");
  delay(3000);
  Serial3.println("Riparto");
  go(200);
  Serial3.println("Mosso");
  }
*/

double readSens() {

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
