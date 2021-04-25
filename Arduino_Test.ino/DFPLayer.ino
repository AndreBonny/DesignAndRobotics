#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

void Inizializza_DFPlayer() {
  Serial2.begin(9600);
  serial_write_debug(F("Initializing DFPlayer ..."));

  while (!myDFPlayer.begin(Serial2)) {
    serial_write_debug(F("Unable to begin DFPlayer"));
  }
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
 // myDFPlayer.outputSetting(true, 30);
  //myDFPlayer.sleep();
  serial_write_debug(F("DFPlayer Mini online."));

}

void play(Track track) {
  myDFPlayer.playMp3Folder(track);
}

void status() {
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(myDFPlayer.readVolume()); //read current volume
  Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  printDetail(myDFPlayer.readType(), myDFPlayer.read());
}

void stop_play()
{
  myDFPlayer.pause();
}

void sleep() {
 myDFPlayer.sleep();
}

bool dfNotPlaying()
{
  if (digitalRead(BUSY_PIN) == LOW)
  {
    return false;
  }
  return true;
}


void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}
