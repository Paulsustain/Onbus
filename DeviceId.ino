
String getESP32MACAddress() {
  // Initialize WiFi library
  WiFi.mode(WIFI_OFF);

  // Get MAC address
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  // Format MAC address as a string
  char macStr[18] = {0};
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println("Mac address: " + String(macStr));
  return String(macStr);
}

