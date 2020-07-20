int r2=5,r3=6,r4=7,lf_r=0,lf_rr=0,a=0;                //Variable for storing Incoming_value
#include "dht.h"
#define DHT11_PIN 3
dht DHT;
int sensorpin=A0,sensorValue;
void setup() 
{
pinMode(r2,OUTPUT);         //r2,r3,r4 are signal pins for relay
pinMode(r3,OUTPUT);
pinMode(r4,OUTPUT);  
Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
pinMode(9,OUTPUT);
pinMode(11,OUTPUT);        
}

void loop()
{
 if(Serial.available() > 0)  
  {
    if(a==0)
    {
      lf_r= Serial.read();       //Read the incoming data and store it into variable Incoming_value
    }
    Serial.print(lf_rr);       //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");        //New line
    
if(lf_r==117)      //code for manual fan 
  { 
    lf_rr= Serial.read();
     Serial.println(lf_rr);
    if(lf_rr>=0&&lf_rr<=100)
    { 
      analogWrite(11,255*(lf_rr)/90);
      digitalWrite(9,LOW);
      a=1;     
    }
  }
else a=0;    
if(lf_r==114)           //code for manual light    
  {
    lf_rr= Serial.read();
    Serial.println(lf_rr);
    if(lf_rr==101||lf_rr==102)
     {
      digitalWrite(r2,LOW);
      a=1;
     }
    else if(lf_rr==103||lf_rr==104||lf_rr==105)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,LOW);
      digitalWrite(r4,LOW);
      a=1;
    }
    else if(lf_rr==106||lf_rr==107)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,LOW);
      digitalWrite(r4,HIGH);
      a=1;
    }
    else if(lf_rr==109||lf_rr==108)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,HIGH);
      digitalWrite(r4,LOW);
      a=1;
    }
    else  if(lf_rr==110||lf_rr==111)
    {
        digitalWrite(r2,HIGH);
        digitalWrite(r3,HIGH);
        digitalWrite(r4,HIGH);
        a=1;
    } 
  }
else a=0;  
if(lf_r==116)               // code for automatic fan 
{           
  DHT.read11(DHT11_PIN);
  //Serial.print("Temperature = ");
  //Serial.println(DHT.temperature);
  if(DHT.temperature>25)
  {
   analogWrite(11,255);
   digitalWrite(9,LOW);
   a=1;
  }
 else if(DHT.temperature>=19&&DHT.temperature<25)
  {
   digitalWrite(9,LOW);
   analogWrite(11,191);
   a=1;
  }
 else if(DHT.temperature>=13&&DHT.temperature<19)
  {
   digitalWrite(9,LOW);
   analogWrite(11,127);
   a=1;
  }
 else if(DHT.temperature>=8&&DHT.temperature<13)
  {
   digitalWrite(9,LOW);
   analogWrite(11,63);
   a=1;
  }
 else if(DHT.temperature<8)
  {
   digitalWrite(9,LOW);
   analogWrite(11,0);
   a=1;
  }
}
else a=0;
if(lf_rr==112)                     //code for auto light
{
 sensorValue=analogRead(sensorpin);
 Serial.println(sensorValue);
 delay(1000);
  if(sensorValue>=27) 
  {
    digitalWrite(r2,LOW);
    a=1;   
  }
else if(sensorValue<27&&sensorValue>=20)       // r3+r4  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);
    digitalWrite(r4,LOW);
    a=1;
  }
else if(sensorValue<20&&sensorValue>=12)       // r3  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);
    digitalWrite(r4,HIGH);
    a=1;
  }
else if(sensorValue<12&&sensorValue>=6)       // r4  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);
    digitalWrite(r4,LOW);
    a=1;
  }
else if(sensorValue<6&&sensorValue>=0)       // no resistance  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);
    digitalWrite(r4,HIGH);
    a=1;
  }         
}
if(lf_rr==113)     // stop light
 {
   digitalWrite(r2,LOW);  
 }
if(lf_rr==115)    //stop fan
 {
   digitalWrite(9,LOW);
   analogWrite(11,0);
 }
}
}                 
