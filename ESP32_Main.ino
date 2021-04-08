#include <SR04.h>
#include "esp_camera.h"
#include "fd_forward.h"



#define LED_BUILTIN 4
#define TRIG_PIN 14
#define ECHO_PIN 15

SR04 HCSR04 = SR04(ECHO_PIN, TRIG_PIN);

// Per Flash
int freq = 5000;
int ledChannel = 3;
int ledResolution = 12;

// Pin e Channel servo
int tilt_pin = 13;
int pan_pin = 12;
int tilt_ch = 2;
int pan_ch = 4;

int tilt_center = 150;
int pan_center = 90;

int tilt_position;
int pan_position;

bool scansione = false;
bool trovato = false;

void setup() {
  //Flash
  ledcSetup(ledChannel, freq, ledResolution);
  ledcAttachPin(LED_BUILTIN, ledChannel);
  Inizializza_servo();
  Inizializza_camera();

  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("<Esp32 is ready>");
  delay(1000);

}


void loop() {
  //Test_camera();
 /* trovato = Search();
  while(trovato == true) {
    Face_tracking();
  }
  //distance = Distanza();
  //Serial.printf("l: %li cm \n", distance);
*/

   Face_tracking();

}

/*  String str = serial_read();
  if (str.length() > 0) {
    if (str == "OK") {
      Serial.println("OK");
      scansione = true;
    }
    if (str == "STOP") {
      Serial.println("STOP");
      scansione = false;
    }
  }

  if (scansione) {
    scan();
  }
  else {
    ledcAnalogWrite(tilt_ch, tilt_center);
    ledcAnalogWrite(pan_ch, pan_center);
  }

  delay(50);*/
