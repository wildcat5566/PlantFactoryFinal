void PythonComm(){
  //if(count < 1440){ //last count = 1440
  count++;
  Serial.println(count);

  
 int readingBytes = Serial.available();

 if(readingBytes > 0){
  byte value[readingBytes];
  if(readingBytes == 10){ //rh[3]+tem[3]+co2[3]+light[1]
     for (int i = 0; i < 10; i++){
    value[i] = Serial.read()-'0';   
     }
    rhTarget = (value[0]*100+value[1]*10+value[2])*0.1;
    temTarget = (value[3]*100+value[4]*10+value[5])*0.1;
    co2Target = value[6]*100+value[7]*10+value[8];
    lightTarget = value[9];
    lcd.setCursor(0,1);
    lcd.print(co2Target);
    lcd.setCursor(3,1);
    lcd.print(" ");
    lcd.setCursor(6,1);
    lcd.print(rhTarget);
    lcd.setCursor(12,1);
    lcd.print(temTarget);
  }
  else if(readingBytes == 11){ //rh[3]+tem[3]+co2[4]+light[1]
    for (int i = 0; i < 11; i++){
    value[i] = Serial.read()-'0';   
     }
    rhTarget = (value[0]*100+value[1]*10+value[2])*0.1;
    temTarget = (value[3]*100+value[4]*10+value[5])*0.1;
    co2Target = value[6]*1000+value[7]*100+value[8]*10+value[9]; 
    lightTarget = value[10];   
    lcd.setCursor(0,1);
    lcd.print(co2Target);
    lcd.setCursor(6,1);
    lcd.print(rhTarget);
    lcd.setCursor(12,1);
    lcd.print(temTarget);
  }
 } 
 //}
}

