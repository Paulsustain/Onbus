
void error001(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("Card NF");
  Led_failed();
  display.display();
}

void error002(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("Success");
  display.display();
  Led_success();
}
void error003(){
  display.clearDisplay();
  display.setCursor(20, 20);
  display.print("No response");
  display.display();
  Led_failed();
}
void error004(){
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print("insuff fund");
  display.display();
  Led_failed();
}

