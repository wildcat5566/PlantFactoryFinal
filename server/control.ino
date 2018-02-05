 void control(){
  if(digitalRead(huSwitch) == HIGH){
    humidifierOpen = 1;
  }
  else if(digitalRead(huSwitch) == LOW){
    humidifierOpen = 0;
  }
  if(digitalRead(hpSwitch) == HIGH){
    heatpumpOpen = 1; 
  }
  else if(digitalRead(hpSwitch) == LOW){
    heatpumpOpen = 0;
  }
  if(digitalRead(heSwitch) == HIGH){
    heaterOpen = 1;
  }
  else if(digitalRead(heSwitch) == LOW){
    heaterOpen = 0;
  }
  if(digitalRead(co2Switch) == HIGH){
    co2Open = 1;
  }
  else if(digitalRead(co2Switch) == LOW){
    co2Open = 0;
  }

lcd.setCursor(0,1);
lcd.print("humidifier = ");
lcd.setCursor(13, 1);
lcd.print(humidifierOpen);
   //Terminal Commands
 if (heaterOpen == 1){
    digitalWrite(heater, HIGH);
 }
  else if (heaterOpen == 0){
    digitalWrite(heater, LOW);
 }
 if (heatpumpOpen == 1){
    digitalWrite(heatpump, HIGH);
 }
  else if (heatpumpOpen == 0){
    digitalWrite(heatpump, LOW);
 }
 if (humidifierOpen == 1){
    digitalWrite(humidifier, HIGH);
 }
  else if (humidifierOpen == 0){
    digitalWrite(humidifier, LOW);
 }
 if(co2Open == 1){
   digitalWrite(CO2, HIGH);
 }
 else if (co2Open == 0){
  digitalWrite(CO2, LOW);
 }
 }
