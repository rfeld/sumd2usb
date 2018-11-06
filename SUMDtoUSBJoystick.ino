// Decode SUMD Signal connected to Serial1 and output USB Joystick Signals


#include <Joystick.h>

//#define DEBUGOUT


// Create the Joystick
Joystick_ Joystick(1,
                   JOYSTICK_TYPE_JOYSTICK, 2, 0,
                   true, true, false, false, false, false,
                   true, true, false, false, false);


// Packet buffer
unsigned char cbuffer[32];
unsigned int channels[5];

void setup()
{
Serial.begin(115200);
#ifdef DEBUGOUT
  Serial.begin(115200);
  Serial.println("Starte");
#endif

  // Serial interface to the GR12
  Serial1.begin(115200);

  // Initialize Joystick Library
  Joystick.begin(false);

  // Set Value Ranges
  Joystick.setXAxisRange(8800, 15200);
  Joystick.setYAxisRange(8800, 15200);
  Joystick.setRudderRange(8800, 15200);
  Joystick.setThrottleRange(8800, 15200);

  // empty Buffer
  while (Serial1.available())
    Serial1.read();

}

void loop()
{
  if (Serial1.available() > 14)
  {
    for (int i = 0; i < 15; i++)
    {
      cbuffer[i] = Serial1.read();
      //Serial.print(cbuffer[i], DEC);
      //Serial.print(",");
    }
    //Serial.println("<<<");
    // Lets have a look in the buffer

    // Check Header
    if ( cbuffer[0] == 168 && cbuffer[1] == 1 && cbuffer[2] == 5)
    {
      int k = 0;
      // Decode Channels
      for (int j = 3; j < 13; j = j + 2)
      {
        int tmp =  cbuffer[j + 1] + (cbuffer[j] << 8);
#ifdef DEBUGOUT
        Serial.print(tmp, DEC);
        Serial.print(",");
#endif
        channels[k++] = tmp;
      }
#ifdef DEBUGOUT
      Serial.println(" ");
#endif
      // Update Joystick
      Joystick.setThrottle(channels[0]);
      Joystick.setXAxis(channels[1]);
      Joystick.setYAxis(channels[2]);
      Joystick.setRudder(channels[3]);

      // Map channel 5 to Button 0
      if (channels[4] < 12000)
      {
        Joystick.releaseButton(0);
      }
      else
      {
        Joystick.pressButton(0);
      }

      Joystick.sendState();
    }
    else
    {
      Serial.println("RX Error!");

      // empty Buffer to restart with next packet
      while (Serial1.available())
        Serial1.read();
    }
  }
}


