void readSensor(){
if (Serial3.available() >= 15) { 
 while(Serial3.read() != 02) {} // dummy
    Serial3.read();
    byte data[6];
    for (int i = 0; i < 6; i++){
      data[i] = Serial3.read();
      co2Now = data[0] * 256.0 + data[1];
      rhNow = (data[2] * 256.0 + data[3]) / 10.0;
      temNow = (data[4] * 256.0 + data[5]) / 10.0;

      if(timer >= 1){
        if(rhNow - rhLast <= 5 && rhNow - rhLast >= -5){   //防亂跳
          rh=rhNow;
        }
        else{
          rh=rh;
        }
        if(temNow - temLast <= 1 && temNow - temLast >= -1){   //防亂跳
          tem=temNow;
        }
        else{
          tem = tem;
        }
        if(co2Now - co2Last <= 50 && co2Now - co2Last >= -50){   //防亂跳
          co2=co2Now;
        }
        else{
          co2 = co2;
        }

      }
      else if(timer == 0){
        rh = rhNow;
        tem = temNow;
        co2 = co2Now;
      }
    }

    lcd.setCursor(0,0);
    lcd.print(co2);
    if (co2<=999){ //co2 = 3digits, clear 4th digit
     lcd.setCursor(3,0);
     lcd.print(" ");      
    }
    lcd.setCursor(6,0);
    lcd.print(rh);
    lcd.setCursor(12,0);
    lcd.print(tem);
    
    lcd.setCursor(4,0);
    lcd.print(" ");
    lcd.setCursor(11,0);
    lcd.print(" ");
  
    //control();
    timer++;

    if(timer % 60 == 30 && count >= 1){

      rhTarget = rh*10;
      temTarget = tem*10;
      co2Target = co2;
      lightTarget = 0;

      Serial.print(count);
      Serial.print(", ");
      Serial.print(rhTarget);
      Serial.print(", ");
      Serial.print(temTarget);
      Serial.print(", ");
      Serial.print(co2Target);
      Serial.print(", ");
      Serial.print(lightTarget);
      Serial.println(", ");     

   
  }
  co2Last = co2;
  rhLast = rh;
  temLast = tem;
}
}
