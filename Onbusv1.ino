#include <Arduino.h>
#include <string>
#include <Wire.h>
#include <Adafruit_PN532.h>
#include "WiFi.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <HardwareSerial.h>
#include <EEPROM.h>

HardwareSerial SIM800(2); // RX = 16, TX = 17
String Tripcost="10";
String APN = "web.gprs.mtnnigeria.net";
String Agent_URL="http://api.dev2.korensi.com/api/v1/wallet/cards/charge/";
String getapi_url = "http://api.dev2.korensi.com/api/v1/auth/devices/";
String mac = "84CCA82CDD6C";

String Phone = "2348126631893";
String cardNumber = "";

const String card_not_found=" Card does not exist";  
const String insufficient= "Insufficient funds";
const String success="Wallet charged successfully";


String deviceID="";

const byte ROWS = 4;
const byte COLS = 4;
TaskHandle_t TaskValidator= NULL;
TaskHandle_t TaskBatteryBar = NULL;
TaskHandle_t Taskhttpconnect = NULL;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte colPins[ROWS] = {13, 12, 14, 27};
byte rowPins[COLS] = {32, 33, 25, 26};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define PN532_IRQ   (26)
#define PN532_RESET (27)
#define Red 15
#define Yellow 2
#define Green 4
#define Buzzer 18

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
const int sensorPin = 34;  //ADC input for battery level and percentage monitoring
const float k = 0.66;     // Constant conversion

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

String enteredUSSD = "";
// Battery bar variables
const int barHeight = 10;
const int barWidth = 20;
const int barX = 100;
const int barY = 0;
const int barSpacing = 2;
const int numBars = 5;
SemaphoreHandle_t xSemaphoreOled=NULL;
SemaphoreHandle_t xSemaphorehttp = NULL;
String convertedNumber="";
String number = "";
String amount = "";
String code = "";   

boolean logic_number = false; 
boolean logic_code = false;   

String retrievedString;
String HexString="";
String phone_number = "";
bool reg_card = false; // flag to check if the user selected register card option
bool agent_logic = false;
bool top_card = false;
boolean amount_code = false;  
bool clear=false; 
//String retrievedString;
void setup(void) {
  Serial.begin(9600);
  SIM800.begin(9600, SERIAL_8N1, 16, 17);
  delay(1000);
  Serial.println("Starting SIM800...");
 Serial.println("Hello!");
 EEPROM.begin(512);
 //checkKorensiId();
 //saveStringToEEPROM(0, myString);
 retrievedString = getStringFromEEPROM(30);
 Serial.println("Retrieved String: " + retrievedString);
 getESP32MACAddress();
// HTTP_get_request(getapi_url, mac);
 //HTTP_GET_REQUEST_OnBus();
nfc.begin();
xSemaphoreOled = xSemaphoreCreateBinary();
xSemaphorehttp= xSemaphoreCreateBinary();
xSemaphoreGive(xSemaphorehttp);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//display.display();
buzzer();
Initialize_GPRS(APN);
deviceIdChecker();
//checkKorensiId();
//retrievedString = getStringFromEEPROM(30);
//HTTP_get_request(getapi_url, mac);
//HTTP_GET_REQUEST_OnBus(mac);
Nfc_connect();
Indicator_initialize();

//Led_failed();
xTaskCreatePinnedToCore(validatorTask, "validatorTask", 8096, NULL, 1, &TaskValidator, 1);

xTaskCreatePinnedToCore(batteryBarTask, "batteryBarTask", 8096, NULL, 1, &TaskBatteryBar, 1);

xTaskCreatePinnedToCore(httpconnect, "httpconnect", 8096, NULL, 1, &Taskhttpconnect, 1); 
}


void loop(void) {

}

