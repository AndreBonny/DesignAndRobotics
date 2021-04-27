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
    indietro(MOT_R, V * 1.1);
    //fermo(MOT_R);
    avanti(MOT_L, V * 1.1);
  }

  if (digitalRead(LS_PIN) && !(digitalRead(RS_PIN))) // turn left
  {
    avanti(MOT_R, V * 1.1);
    indietro(MOT_L, V * 1.1);
    //fermo(MOT_L);
  }

  if (digitalRead(LS_PIN) && digitalRead(RS_PIN)) // stop
  {
    fermo(MOT_R);
    fermo(MOT_L);
    return true;
  }
  /*
    if (digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(LLS_PIN) && digitalRead(RRS_PIN)) // stop
    {
      fermo(MOT_R);
      fermo(MOT_L);
      return true;
    }*/
  return false;
}

bool following_forward2() {

  int Input = readSens();

  if (Input == 0) // Move Forward
  {
    avanti(MOT_R, V);
    avanti(MOT_L, V);
  }

  if (Input == 1 || Input == 2 || Input == 3) // Turn right
  {
    indietro(MOT_R, V * 0.8);
    avanti(MOT_L, V*0.9);
  }
/*
  if (Input == 2 || Input == 3) // Turn right
  {
    indietro(MOT_R, V * 0.8);
    avanti(MOT_L, V *0.9);
  }*/

  if (Input == -1 || Input == -2 || Input == -3) // turn left
  {
    avanti(MOT_R, 230);
    indietro(MOT_L, 230);
  }

/*
  if (Input == -2 || Input == -3) // Turn left
  {
    avanti(MOT_R, 230);
    indietro(MOT_L, 230);
  }*/

  if (Input == 10) // stop
  {
    fermo(MOT_R);
    fermo(MOT_L);
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
    indietro(MOT_R, int(V * 1.2));
    avanti(MOT_L, int(V * 1.1));
  }

  if (digitalRead(LS_PIN) && !(digitalRead(RS_PIN))) // turn left
  {
    avanti(MOT_R, int(V * 1.1));
    indietro(MOT_L, int(V * 1.2));
  }

  if ((digitalRead(LS_PIN)) && (digitalRead(RS_PIN))) // stop
  {
    fermo(MOT_R);
    fermo(MOT_L);
  }
}

void follow() {

  Serial3.println("Seguo Linea");
  while (!following_forward2()) {
  }
  Serial3.println("Arrivato");
  delay(2000);
  Serial3.println("Riparto");
  move_forward(400, V);
  Serial3.println("Mosso");
}


double readSens() {

  LLS = 0;
  LS = 0;
  RS = 0;
  RRS = 0;
  double x;

  if (digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = -e3;
  }
  else if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = -e2;
  }
  else if (!digitalRead(LLS_PIN) && digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = -e1;
  }
  else if (!digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = 0;
  }
  else if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) {
    x = e1;
  }
  else if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) {
    x = e2;
  }
  else if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && digitalRead(RRS_PIN)) {
    x = e3;
  }
  else if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) {
    x = 10;
  }
  else{
    x=0;}
  Serial.println(x);

  return x;
}

bool checkLine() {
  if (digitalRead(LLS_PIN) || digitalRead(LS_PIN) || digitalRead(RS_PIN) || digitalRead(RRS_PIN))
    return true;
  else
    return false;
}
