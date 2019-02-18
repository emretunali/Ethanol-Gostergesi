/**
  ******************************************************************************
  * @file      EthanolGostergesi-v1.ino
  * @author    Emre TUNALI
  * @version   V1.0.1
  * @date      19 - Şubat - 2019
  * @Copyright Emre TUNALI - Simple flex fuel sensor gauge for the Arduino Nano, 
  *            Pro Mini, Uno platform
  *            Copyright 2012-2019 (C) Emre TUNALI
  ******************************************************************************
  * @attention
  * V1.0.0 - Continental Flex Fuel Sensorden alınan veriler işlendi
  *        - Nextion 2.8" Lcd'ye görüntü aktarıldı ve test edildi çalışıyor.
  * V1.0.1 - 2x16 LCD eklemesi yapıldı. ( Test Edilmedi ! )
  ******************************************************************************
  */
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;   // 2x16 lcd pin tanımlamaları
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte pinFlex = 2; // Ethanol sensörü sinyal portu

SoftwareSerial mySerial(12, 11); // RX, TX - Nextion Display haberleşme pinleri

int nextionComm = 1; // Nextion Lcd ile haberleşme donanımsal uart'dan yapılmasını istiyorsanız "0" tanımlamanız gerekiyor.
                     // Nextion Lcd ile haberleşme yazılımsal uart'dan yapılmasını istiyorsanız "1" tanımlamanız gerekiyor.
                     // Ön tanımlı olarak "1" yani yazılımsal uart'dan haberleşme gerçekleşecektir. 

unsigned int ethanol=0;
unsigned int ethanol2 = 0;   

unsigned long curTime;
unsigned long curGap;
unsigned long toothLastToothTime = 0;
unsigned long toothLastMinusOneToothTime = 0;

int mainLoopCount;

void setup()
{
 Serial.begin(9600); // Seri terminal debug modnitor baudrate ayarı
 mySerial.begin(9600); // nextion display baudrate ayarı
 
 lcd.begin(16, 2);
 
 pinMode(pinFlex, INPUT_PULLUP);  // ethanol sensörü portu giriş olarak tanımlanıp internal pull-up direnci tanımlanıyor.

 for (int i=0; i <= 100; i++)
 {
    if(nextionComm == 0){goster_hw();}
    if(nextionComm == 1){goster_sw();}
    lcd216();
    ethanol=ethanol+1;
    ethanol2=map(ethanol,0,100,5,84);
    delay(1);
  }

  for (int i=0; i <= 101; i++)
  {
    if(nextionComm == 0){goster_hw();}
    if(nextionComm == 1){goster_sw();}
    lcd216();
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

void lcd216(void)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ETHANOL = ");lcd.print("%");lcd.print(ethanol);
  lcd.setCursor(0,1);
  lcd.print("BENZIN  = ");lcd.print("%");lcd.print(100-ethanol); 
}


void loop()
{
  while(1)
  {
    mainLoopCount++;
    if( (mainLoopCount & 31) == 1) //32 loop
    {

    }

    if( (mainLoopCount & 63) == 1) //Every 64 loops
    {
      
    }
    if( (mainLoopCount & 255) == 1) //256 Loop
    {
      if(nextionComm == 0){goster_hw();}
      if(nextionComm == 1){goster_sw();}
      lcd216();
    }
  }
}
