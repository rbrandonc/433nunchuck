#include <VirtualWire.h>
#include <SoftwareServo.h>

const int led_pin = 13;
const int transmit_pin = 11;
const int receive_pin = 12;
const int transmit_en_pin = 3;
SoftwareServo ESC;
 
void setup()
{
  delay(500);

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
 
  vw_rx_start();
  ESC.attach(3);
  pinMode(led_pin, OUTPUT);
}
char CharMsg[4]; int PPM;
void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))
  {
    int i;

    for (i = 0; i < buflen; i++)
    {
      CharMsg[i] = char(buf[i]);
    }

    CharMsg[buflen] = '\0';

    PPM = atoi(CharMsg);

    ESC.write(PPM);
    SoftwareServo::refresh();


  }
  else{
    SoftwareServo::refresh();
  }
}
