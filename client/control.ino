void control(){
if (Serial.available() >= 9){
if(co2Target != 0 && temTarget != 0 && rhTarget != 0){
  temDelta = tem - temTarget;
  rhDelta = rh - rhTarget;
  co2Delta = co2 - co2Target;
}

if(lightTarget == 1){
  digitalWrite(light1, HIGH);
  digitalWrite(light2, HIGH);
  digitalWrite(light3, HIGH);
}
else if(lightTarget == 0){
  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  digitalWrite(light3, LOW);
}
  
  
//co2 control
if(timer%30 == 1 && co2Delta < -40){//****
  co2Open = 1;
}

else if(timer%45 == 1 && co2Delta < -20){//-20
//if(timer%45 == 1 && co2 < 1020){ //for co2-fixed design
    co2Open = 1; 
  }

  else if(timer%60 == 1 && co2Delta < 0){
//else if(timer%60 == 1 && co2 < 1000){ //for co2-fixed design
    co2Open = 1;
  }
  else{
    co2Open = 0;
  }


 //heater control, only heater-related
  if(temDelta <= -0.4){ //heat
    heaterAccess = 1;
    heTime++;
    //heatpumpOpen = 0;
  }
  else if(temDelta > -0.4 && temDelta < -0.2){ //critical heating
    if(rhDelta > -2){
      heaterAccess = 1;
      heTime++;
    }
    else{
      heaterAccess = 0;
      heTime = 0;
    }
  }
  else{ //需降溫
    heaterAccess = 0;
    heTime = 0;
  }
  
//heatpump & humidifier control
  if(rhDelta >= 1){ //dry £££0606 was 2
    humidifierAccess = 0;
    huTime = 0;
    if(temDelta >= -0.5){ //heat but dry
      heatpumpAccess = 1;
      hpTime++;
    }
    else{  //no need dry
      heatpumpAccess = 2;
      hpTime++;  
    }
  }
  
  //new condition 0606
  else if(rhDelta >= 0.5){//slowly dry
    humidifierAccess = 0;
    huTime = 0;
    if(temDelta >= 0.2){
    heatpumpAccess = 1;
    hpTime++;
    }
    else if(temDelta < 0.2){
      heatpumpAccess = 2;
      hpTime++;
    }
  }
  /*
  //new condition 0606
  else if(rhDelta <= -2){//slightly dry
    humidifierAccess = 2;//critical
    huTime++;
    if(temDelta >= 0.2){//cool but humidify
      heatpumpAccess = 2;
      hpTime++;
    }
    else{
      heatpumpAccess = 0;
      hpTime = 0;
    }
  }
   */
  else if(rhDelta <= -2){ //humidify £££0606 original = -5 tried -3
    humidifierAccess = 1;
    huTime++;
    if(temDelta >= 0.3){//cool but humidify. was 0.3
      heatpumpAccess = 2;
      hpTime++;
    }
    else{
      heatpumpAccess = 0;
      hpTime = 0;
    }
  }
  
  else{ //critical
    humidifierAccess = 0;//must off
    huTime = 0;
    if(temDelta >= 0.3){ //cool
      heatpumpAccess = 2;
      hpTime++;
    }
    else{
    heatpumpAccess = 0;//must off
    hpTime = 0;
    }
  }


//CD routine settings
if(hpTime == 10){//(5,3 /12)
  hpTime = 0;
  heatpumpAccess = 0;
}
if(huTime == 15){ //£££0606 original = 15 tried 12, 2/15
  huTime = 0;
  humidifierAccess = 0;
}
if(heTime == 10){
  heTime = 0;
  heaterAccess = 0;
}
//heatpump CD time settings
//access 0, 1 or 2
if(rhDelta <= 5){
  if (heatpumpAccess == 1 && hpTime <= 4) //access 1 : all-on tried 6/12, tried 3/8
    heatpumpOpen = 1;
  else if(heatpumpAccess == 2 && hpTime <= 3) //access 2 : critical, tried 2/8
    heatpumpOpen = 1;
  else// if (heatpumpAccess == 0 || hpTime > 5)
    heatpumpOpen = 0;
}
else if(rhDelta > 5){
  if (heatpumpAccess == 1 && hpTime <= 8)
    heatpumpOpen = 1;
  else if (heatpumpAccess == 0 || hpTime > 8)
    heatpumpOpen = 0;
}
//humidifier CD time settings
//access 0, 1, 2
if (humidifierAccess == 1 && huTime <= 1) //£££0606 hutime original = 1
  humidifierOpen = 1;
//else if (humidifierAccess == 2 || huTime <= 1)
//  humidifierOpen = 1;
else if (humidifierAccess == 0 || huTime > 1) //£££0606 hutime original = 1
  humidifierOpen = 0;
  
//heater CD time settings
//access 0, 1
if (heaterAccess == 1 && heTime <= 5)//£££0606 was 3 tried 6: too hot, tried 4: too dry
  heaterOpen = 1;
else if (heaterAccess == 0 || heTime > 5)
  heaterOpen = 0;

//delta lights





if(co2Target != 0 && temTarget != 0 && rhTarget != 0){
//Terminal Commands
 if (co2Open == 1){
    digitalWrite(CO2, HIGH);
    digitalWrite(co2valveLed , HIGH);
 }
  else if (co2Open == 0){
    digitalWrite(CO2, LOW);
    digitalWrite(co2valveLed , LOW);
 }
 if (heaterOpen == 1){
    digitalWrite(heater, HIGH);
    digitalWrite(heaterLed , HIGH);
 }
  else if (heaterOpen == 0){
    digitalWrite(heater, LOW);
    digitalWrite(heaterLed , LOW);
 }
 if (heatpumpOpen == 1){
    digitalWrite(heatpump, HIGH);
    digitalWrite(heatpumpLed , HIGH);
 }
  else if (heatpumpOpen == 0){
    digitalWrite(heatpump, LOW);
    digitalWrite(heatpumpLed , LOW);
 }
 if (humidifierOpen == 1){
    digitalWrite(humidifier, HIGH);
    digitalWrite(humidifierLed , HIGH);
 }
  else if (humidifierOpen == 0){
    digitalWrite(humidifier, LOW);
    digitalWrite(humidifierLed , LOW);
  }
}

else if(co2Target == 0 || temTarget == 0 || rhTarget == 0){
// if(Serial.available() <= 3){ //ending message '123': all ctrls down
  digitalWrite(light1 , LOW);
  digitalWrite(light2 , LOW);
  digitalWrite(light3 , LOW);
  digitalWrite(CO2 , LOW);
  digitalWrite(heatpump , LOW);
  //digitalWrite(compressor , LOW);
  digitalWrite(humidifier , LOW);
  //digitalWrite(fan , LOW);
  digitalWrite(heater, LOW);
}
    
}
}
