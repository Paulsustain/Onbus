// Function to save a string to EEPROM
void saveStringToEEPROM(int address, const String& data) {
  int length = data.length();
  for (int i = 0; i < length; i++) {
    EEPROM.write(address + i, data[i]);
  }
  EEPROM.write(address + length, '\0'); // Null-terminate the string in EEPROM
  EEPROM.commit(); // Save the changes to EEPROM
  Serial.println("Korensi Id saved successully");
  
}


// Function to retrieve a string from EEPROM
String getStringFromEEPROM(int address) {
  String data = "";
  char character;
  int i = 0;
  do {
    character = EEPROM.read(address + i);
    data += character;
    i++;
  } while (character != '\0');
  return data;
}
