int r2 = 5, r3 = 6, r4 = 7, lf_rr = 0;     //Variable for storing Incoming_value
#include "dht.h"
#define DHT11_PIN 3
dht DHT;
int sensorpin = A0, sensorValue;
void setup()
{
  pinMode(r2, OUTPUT);        //r2,r3,r4 are signal pins for relay
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
}

int trigf=3;       //auto fan
int trigl=3;       //auto light 

void loop()
{
  if (lf_rr == 116)               // code for automatic fan
    {
      trigf = 0;                  // to turn to auto mode
    }
  if(trigf==0)
    {   
      DHT.read11(DHT11_PIN);
      //Serial.print("Temperature = ");
      //Serial.println(DHT.temperature);
      if (DHT.temperature > 25)
      {
        analogWrite(11, 255);
        digitalWrite(9, LOW);
      }
      else if (DHT.temperature >= 19 && DHT.temperature < 25)
      {
        digitalWrite(9, LOW);
        analogWrite(11, 191);
      }
      else if (DHT.temperature >= 13 && DHT.temperature < 19)
      {
        digitalWrite(9, LOW);
        analogWrite(11, 127);
      }
      else if (DHT.temperature >= 8 && DHT.temperature < 13)
      {
        digitalWrite(9, LOW);
        analogWrite(11, 63);
      }
      else if (DHT.temperature < 8)
      {
        digitalWrite(9, LOW);
        analogWrite(11, 0);
      }
   }  
  if (lf_rr == 112)                  //code for auto light
    { 
      trigl=0;                        //to turn on to auto mode
    }
   if(trigl==0)   
    {
      sensorValue = analogRead(sensorpin);
      Serial.println(sensorValue);
      delay(1000);
      if (sensorValue >= 27)
      {
        digitalWrite(r2, LOW);
      }
      else if (sensorValue < 27 && sensorValue >= 20) // r3+r4
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);
        digitalWrite(r4, LOW);
      }
      else if (sensorValue < 20 && sensorValue >= 12) // r3
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);
        digitalWrite(r4, HIGH);
      }
      else if (sensorValue < 12 && sensorValue >= 6) // r4
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);
        digitalWrite(r4, LOW);
      }
      else if (sensorValue < 6 && sensorValue >= 0) // no resistance
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);
        digitalWrite(r4, HIGH);
      }
   }
  if (Serial.available() > 0)
  {
    lf_rr = Serial.read();         //Read the incoming data and store it into variable Incoming_value
    Serial.print(lf_rr);           //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");            //New line
    if (lf_rr == 117)              //code for manual fan
    { 
      trigf = 1;                   // to manual
    }
    if (trigf == 1)                //manual fan runs           
    {
      if (lf_rr >= 0 && lf_rr <= 100)
      {
        analogWrite(11, 255 * (lf_rr) / 100);
        digitalWrite(9, LOW);
      }
    }
  
    if (lf_rr == 114)               //code for manual light
    { 
      trigl=1;                      //to manual
    }
   if(trigl==1)                     //manual light runs
   { 
     if (lf_rr == 101 || lf_rr == 102)
      {
        digitalWrite(r2, LOW);
      }
      else if (lf_rr == 103 || lf_rr == 104 || lf_rr == 105)
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);
        digitalWrite(r4, LOW);
      }
      else if (lf_rr == 106 || lf_rr == 107)
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);
        digitalWrite(r4, HIGH);
      }
      else if (lf_rr == 109 || lf_rr == 108)
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);
        digitalWrite(r4, LOW);
      }
      else  if (lf_rr == 110 || lf_rr == 111)
      {
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);
        digitalWrite(r4, HIGH);
      }
   }
   
   if (lf_rr == 113)                     // stop light
    {
      trigl=2;
    }
    if(trigl==2)
    {
      digitalWrite(r2,LOW);
      Serial.println("stop");
    }
   if (lf_rr == 115)                    //stop fan
    {
      trigf=2;
      Serial.println("stop");
    }  
   if(trigf==2)
   {   
      digitalWrite(9, LOW);
      analogWrite(11, 0);
    }
  }
}
