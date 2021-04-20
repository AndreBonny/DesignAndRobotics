#include <AFMotor.h>
#include <PID_v1.h>


#define MOT_R 4
#define MOT_L 1
#define V  150
#define Omega  240



double Setpoint, Input, Output;
int Speed_R, Speed_L;

double Kp = 2*V, Ki = 0 , Kd = 0;
PID PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  PID.SetMode(AUTOMATIC);
  PID.SetSampleTime(1);
  PID.SetOutputLimits(-500, 500);

  Inizializza_sensori();
  Inizializza_Motori();

  Serial3.println("START");

  delay(2000);
}


void loop() {
  //avanti(MOT_L,200);
  //fermo(MOT_R);
  following_PID();
  //readSens();

 // follow();
  /*  int x = 0;
    if(Serial.available()>0){
     x = Serial.parseInt();
     Serial.println(x);
    }

     move(MOT_L,x);
     move(MOT_R,x);
     delay(1000);*/
}
