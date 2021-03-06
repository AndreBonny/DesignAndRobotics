void eyes_setup() {
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

byte scared_eye_5_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000,
};

byte scared_eye_6_0[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111100,
  B00000110,
  B01111100,
  B00000000,
  B00000000,
};

byte scared_eye_7_0[8] = {
  B00000000,
  B00000000,
  B01110000,
  B00001100,
  B00000010,
  B00001100,
  B01110000,
  B00000000,
};

byte scared_eye_5_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01111111,
  B00000000,
  B00000000,
  B00000000,
};
byte scared_eye_6_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00111110,
  B01100000,
  B00111110,
  B00000000,
  B00000000,
};

byte scared_eye_7_1[8] = {
  B00000000,
  B00000000,
  B00001110,
  B00110000,
  B01000000,
  B00110000,
  B00001110,
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



byte sad_eye_R_1[8] = {
  B00000000,
  B00000000,
  B01111100,
  B11111100,
  B11111100,
  B11111000,
  B00000000,
  B00000000
};
byte sad_eye_R_2[8] = {
  B00000000,
  B00000000,
  B01111100,
  B11111100,
  B11111100,
  B11111000,
  B01110000,
  B00000000
};
byte sad_eye_R_3[8] = {
  B00000000,
  B00111000,
  B01111100,
  B11111100,
  B11111100,
  B11111000,
  B01110000,
  B00100000
};

byte sad_eye_L_1[8] = {
  B00000000,
  B00000000,
  B00111110,
  B00111111,
  B00111111,
  B00011111,
  B0000000,
  B00000000
};
byte sad_eye_L_2[8] = {
  B00000000,
  B00000000,
  B00111110,
  B00111111,
  B00111111,
  B00011111,
  B00001110,
  B00000000
};
byte sad_eye_L_3[8] = {
  B00000000,
  B00011100,
  B00111110,
  B00111111,
  B00111111,
  B00011111,
  B00001110,
  B00000100
};


byte surprised_eye_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00000000,
  B00000000,
  B00000000
};
byte surprised_eye_2[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};
byte surprised_eye_3[8] = {
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00011000,
  B00000000,
  B00011000,
  B00000000
};
byte surprised_eye_4[8] = {
  B00000000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00000000,
  B00011000,
  B00011000
};

byte happy_eye_R_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B11111110,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte happy_eye_R_2[8] = {
  B00000000,
  B00000000,
  B01111100,
  B11111110,
  B11111110,
  B11101110,
  B00000000,
  B00000000
};

byte happy_eye_R_3[8] = {
  B00000000,
  B00111000,
  B01111100,
  B11111110,
  B11111110,
  B11101110,
  B01000100,
  B00000000
};
byte happy_eye_L_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B01111111,
  B01111111,
  B00000000,
  B00000000,
  B00000000
};
byte happy_eye_L_2[8] = {
  B00000000,
  B00000000,
  B00111110,
  B01111111,
  B01111111,
  B01110111,
  B00000000,
  B00000000
};
byte happy_eye_L_3[8] = {
  B00000000,
  B00011100,
  B00111110,
  B01111111,
  B01111111,
  B01110111,
  B00100010,
  B00000000
};


byte correct_eye_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B00000000,
  B00000000,
  B00000000
};

byte correct_eye_2[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B00000000,
  B00000000
};

byte correct_eye_3[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B01100000,
  B00000000
};

byte correct_eye_4[8] = {
  B00000000,
  B0000000,
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B0110000,
  B00100000
};
byte correct_eye_5[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B11010000,
  B01110000,
  B00100000
};
byte correct_eye_6[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10001100,
  B11011000,
  B01110000,
  B00100000
};
byte correct_eye_7[8] = {
  B00000000,
  B00000001,
  B00000011,
  B00000110,
  B10001100,
  B11011000,
  B01110000,
  B00100000
};
byte correct_eye_8[8] = {
  B00000000,
  B00000000,
  B00000011,
  B00000110,
  B10001100,
  B11011000,
  B01110000,
  B00000000
};
byte correct_eye_9[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000110,
  B10011100,
  B11011000,
  B00000000,
  B00000000
};

byte correct_eye_10[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11011100,
  B00000000,
  B00000000,
  B00000000
};

byte shrinking_eye_1[8] = {
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

byte shrinking_eye_2[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B00011000,
  B00000000,
  B00000000
};

byte shrinking_eye_3[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};

byte wrong_eye_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00011000,
  B00111100,
  B00000000,
  B00000000
};

byte wrong_eye_2[8] = {
  B00000000,
  B00000000,
  B01100110,
  B00111100,
  B00011000,
  B00111100,
  B01100110,
  B00000000
};

byte wrong_eye_3[8] = {
  B00000000,
  B11000011,
  B01100110,
  B00111100,
  B00011000,
  B00111100,
  B01100110,
  B11000011
};

byte wrong_eye_4_R[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00111000,
  B00000000,
  B00000000,
  B00000000
};

byte wrong_eye_4_L[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011100,
  B00000000,
  B00000000,
  B00000000
};

byte question_eye_1[8] = {
  B00000000,
  B00000000,
  B01100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte question_eye_2[8] = {
  B00011000,
  B00100000,
  B01100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte question_eye_3[8] = {
  B00011000,
  B00100100,
  B01100000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte question_eye_4[8] = {
  B00011000,
  B00100100,
  B01100110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte question_eye_5[8] = {
  B00011000,
  B00100100,
  B01100110,
  B00001100,
  B00011000,
  B00000000,
  B00000000,
  B00000000
};

byte question_eye_6[8] = {
  B00011000,
  B00100100,
  B01100110,
  B00001100,
  B00011000,
  B00000000,
  B00011000,
  B00011000
};


byte angry_eye_R_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B11111000,
  B11111110,
  B11111110,
  B00000000,
  B00000000
};

byte angry_eye_R_2[8] = {
  B00000000,
  B00000000,
  B01110000,
  B11111000,
  B11111110,
  B11111110,
  B01111100,
  B00000000
};

byte angry_eye_R_3[8] = {
  B00000000,
  B00100000,
  B01110000,
  B11111000,
  B11111110,
  B11111110,
  B01111100,
  B00111000
};

byte angry_eye_L_1[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00011111,
  B01111111,
  B01111111,
  B00000000,
  B00000000
};

byte angry_eye_L_2[8] = {
  B00000000,
  B00000000,
  B00001110,
  B00011111,
  B01111111,
  B01111111,
  B00111110,
  B00000000
};

byte angry_eye_L_3[8] = {
  B00000000,
  B00000100,
  B00001110,
  B00011111,
  B01111111,
  B01111111,
  B00111110,
  B00011100
};

void write_eye(byte eye[8], int index, int del) {
  int row = 0, col = 7;
  while (row < 8 && col >= 0) {
    lc.setColumn(index, col, eye[row]);
    row++;
    col--;
  }
}

// duration 600 millis
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
  delay(1000);
}

// divided in two parts, it has to hold "scared" for some time
// then it has to be reset
// duration 800 millis
void draw_scared_start() {
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
  write_eye(scared_eye_5_0, 0, 500);
  write_eye(scared_eye_5_1, 1, 500);
  delay(150);
  write_eye(scared_eye_6_0, 0, 500);
  write_eye(scared_eye_6_1, 1, 500);
  delay(150);
  write_eye(scared_eye_7_0, 0, 500);
  write_eye(scared_eye_7_1, 1, 500);
}

void draw_scared_end() {
  write_eye(scared_eye_7_0, 0, 500);
  write_eye(scared_eye_7_1, 1, 500);
  delay(150);
  write_eye(scared_eye_6_0, 0, 500);
  write_eye(scared_eye_6_1, 1, 500);
  delay(150);
  write_eye(scared_eye_5_0, 0, 500);
  write_eye(scared_eye_5_1, 1, 500);
  delay(150);
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
  delay(1000);
}

void draw_surprised_start() {
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
  delay(50);
  write_eye(surprised_eye_1, 0, 50);
  write_eye(surprised_eye_1, 1, 50);
  delay(25);
  write_eye(surprised_eye_2, 0, 50);
  write_eye(surprised_eye_2, 1, 50);
  delay(25);
  write_eye(surprised_eye_3, 0, 50);
  write_eye(surprised_eye_3, 1, 50);
  delay(25);
  write_eye(surprised_eye_4, 0, 50);
  write_eye(surprised_eye_4, 1, 50);
}

void draw_surprised_end() {
  write_eye(surprised_eye_4, 0, 50);
  write_eye(surprised_eye_4, 1, 50);
  delay(25);
  write_eye(surprised_eye_3, 0, 50);
  write_eye(surprised_eye_3, 1, 50);
  delay(25);
  write_eye(surprised_eye_2, 0, 50);
  write_eye(surprised_eye_2, 1, 50);
  delay(25);
  write_eye(surprised_eye_1, 0, 50);
  write_eye(surprised_eye_1, 1, 50);
  delay(25);
  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(50);
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
  delay(1000);
}

void draw_sad_start() {
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
  delay(50);
  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(50);
  write_eye(sad_eye_R_1, 0, 50);
  write_eye(sad_eye_L_1, 1, 50);
  delay(150);
  write_eye(sad_eye_R_2, 0, 50);
  write_eye(sad_eye_L_2, 1, 50);
  delay(150);
  write_eye(sad_eye_R_3, 0, 50);
  write_eye(sad_eye_L_3, 1, 50);
  delay(150);
}

void draw_sad_end() {
  write_eye(sad_eye_R_3, 0, 50);
  write_eye(sad_eye_L_3, 1, 50);
  delay(100);
  write_eye(sad_eye_R_2, 0, 50);
  write_eye(sad_eye_L_2, 1, 50);
  delay(100);
  write_eye(sad_eye_R_1, 0, 50);
  write_eye(sad_eye_L_1, 1, 50);
  delay(100);
  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(100);
  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(50);
  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(50);
  write_eye(open_eye_3_0, 0, 50);
  write_eye(open_eye_3_1, 1, 50);
  delay(50);
  write_eye(open_eye_2_0, 0, 50);
  write_eye(open_eye_2_1, 1, 50);
  delay(50);
  write_eye(open_eye_1_0, 0, 0);
  write_eye(open_eye_1_1, 1, 0);
  delay(300);
}
void draw_sad_blink() {
  write_eye(sad_eye_R_3, 0, 50);
  write_eye(sad_eye_L_3, 1, 50);
  delay(65);
  write_eye(sad_eye_R_2, 0, 50);
  write_eye(sad_eye_L_2, 1, 50);
  delay(65);
  write_eye(sad_eye_R_1, 0, 50);
  write_eye(sad_eye_L_1, 1, 50);
  delay(65);
  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(65);
  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(50);
  write_eye(sad_eye_R_1, 0, 50);
  write_eye(sad_eye_L_1, 1, 50);
  delay(65);
  write_eye(sad_eye_R_2, 0, 50);
  write_eye(sad_eye_L_2, 1, 50);
  delay(65);
  write_eye(sad_eye_R_3, 0, 50);
  write_eye(sad_eye_L_3, 1, 50);
  delay(65);
}

// to do the first time there's a transition between neutral and happy
void draw_happy_start() {
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
  delay(50);
}

// needs a draw_happy_close() before
void draw_happy_end() {
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
  delay(1000);
}

void draw_happy_open() {
  write_eye(happy_eye_R_1, 0, 200);
  write_eye(happy_eye_L_1, 1, 200);
  delay(50);
  write_eye(happy_eye_R_2, 0, 200);
  write_eye(happy_eye_L_2, 1, 200);
  delay(50);
  write_eye(happy_eye_R_3, 0, 200);
  write_eye(happy_eye_L_3, 1, 200);
  delay(50);
}

void draw_happy_close() {
  write_eye(happy_eye_R_3, 0, 200);
  write_eye(happy_eye_L_3, 1, 200);
  delay(50);
  write_eye(happy_eye_R_2, 0, 200);
  write_eye(happy_eye_L_2, 1, 200);
  delay(50);
  write_eye(happy_eye_R_1, 0, 200);
  write_eye(happy_eye_L_1, 1, 200);
  delay(50);
  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(50);

}

void draw_happy_blink() {
  draw_happy_close();
  draw_happy_open();
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


void draw_correct_eye_start() {
  write_eye(shrinking_eye_1, 0, 0);
  write_eye(shrinking_eye_1, 1, 0);
  delay(65);
  write_eye(shrinking_eye_2, 0, 0);
  write_eye(shrinking_eye_2, 1, 0);
  delay(65);
  write_eye(shrinking_eye_3, 0, 0);
  write_eye(shrinking_eye_3, 1, 0);
  delay(65);
  write_eye(empty_eye, 0, 500);
  write_eye(empty_eye, 1, 500);
  delay(65);
  write_eye(correct_eye_1, 0, 500);
  write_eye(correct_eye_1, 1, 500);
  delay(40);
  write_eye(correct_eye_2, 0, 500);
  write_eye(correct_eye_2, 1, 500);
  delay(30);
  write_eye(correct_eye_3, 0, 500);
  write_eye(correct_eye_3, 1, 500);
  delay(30);
  write_eye(correct_eye_4, 0, 500);
  write_eye(correct_eye_4, 1, 500);
  delay(30);
  write_eye(correct_eye_5, 0, 500);
  write_eye(correct_eye_5, 1, 500);
  delay(30);
  write_eye(correct_eye_6, 0, 500);
  write_eye(correct_eye_6, 1, 500);
  delay(30);
  write_eye(correct_eye_7, 0, 500);
  write_eye(correct_eye_7, 1, 500);

}

void draw_correct_eye_end() {
  write_eye(correct_eye_8, 0, 500);
  write_eye(correct_eye_8, 1, 500);
  delay(30);
  write_eye(correct_eye_9, 0, 500);
  write_eye(correct_eye_9, 1, 500);
  delay(50);
  write_eye(correct_eye_10, 0, 500);
  write_eye(correct_eye_10, 1, 500);
  delay(65);
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
}

void draw_wrong_eye_start() {
  write_eye(shrinking_eye_1, 0, 0);
  write_eye(shrinking_eye_1, 1, 0);
  delay(65);
  write_eye(shrinking_eye_2, 0, 0);
  write_eye(shrinking_eye_2, 1, 0);
  delay(65);
  write_eye(shrinking_eye_3, 0, 0);
  write_eye(shrinking_eye_3, 1, 0);
  delay(65);
  write_eye(empty_eye, 0, 500);
  write_eye(empty_eye, 1, 500);
  delay(65);
  write_eye(wrong_eye_1, 0, 500);
  write_eye(wrong_eye_1, 1, 500);
  delay(65);
  write_eye(wrong_eye_2, 0, 500);
  write_eye(wrong_eye_2, 1, 500);
  delay(65);
  write_eye(wrong_eye_3, 0, 500);
  write_eye(wrong_eye_3, 1, 500);
  delay(65);
}
void draw_wrong_eye_end() {
  write_eye(wrong_eye_3, 0, 500);
  write_eye(wrong_eye_3, 1, 500);
  delay(65);
  write_eye(wrong_eye_2, 0, 500);
  write_eye(wrong_eye_2, 1, 500);
  delay(65);
  write_eye(wrong_eye_1, 0, 500);
  write_eye(wrong_eye_1, 1, 500);
  delay(65);
  write_eye(empty_eye, 0, 500);
  write_eye(empty_eye, 1, 500);
  delay(65);
  write_eye(wrong_eye_4_R, 0, 500);
  write_eye(wrong_eye_4_L, 1, 500);
  delay(65);
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
}

void draw_question_start() {
  write_eye(shrinking_eye_1, 0, 0);
  write_eye(shrinking_eye_1, 1, 0);
  delay(65);
  write_eye(shrinking_eye_2, 0, 0);
  write_eye(shrinking_eye_2, 1, 0);
  delay(65);
  write_eye(shrinking_eye_3, 0, 0);
  write_eye(shrinking_eye_3, 1, 0);
  delay(65);
  write_eye(empty_eye, 0, 500);
  write_eye(empty_eye, 1, 500);
  delay(65);
  write_eye(question_eye_1, 0, 50);
  write_eye(question_eye_1, 1, 50);
  delay(30);
  write_eye(question_eye_2, 0, 50);
  write_eye(question_eye_2, 1, 50);
  delay(30);
  write_eye(question_eye_3, 0, 50);
  write_eye(question_eye_3, 1, 50);
  delay(30);
  write_eye(question_eye_4, 0, 50);
  write_eye(question_eye_4, 1, 50);
  delay(30);
  write_eye(question_eye_5, 0, 50);
  write_eye(question_eye_5, 1, 50);
  delay(30);
  write_eye(question_eye_6, 0, 50);
  write_eye(question_eye_6, 1, 50);
  delay(30);
}

void draw_question_end() {
  write_eye(question_eye_6, 0, 50);
  write_eye(question_eye_6, 1, 50);
  delay(30);
  write_eye(question_eye_5, 0, 50);
  write_eye(question_eye_5, 1, 50);
  delay(30);
  write_eye(question_eye_4, 0, 50);
  write_eye(question_eye_4, 1, 50);
  delay(30);
  write_eye(question_eye_3, 0, 50);
  write_eye(question_eye_3, 1, 50);
  delay(30);
  write_eye(question_eye_2, 0, 50);
  write_eye(question_eye_2, 1, 50);
  delay(30);
  write_eye(question_eye_1, 0, 50);
  write_eye(question_eye_1, 1, 50);
  delay(30);
  write_eye(empty_eye, 0, 500);
  write_eye(empty_eye, 1, 500);
  delay(65);
  write_eye(shrinking_eye_3, 0, 0);
  write_eye(shrinking_eye_3, 1, 0);
  delay(65);
  write_eye(shrinking_eye_2, 0, 0);
  write_eye(shrinking_eye_2, 1, 0);
  delay(65);
  write_eye(shrinking_eye_1, 0, 0);
  write_eye(shrinking_eye_1, 1, 0);
  delay(65);
  write_eye(open_eye_1_0, 0, 0);
  write_eye(open_eye_1_1, 1, 0);

}

void draw_angry_start() {
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
  delay(50);
  write_eye(angry_eye_R_1, 0, 50);
  write_eye(angry_eye_L_1, 1, 50);
  delay(50);
  write_eye(angry_eye_R_2, 0, 50);
  write_eye(angry_eye_L_2, 1, 50);
  delay(50);
  write_eye(angry_eye_R_3, 0, 50);
  write_eye(angry_eye_L_3, 1, 50);
  delay(50);
}

void draw_angry_end() {
  write_eye(angry_eye_R_3, 0, 50);
  write_eye(angry_eye_L_3, 1, 50);
  delay(50);
  write_eye(angry_eye_R_2, 0, 50);
  write_eye(angry_eye_L_2, 1, 50);
  delay(50);
  write_eye(angry_eye_R_1, 0, 50);
  write_eye(angry_eye_L_1, 1, 50);
  delay(50);
  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(50);
  write_eye(open_eye_4_0, 0, 50);
  write_eye(open_eye_4_1, 1, 50);
  delay(50);
  write_eye(open_eye_3_0, 0, 50);
  write_eye(open_eye_3_1, 1, 50);
  delay(50);
  write_eye(open_eye_2_0, 0, 50);
  write_eye(open_eye_2_1, 1, 50);
  delay(50);
  write_eye(open_eye_1_0, 0, 0);
  write_eye(open_eye_1_1, 1, 0);
  delay(50);

}

void draw_angry_blink() {
  write_eye(angry_eye_R_3, 0, 50);
  write_eye(angry_eye_L_3, 1, 50);
  delay(50);
  write_eye(angry_eye_R_2, 0, 50);
  write_eye(angry_eye_L_2, 1, 50);
  delay(50);
  write_eye(angry_eye_R_1, 0, 50);
  write_eye(angry_eye_L_1, 1, 50);
  delay(50);
  write_eye(closed_eye_0, 0, 200);
  write_eye(closed_eye_1, 1, 200);
  delay(50);
  write_eye(angry_eye_R_1, 0, 50);
  write_eye(angry_eye_L_1, 1, 50);
  delay(50);
  write_eye(angry_eye_R_2, 0, 50);
  write_eye(angry_eye_L_2, 1, 50);
  delay(50);
  write_eye(angry_eye_R_3, 0, 50);
  write_eye(angry_eye_L_3, 1, 50);
  delay(50);
}
