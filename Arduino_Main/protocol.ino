bool serial_write(String input) {
  char* cString = (char*) malloc(sizeof(char)*(input.length() + 1));
  input.toCharArray(cString, input.length() + 1);
  Serial1.write(cString);
}

bool serial_write_debug(String input) {
  input = "\n DEBUG ARDUINO " + input +"\n";
  char* cString = (char*) malloc(sizeof(char) * (input.length() + 1));
  input.toCharArray(cString, input.length() + 1);
  Serial.write(cString);
}

String serial_read() {
  if(Serial1.available() > 0) {
    return Serial1.readString();
  } else
    return "";
}
