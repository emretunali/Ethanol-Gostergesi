#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 11); // RX, TX

unsigned int ethanol=0;
unsigned int ethanol2 = 0;   

unsigned long curTime;
unsigned long curGap;
unsigned long toothLastToothTime = 0;
unsigned long toothLastMinusOneToothTime = 0;

byte pinFlex = 2;

int mainLoopCount;

void setup()
{
 Serial.begin(9600); // Debug Monitor baudrate
 mySerial.begin(9600);
 
 pinMode(pinFlex, INPUT_PULLUP);

 for (int i=0; i <= 100; i++)
 {
    goster_hw();
    ethanol=ethanol+1;
    ethanol2=map(ethanol,0,100,5,84);
    delay(1);
  }

  for (int i=0; i <= 101; i++)
  {
    goster_hw();
    ethanol=ethanol-1;
    ethanol2=map(ethanol,0,100,5,84);
    delay(1);
  }

 attachInterrupt(digitalPinToInterrupt(pinFlex), flexPulse, RISING);

 mainLoopCount = 0;
}

void flexPulse()
{
    curTime = micros();
    curGap = curTime - toothLastToothTime;
    ethanol = map(curGap, 20004, 6668, 0, 100);

    if(ethanol >= 100){ethanol=100;}
    if(ethanol <= 0){ethanol=0;}

    ethanol2=map(ethanol,0,100,5,90);
     
    toothLastMinusOneToothTime = toothLastToothTime;
    toothLastToothTime = curTime;
}

void goster_hw(void)
{
  Serial.print("j1.val=");
  Serial.print(ethanol2);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.print("t1.txt=");
  Serial.write(0x22);
  Serial.print(ethanol);
  Serial.write(0x22);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void goster_sw(void)
{
  mySerial.print("j1.val=");
  mySerial.print(ethanol2);
  mySerial.write(0xff);
  mySerial.write(0xff);
  mySerial.write(0xff);
  mySerial.print("t1.txt=");
  mySerial.write(0x22);
  mySerial.print(ethanol);
  mySerial.write(0x22);
  mySerial.write(0xff);
  mySerial.write(0xff);
  mySerial.write(0xff);
}


void loop()
{
  while(1)
  {
    mainLoopCount++;
    if( (mainLoopCount & 31) == 1) //32 loop
    {
      /*Serial.print("j1.val=");
      Serial.print(ethanol2);
      Serial.print(" t1.txt=");
      Serial.println(ethanol);*/
    }

    if( (mainLoopCount & 63) == 1) //Every 64 loops
    {

      
    }
    if( (mainLoopCount & 255) == 1) //256 Loop
    {
      goster_hw();
    }
  }
}
