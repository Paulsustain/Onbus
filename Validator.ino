
void Nfc_connect(){
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  Serial.println("Waiting for an ISO14443A card"); 
}




void validatorTask(void *parameter){ 
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength; 
   while(1){   
  if(xSemaphoreTake(xSemaphorehttp, portMAX_DELAY)){  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success)
  {
    char hexStr[3];
    int offset=0;
   for (uint8_t i=0; i < uidLength; i++) 
    {
      sprintf(hexStr+offset,"%02X",uid[i]);
      offset+=2;  
    }

    HexString =  String (hexStr);
    Serial.print("The UUID is :"); 
    Serial.println(HexString);
    vTaskSuspend(TaskBatteryBar);
    //vTaskSuspend(Taskhttpconnect);      
    Tag_accept();
    buzzer_click();
    Led_processing1();
    HTTP_POST_REQUEST_OnBus();
    Led_processing_end();
    //vTaskResume(Taskhttpconnect);
    vTaskResume(TaskBatteryBar); 
     
  }
  xSemaphoreGive(xSemaphorehttp);
  }
  else
  {
    // PN532 probably timed out waiting for a card
    // Serial.println("Timed out waiting for a card");
  }
  vTaskDelay(pdMS_TO_TICKS(100));
 
  } 
  
}


void httpconnect(void *parameter){ 

  while(1){   
    
  if(xSemaphoreTake(xSemaphorehttp, portMAX_DELAY)){  
  SIM800.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  vTaskDelay(pdMS_TO_TICKS(1000));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+SAPBR=3,1,\"APN\",\"" + APN + "\"");// Network provider APN 
  vTaskDelay(pdMS_TO_TICKS(1000));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+SAPBR=1,1");
  vTaskDelay(pdMS_TO_TICKS(1000));
  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
  xSemaphoreGive(xSemaphorehttp);
  }

   vTaskDelay(pdMS_TO_TICKS(300000));
   }
  
}

