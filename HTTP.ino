bool searchString(const String& str, String target) {
  //String target = "User with this phone number does not exist or is not verified";
  return str.indexOf(target) != -1;
}

String HTTP_get_request(String api_url,String Korensi_Id) {
  char save[445];
  char save1[30];
  int counter = 0;
  long int i = 0;
  String resaved="";
  SIM800.println("AT+HTTPINIT");
  vTaskDelay(pdMS_TO_TICKS(50));
  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"CID\",1");
  vTaskDelay(pdMS_TO_TICKS(50));
  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  String url_with_params = api_url + "?device_uid=" + Korensi_Id;
  SIM800.println("AT+HTTPPARA=\"URL\",\"" + url_with_params + "\"");
  vTaskDelay(pdMS_TO_TICKS(500));
  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPACTION=0");
  vTaskDelay(pdMS_TO_TICKS(100));
  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  for (;;) {
    
    if (SIM800.available()) {
      char c = SIM800.read();
      save1[i] = c;
     // Serial.print("len: ");
      Serial.print(save[i]);
      if (i >= 23) {
        i = 0;
        break;
      }
      i++;
    }
  }
  
  SIM800.println("AT+HTTPREAD");
   Serial.println();
   i=0;
  for (;;) {
    
    if (SIM800.available()) {
      char c = SIM800.read();
      // Serial.println(c);
      save[i] = c;
      Serial.print(save[i]);
     
    if(i>=445){
      Serial.println();
       save[i] = '\0';
       String savedString(save);
       int len=savedString.length(); 
       Serial.print("Response Length is: ");
       Serial.println(len);
       resaved=savedString;
      i=0;
      break;
    }
    
      i++;
    } 
     
  }
  Serial.println("FINISHED");
  SIM800.println("AT+HTTPTERM");
  vTaskDelay(pdMS_TO_TICKS(100));
   //Serial.println("Extracted Message: " + resaved);
  return resaved;
}


String HTTP_GET_REQUEST_OnBus(String Korensi_Id){
//unsigned long startTime = millis();
 bool found;
 String resp= HTTP_get_request(getapi_url,Korensi_Id);
 String modifiedString = removeCharacters(resp,337,93); // phone does not exist
 Serial.print("Modified String is : "); 
 Serial.println(modifiedString.length()); 
 Serial.println("Extracted Message: " + modifiedString);
 
 
return modifiedString;
}



String HTTP_post_request_pay(String api_url,String Amount,String card_id,String Korensi_Id){
  char save[160];
  int counter=0;
  int i=0;
  String ntn="";
  
  SIM800.println("AT+HTTPINIT");
   vTaskDelay(pdMS_TO_TICKS(50));
 if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }  
  SIM800.println("AT+HTTPPARA=\"CID\",1");
  vTaskDelay(pdMS_TO_TICKS(50));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"URL\",\"" + api_url + "\"");
  vTaskDelay(pdMS_TO_TICKS(100));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  vTaskDelay(pdMS_TO_TICKS(50));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
  
  int amt=10;
  const char* device=Korensi_Id.c_str();
  
 // String body = "{\"card_number\":\"" + card_id + "\",\"device\":\"" + koren_id + "\",\"amount\":" + String(amt) + "}";
  //String body = "{\"card_number\":\"" + card_id + "\",\"amount\":" + String(amt) + ",\"device\":\"" + Korensi_Id + "\"}";
    //String body = "{\"card_number\":\"" + card_id + "\",\"amount\":" + String(amt) + ",\"device\":\"K16911419475295\"}";
     //String body = "{\"card_number\":\"" + card_id + "\",\"amount\":" + String(amt) + ",\"device\":\"" + Korensi_Id + "\"}";
     //String body = "{\"device\":\"" + Korensi_Id + "\",\"card_number\":\"" + card_id + "\",\"amount\":" + String(amt) + "}";
    // String body = "{\"device\":\"" + String(Korensi_Id) + "\",\"card_number\":\"" + card_id + "\",\"amount\":" + String(amt) + "}";
  String body = "{\"device\":\"";
  body += String(device);
  body += "\",\"card_number\":\"";
  body += card_id;
  body += "\",\"amount\":";
  body += amt;
  body += "}";

   
  SIM800.println("AT+HTTPDATA=" + String(body.length()) + ",10000");
  vTaskDelay(pdMS_TO_TICKS(100));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
  Serial.println(body);
  SIM800.println(body);
 vTaskDelay(pdMS_TO_TICKS(100));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+HTTPACTION=1");
  vTaskDelay(pdMS_TO_TICKS(100));
   if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
 
  for(;;){
 
  if (SIM800.available()) {
    
    char c  = SIM800.read();
      save[i]=c;
      Serial.print(save[i]);     
      if(i>=20){
        // Serial.println("finishing");
        i=0; 
        break;        
      }
      i++;
     }
  //Serial.println("Loop");
  
}
  
  SIM800.println("AT+HTTPREAD");
  vTaskDelay(pdMS_TO_TICKS(400));
 /* 
 if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }  

  */
  for(;;){

  if (SIM800.available()) {
    
    char c  = SIM800.read();
      save[i]=c;
      //Serial.println(save[i]);
      
    }
     if(i>=157){
       save[i] = '\0';
        String savedString(save);
        int len=savedString.length(); 
       Serial.println(len);
        i=0;
        SIM800.println("AT+HTTPTERM");
        return (savedString);
      }  

      else if(counter>=2000){
       goto end;
        
      }      
      i++;
   }
   end:
  SIM800.println("AT+HTTPTERM");
  vTaskDelay(pdMS_TO_TICKS(100));

}

String removeCharacters(String inputString, int start, int end) {
  if (inputString.length() >= start + end) {
    return inputString.substring(start, inputString.length() - end);
  }
  return "";
}





void Initialize_GPRS(String apn){

  /*
  SIM800.println("AT"); // Check if SIM800 is responding
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
  */
  /*
   SIM800.println("ATE0"); // Check if SIM800 is responding
  delay(100);

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }
  */
  DeviceStartup();
  for(int i=0;i<2;i++){
  SIM800.println("AT"); // Check if SIM800 is responding
  vTaskDelay(pdMS_TO_TICKS(1000));
  SIM800.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  vTaskDelay(pdMS_TO_TICKS(1000));

  if (SIM800.available()) {
    String response = SIM800.readString();
    Serial.println(response);
  }

  SIM800.println("AT+SAPBR=3,1,\"APN\",\"" + apn + "\"");// Network provider APN 
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
  KorensiLogo();
  }

}

int HTTP_POST_REQUEST_OnBus(){
unsigned long startTime = millis();
bool found;
//String uniqueID = getESP32MACAddress();
 //String resp= HTTP_post_request_pay(Agent_URL,Tripcost,HexString,retrievedString);
 String retrievedString = getStringFromEEPROM(30);
 String resp= HTTP_post_request_pay(Agent_URL,Tripcost,HexString,retrievedString);
 Serial.print("tripcost is: "); 
 Serial.println(Tripcost); 
 Serial.print("card id is "); 
 Serial.println(HexString);  
 String modifiedString = removeCharacters(resp,50,3); // phone does not exist
 Serial.print("Modified String is : "); 
 Serial.println(modifiedString.length()); 
 Serial.println("Extracted Message: " + modifiedString);
 found = searchString(modifiedString,card_not_found);
 if(found){
  Serial.println("found error :" + card_not_found); 
  goto err1;
 }

found = searchString(modifiedString,insufficient); 
if(found){
  Serial.println("found error :" + insufficient); 
  goto err4;
 }
 found = searchString(modifiedString,success); 
if(found){
  Serial.println("found error :" + success); 
  goto err2;
 }
err1: 
error001();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
err4: 
error004();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
err2: 
error002();
digitalWrite(Green,HIGH);
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
error003();
vTaskDelay(pdMS_TO_TICKS(3000));
return 1;
}
