void Tag_accept(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
   display.setCursor(0, 10);
  display.println("Processing");
  //Led_processing1();
  display.display();
}

void DeviceStartup(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Loading...");
  display.display();
  
}

void KorensiLogo(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("KORENSI");
  display.display();
  
}

void Swipe(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Swipe Card");
  display.display();
}
void oled_processing(){
  //vTaskSuspend(TaskBatteryBar);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Processing...");
  display.display();
}


void Startup(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Starting...");
  display.display();
}





