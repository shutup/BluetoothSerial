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
//to see if an command is over
boolean ok=false;
//to store the cmd
String str;
//the initial function
void setup()
{
  //set the hardware Serial baud to 57600
  DEBUG_BEGIN(57600);
  //to find the software Serial baud 
  btSerial.findBaud();
}
//the forever loop
void loop()
{
  //to see if the bluetooth is connected
  while (btSerial.connected())
  {
    //if the cmd is not received over
    if(!ok)
    {
      // is data available
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
      btSerial.print("hello world\n");
      ok=false;
      str="";
    }
  }
}
