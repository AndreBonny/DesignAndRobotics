#define DATA_PIN 31
#define CS_PIN 33
#define CLK_PIN 32
#define INTENSITY 1

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

void write_eye(byte eye[8], int index, int del) {
  int row = 0, col = 7;
  while (row < 8 && col >= 0) {
    lc.setColumn(index, col, eye[row]);
    row++;
    col--;
  }
}

void draw_openclose() {  // duration 600 millis
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

//divided in two parts, it has to hold "scared" for some time
//then it has to be reset
void draw_scared_start() //duration 800 mills
{
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

void draw_scared_end()
{
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

void draw_surprised_start()
{
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

void draw_surprised_end()
{
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

void draw_sad_start()
{
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

void draw_sad_end()
{
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
void draw_sad_blink()
{
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
void draw_happy_start() //to do the first time there's a transition between neutral and happy
{
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
void draw_happy_end()//needs a draw_happy_close() before
{
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
void draw_happy_open()
{
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

void draw_happy_close()
{

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

void draw_happy_blink()
{
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
