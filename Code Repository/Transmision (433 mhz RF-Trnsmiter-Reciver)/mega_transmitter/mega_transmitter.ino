#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
int serRead;
void setup()
{
    Serial.begin(9600);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
serRead=  Serial.read();
  if(serRead==49)
  {
        const char *msg = "R";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print(serRead);
  }
   if(serRead==50)
  {
        const char *msg = "L";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print(serRead);
  }
   if(serRead==51)
  {
        const char *msg = "F";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print(serRead);
  }
   if(serRead==52)
  {
        const char *msg = "B";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print(serRead);
  }
  
   if(serRead==48)
  {
        const char *msg = "S";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print(serRead);
  }
  else
 {
    const char *msg = "W";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print(serRead);
 }
}
//////////////////////////////

