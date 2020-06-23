 int r2=5,r3=6,r4=7,lf_rr;
char Incoming_value=0;                //Variable for storing Incoming_value
void setup() 
{
 pinMode(r2,OUTPUT);
 pinMode(r3,OUTPUT);
 pinMode(r4,OUTPUT);  
 Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
                             //Sets digital pin 13 as output pin
}
void loop()
{
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");                  //New line
    lf_rr=Incoming_value;
    if(lf_rr>=0&&lf_rr<=100)
    {
      analogWrite(11,255*(lf_rr)/90);
      digitalWrite(9,LOW);
    }
    if(lf_rr==101||lf_rr==102)
    {
     digitalWrite(r2,LOW);
    }
    else if(lf_rr==103||lf_rr==104||lf_rr==105)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,LOW);
      digitalWrite(r4,LOW);
    }
    else if(lf_rr==106||lf_rr==107)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,LOW);
      digitalWrite(r4,HIGH);
    }
    else if(lf_rr==109||lf_rr==108)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,HIGH);
      digitalWrite(r4,LOW);          
    }
    else  if(lf_rr==110||lf_rr==111)
    {
        digitalWrite(r2,HIGH);
        digitalWrite(r3,HIGH);
        digitalWrite(r4,HIGH);
    }
    
  }                            
 
}                 
