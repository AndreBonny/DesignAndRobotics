#define RRS_PIN 49
#define RS_PIN 48
#define LS_PIN 47
#define LLS_PIN 46

double RRS;
double RS;
double LS;
double LLS;

// setup the sensors
void sensor_setup() {
  pinMode(RRS_PIN, INPUT);
  pinMode(RS_PIN, INPUT);
  pinMode(LS_PIN, INPUT);
  pinMode(LLS_PIN, INPUT);
}

// uses only the central sensors
bool following_forward() {

  // none of the central sensors see the black line
  // Move Forward
  if (!digitalRead(LS_PIN) && !digitalRead(RS_PIN)) {
    forward(MOT_R, V);
    forward(MOT_L, V);
  }

  // the central right sensor sees the line, while the central left one doesn't
  // Turn right
  if (!(digitalRead(LS_PIN)) && digitalRead(RS_PIN)) {
    backward(MOT_R, V * 1.1);
    forward(MOT_L, V * 1.1);
  }

  // the central left sensor sees the line, while the central right one doesn't
  // turn left
  if (digitalRead(LS_PIN) && !(digitalRead(RS_PIN))) {
    forward(MOT_R, V * 1.1);
    backward(MOT_L, V * 1.1);
  }

  // both of the central sensors see the black line
  // stop
  if (digitalRead(LS_PIN) && digitalRead(RS_PIN)) {
    stop(MOT_R);
    stop(MOT_L);
    return true;
  }

  return false;
}

// uses all the four sensors
bool following_forward2() {

  int Input = readSens();

  // Move Forward
  if (Input == 0) {
    forward(MOT_R, V);
    forward(MOT_L, V);
  }

  // Turn right
  if (Input == 1 || Input == 2 || Input == 3) {
    backward(MOT_R, V );
    forward(MOT_L, V * 0.9);
  }

  // turn left
  if (Input == -1 || Input == -2 || Input == -3) {
    forward(MOT_R, V * 1.4);
    backward(MOT_L, V * 0.8);
  }

  // stop
  if (Input == 10) {
    stop(MOT_R);
    stop(MOT_L);
    return true;
  }

  return false;
}

void following_backward() {

  // Move Forward
  if (!digitalRead(LS_PIN) && !digitalRead(RS_PIN)) {
    backward(MOT_R, V);
    backward(MOT_L, V);
  }

  // Turn right
  if (!(digitalRead(LS_PIN)) && digitalRead(RS_PIN)) {
    backward(MOT_R, int(V * 1.2));
    forward(MOT_L, int(V * 1.0));
  }

  // turn left
  if (digitalRead(LS_PIN) && !(digitalRead(RS_PIN))) {
    forward(MOT_R, int(V * 1.1));
    backward(MOT_L, int(V * 1.2));
  }

  // stop
  if ((digitalRead(LS_PIN)) && (digitalRead(RS_PIN))) {
    stop(MOT_R);
    stop(MOT_L);
  }
}

// returns how much the robot should rotate
double readSens() {

  LLS = 0;
  LS = 0;
  RS = 0;
  RRS = 0;
  double x;

  // left
  if (digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) { x = -3; }
  else if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) { x = -2; }
  else if (!digitalRead(LLS_PIN) && digitalRead(LS_PIN) && !digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) { x = -1; }
  
  // forward
  else if (!digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) { x = 0; }
  
  // right
  else if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) { x = 1; }
  else if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) { x = 2; }
  else if (!digitalRead(LLS_PIN) && !digitalRead(LS_PIN) && !digitalRead(RS_PIN) && digitalRead(RRS_PIN)) { x = 3; }

  // stop
  else if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && !digitalRead(RRS_PIN)) { x = 10; }
  else if (!digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) { x = 10; }
  else if (digitalRead(LLS_PIN) && digitalRead(LS_PIN) && digitalRead(RS_PIN) && digitalRead(RRS_PIN)) { x = 10; }
  
  // forward
  else { x = 0; }

  return x;
}

// returns true if any of the sensors detect the line, else returns false
bool checkLine() {
  if (digitalRead(LLS_PIN) || digitalRead(LS_PIN) || digitalRead(RS_PIN) || digitalRead(RRS_PIN))
    return true;
  else
    return false;
}
