#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
int speed = 90;
int speedMap = 0;

void setup()
{
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  speed = analogRead(A0);
  speedMap = map(speed, 0, 1023, 0, 180);
  String speedString = String(speedMap);
  char speedCharArray[4];
  speedString.toCharArray(speedCharArray, 4);

  digitalWrite(led_pin, HIGH);
  vw_send((uint8_t *)speedCharArray, strlen(speedCharArray));
  vw_wait_tx();
  digitalWrite(led_pin, LOW);
  delay(10);
}
