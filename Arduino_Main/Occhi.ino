#define DATA_PIN 31
#define CS_PIN 33
#define CLK_PIN 32
#define INTENSITY 8

LedControl lc = LedControl(DATA_PIN, CLK_PIN, CS_PIN, 2);

void Inizializza_Occhi() {
  //we have already set the number of devices when we created the LedControl
  int devices = lc.getDeviceCount();
  //we have to init all devices in a loop
  for (int address = 0; address < devices; address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address, false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address, INTENSITY);
    /* and clear the display */
    lc.clearDisplay(address);
  }
}


byte open_eye_1_0[8] = {
  B00000000,
  B00111000,
  B01111100,
  B11111110,
  B11111110,
  B11111110,
  B01111100,
  B00111000
};

byte open_eye_2_0[8] = {
  B00000000,
  B00000000,
  B01111100,
  B11111110,
  B11111110,
  B11111110,
  B01111100,
  B00000000,
};

byte open_eye_3_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B11111110,
  B11111110,
  B11111110,
  B00000000,
  B00000000,
};

byte open_eye_4_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B11111110,
  B11111110,
  B00000000,
  B00000000,
  B00000000,
};

byte closed_eye_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000,
};

byte open_eye_1_1[8] = {
  B00000000,
  B00011100,
  B00111110,
  B01111111,
  B01111111,
  B01111111,
  B00111110,
  B00011100
};

byte open_eye_2_1[8] = {
  B00000000,
  B00000000,
  B00111110,
  B01111111,
  B01111111,
  B01111111,
  B00111110,
  B00000000,
};

byte open_eye_3_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111111,
  B01111111,
  B01111111,
  B00000000,
  B00000000,
};

byte open_eye_4_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111111,
  B01111111,
  B00000000,
  B00000000,
  B00000000,
};

byte closed_eye_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111111,
  B00000000,
  B00000000,
  B00000000,
};

byte scarred_eye_1_0[8] = {
  B00000000,
  B00000000,
  B01111000,
  B00111100,
  B00111110,
  B00111100,
  B01111000,
  B00000000,
};

byte scarred_eye_2_0[8] = {
  B00000000,
  B00000000,
  B01110000,
  B00111100,
  B00011110,
  B00111100,
  B01110000,
  B00000000,
};

byte scarred_eye_3_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111100,
  B00011110,
  B01111100,
  B00000000,
  B00000000,
};

byte scarred_eye_4_0[8] = {
  B00000000,
  B00000000,
  B01110000,
  B00001100,
  B00000110,
  B00001100,
  B01110000,
  B00000000,
};

byte scarred_eye_1_1[8] = {
  B00000000,
  B00000000,
  B01111000,
  B00111100,
  B00111110,
  B00111100,
  B01111000,
  B00000000,
};

byte scarred_eye_2_1[8] = {
  B00000000,
  B00000000,
  B01110000,
  B00111100,
  B00011110,
  B00111100,
  B01110000,
  B00000000,
};

byte scarred_eye_3_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111100,
  B00011110,
  B01111100,
  B00000000,
  B00000000,
};

byte scarred_eye_4_1[8] = {
  B00000000,
  B00000000,
  B01110000,
  B00001100,
  B00000110,
  B00001100,
  B01110000,
  B00000000,
};

byte empty_eye[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

void write_eye(byte eye[8], int index, int del) {
  int row = 0, col = 7;
  while (row < 8 && col >= 0) {
    lc.setColumn(index, col, eye[row]);
    row++;
    col--;
  }
}

void draw_scanning_R() {
  write_eye(open_eye_1_0, 0, 500);
  write_eye(open_eye_2_0, 0, 500);
  write_eye(open_eye_3_0, 0, 500);
  //write_eye(open_eye_4_0, 0, 500);
  //write_eye(empty_eye, 0, 500);
}

void draw_scanning_L() {
  write_eye(open_eye_1_1, 1, 500);
  write_eye(open_eye_2_1, 1, 500);
  write_eye(open_eye_3_1, 1, 500);
  //write_eye(open_eye_4_1, 1, 500);
  //write_eye(empty_eye, 1, 500);
}

void draw_openclose() {
  write_eye(open_eye_1_0, 0, 0);
  write_eye(open_eye_1_1, 1, 0);
  delay(50);

  write_eye(open_eye_2_0, 0, 50);
  write_eye(open_eye_2_1, 1, 50);
  delay(50);

  write_eye(open_eye_3_0, 0, 50);
  write_eye(open_eye_3_1, 1, 50);
  delay(50);

  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(50);

  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(200);

  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(50);

  write_eye(open_eye_3_0, 0, 50);
  write_eye(open_eye_3_1, 1, 50);
  delay(50);

  write_eye(open_eye_2_0, 0, 50);
  write_eye(open_eye_2_1, 1, 50);
  delay(50);

  write_eye(open_eye_1_0, 0, 50);
  write_eye(open_eye_1_1, 1, 50);
  delay(50);
}



void draw_scarred_R() {
  write_eye(open_eye_1_0, 0, 50);
  write_eye(scarred_eye_2_0, 0, 50);
  write_eye(scarred_eye_3_0, 0, 50);
  write_eye(scarred_eye_4_0, 0, 500);
}

void draw_scarred_L() {
  write_eye(open_eye_1_1, 1, 50);
  write_eye(scarred_eye_2_1, 1, 50);
  write_eye(scarred_eye_3_1, 1, 50);
  write_eye(scarred_eye_4_1, 1, 500);
}

void prova() {
  lc.setColumn(0, 2, B11001100);
}
