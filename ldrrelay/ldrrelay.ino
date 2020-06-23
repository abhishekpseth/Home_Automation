int r2=7,r3=6,r4=5;
int sensorpin=A0,sensorValue;
void setup() 
{
 pinMode(r2,OUTPUT);
 pinMode(r3,OUTPUT);
 pinMode(r4,OUTPUT);  
 Serial.begin(9600);
}

void loop() 
{
 sensorValue=analogRead(sensorpin);
 Serial.println(sensorValue);
 delay(1000);
  if(sensorValue>=27) 
  digitalWrite(r2,LOW);   
else if(sensorValue<27&&sensorValue>=20)       // r3+r4  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);
    digitalWrite(r4,LOW);
  }
else if(sensorValue<20&&sensorValue>=12)       // r3  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,LOW);
    digitalWrite(r4,HIGH);
  }
else if(sensorValue<12&&sensorValue>=6)       // r4  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);
    digitalWrite(r4,LOW);
  }
else if(sensorValue<6&&sensorValue>=0)       // no resistance  
  {
    digitalWrite(r2,HIGH);
    digitalWrite(r3,HIGH);
    digitalWrite(r4,HIGH);
  }    
                    
}  
