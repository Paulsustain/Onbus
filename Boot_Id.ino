void deviceIdChecker() {
    while (!checkKorensiId()) {
        delay(1000);  // Add a delay to prevent busy waiting
    }
}

bool checkKorensiId() {
    retrievedString = getStringFromEEPROM(30);
    Serial.println("Retrieved String: " + retrievedString);
    
    if (retrievedString[0] == 'K') {
        return true;
    } else {
        Serial.println("No Korensi Id");
        String mac = getESP32MACAddress();
        String formattedMac = removeColons(mac);
        String Korensi_id = HTTP_GET_REQUEST_OnBus(formattedMac);
        saveStringToEEPROM(30, Korensi_id);
        return false;  // Return false when retrieving and saving Korensi Id
    }
}

String removeColons(const String& inputString) {
    String result;
    for (char c : inputString) {
        if (c != ':') {
            result += c;
        }
    }
    return result;
}

