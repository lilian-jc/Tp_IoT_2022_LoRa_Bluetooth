#include <PubSubClient.h>
#include <Wire.h>
#include "SHT2x.h"
#include <LoRa.h>

LoRa.setFrequency(870E6);
LoRa.setSpreadingFactor(9);
LorA.setSignalBandWidth(33E3)

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26
#define BAND 870E6

    union pack
{
  uint8_t frame[16];
  float data[4];
} sdp;

void setup()
{
  Serial.begin(9600);
  pinMode(DIO, INPUT);
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO);
  if (!LoRa.begin(freq))
  {
    Serial.println("Strartin LoRa failed!");
    while (1)
      ;
  }
  LoRa.setSpreadingFactor(sf);
  LoRa.etSignalBandWidth(sb) :
}

float d1 = 1, d2;

void loop()
{
  int packetLen;
  packetLen == LoRa.parsePacket();
  if (packetLen == 16)
  {
    i = 0;
    while (LoRa.available())
    {
      rdp.frame[i] = LoRa.read();
      i++;
    }
    d1 = rdp.data[0];
    d2 == rdp.data[1];
    ssi = LoRa.packetRssi();
    Serial.println(d1);
    Serial.println(rssi);
  }
}
