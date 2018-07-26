#include <SoftwareSerial.h>
#include <String.h>


SoftwareSerial mySerial(9, 10);
const int gasPin =A0;
int thresh = 250;
int critical=350;
int rasp = 2,d=0,c=0,gg;
int v=0,i=0,j=0,k=0;
int buzz= 8;
char buff;
int serve = 7;
void setup()

{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module 

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(15000);
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CNMI=2,2,0,0,0");
  tone(buzz,10000,100);
  delay(200);
  tone(buzz,10000,100);
  pinMode(serve, OUTPUT);
  delay(1000);
  pinMode(rasp, INPUT);
  digitalWrite(serve, HIGH);
  
}

void loop()

{ 
  gg = digitalRead(rasp);
  if(gg != d)
  {
    digitalWrite(serve, d);
    d=gg;
  }
  

 if (mySerial.available()>0)
 {
   v= analogRead(gasPin);
   delay(500);
   buff=mySerial.read();
   while(buff != -1)
   {
    //buff = mySerial.read();
    if(buff == 'z')
    {
      tone(buzz,10000,500);
      SendMessage3(v);
    }
    else if(buff == 'b')
    {
      tone(buzz,10000,500);
      delay(500);
    }
    else if(buff == 'o')
    {
      tone(buzz,10000,500);
      digitalWrite(serve, HIGH);
      delay(500);
    }
    else if(buff == 'p')
    {
      tone(buzz,10000,500);
      digitalWrite(serve, LOW);
      delay(500);
    }

    buff = mySerial.read();
   }
 }
 if(v<=thresh)
   {
      if(i==1)
      {
        SendMessage0();
      }
      i=0;
      j=0;
      k=0;
   }
   if(v>thresh && v<=critical)
   {
      if(k!=1)
      {
        SendMessage1();
        k=1;
        i=1;
        j=0;
      }
      tone(buzz,9000,500);
      delay(1000);
   }
   if(v> critical)
   {
      if(j!=1)
      {
        SendMessage2();
        delay(5000);
        DialCall();
        j=1;
        i=1;
        k=0;
      }
      tone(buzz,10000,100);
      delay(200);
   }
}

 void SendMessage0()

{
  mySerial.println("AT+CMGS=\"+918420137845\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Flammable Gases are under control. No need to worry now.");// The SMS text you want to send
  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void SendMessage1()

{
  mySerial.println("AT+CMGS=\"+918420137845\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Flammable Gases are increasing");// The SMS text you want to send
  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void SendMessage2()
 
{
  mySerial.println("AT+CMGS=\"+918420137845\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Flammable Gases are in very critical state, visit home fast!!!");// The SMS text you want to send
  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void SendMessage3(int v)

{
  mySerial.println("AT+CMGS=\"+918420137845\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println(v);// The SMS text you want to send
  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}



  void DialCall()

 {
  Serial.println("Dialing");
  mySerial.println("ATD+918420137845;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!

  delay(100);
 }
 
