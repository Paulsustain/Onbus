void Led_processing1(){
  digitalWrite(Yellow,HIGH);
  digitalWrite(Green,LOW);
  digitalWrite(Red,LOW);
}
void buzzer(){
  digitalWrite(Buzzer,HIGH);
  vTaskDelay(pdMS_TO_TICKS(2000));
 digitalWrite(Buzzer,LOW);
  vTaskDelay(pdMS_TO_TICKS(1000)); 
}
void buzzer_click(){
  digitalWrite(Buzzer,HIGH);
  vTaskDelay(pdMS_TO_TICKS(500));
  digitalWrite(Buzzer,LOW);
  vTaskDelay(pdMS_TO_TICKS(500)); 
}

void Led_processing_end(){
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
  digitalWrite(Red,LOW);
}


void Indicator_initialize(){
  pinMode(Red,OUTPUT);
 pinMode(Buzzer,OUTPUT);
  pinMode(Yellow,OUTPUT);
  pinMode(Green,OUTPUT);
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
  digitalWrite(Buzzer,LOW);
}

void Led_failed(){
  digitalWrite(Red,HIGH);
  digitalWrite(Yellow,LOW);
  digitalWrite(Green,LOW);
}
void Led_failed_end(){
  digitalWrite(Red,LOW);  
}

void Led_success(){
  digitalWrite(Green,HIGH);
  digitalWrite(Red,LOW);
  digitalWrite(Yellow,LOW);
}
