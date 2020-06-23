 #include "dht.h"
#define DHT11_PIN 3
dht DHT;
void setup() 
{
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop()
{
  DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  delay(1000);
   analogWrite(11,255);
   digitalWrite(9,LOW);
 /*else if(DHT.temperature>=19&&DHT.temperature<25)
 {
   digitalWrite(9,LOW);
   analogWrite(11,191);
 }
 else if(DHT.temperature>=13&&DHT.temperature<19)
 {
   digitalWrite(9,LOW);
   analogWrite(11,127);
 }
 else if(DHT.temperature>=8&&DHT.temperature<13)
 {
   digitalWrite(9,LOW);
   analogWrite(11,63);
 }
 else if(DHT.temperature<8)
 {
   digitalWrite(9,LOW);
   analogWrite(11,0);
 }*/
}
