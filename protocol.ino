bool serial_write(String input) {
  char* cString = (char*) malloc(sizeof(char) * (input.length() + 1));
  input.toCharArray(cString, input.length() + 1);
  Serial.write(cString);
}

String serial_read() {
  if (Serial.available() > 0) {
    return Serial.readString();
  } else
    return "";
}
