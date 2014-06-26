/*
 * echo - echo characters back to bluetooth device
 *
 * Waits for a connection and then echos each charater received.
 *
 * Debugging is enabled, so if you open the 'Serial Monitor' you can see
 * the search for the HC05 baud and the wait for the BT connection.
 */
#include <Arduino.h>
#include "HC05.h"

#ifdef HC05_SOFTWARE_SERIAL
#include <SoftwareSerial.h>
HC05 btSerial = HC05(A2, A5, A3, A4);  // cmd, state, rx, tx
#else
HC05 btSerial = HC05(3, 2);  // cmd, state
#endif
boolean ok=false;
String str;
unsigned int MAX=50000;
void setup()
{
  DEBUG_BEGIN(57600);
  btSerial.findBaud();
}

void loop()
{
  while (btSerial.connected())
  {
    if(!ok)
    {
      if (btSerial.available())
      {
      //  Serial.println(btSerial.read());
         char temp=btSerial.read();
         //if the data is not the end tag,then add it to the str
         //else change the ok to false,which means received an 
         //cmd 
         if (temp!='\n')
         {
           str +=temp;
           Serial.println(str);
         }
         else
         {
           ok=true;
         }
      }
    }
    //do something to the cmd
    else{
      Serial.println(str);
//      btSerial.print("hello world\n");
      something();
      ok=false;
      str="";
    }
    
  }
}
void something()
{
  for(unsigned int i=0;i<MAX;i++)
  {
    btSerial.print("hello world_12345678901");
    btSerial.print('\n');
    //may be cause some wrong code
    delay(50);
  }
}
