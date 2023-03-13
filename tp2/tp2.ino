#include <SPI.h>
#include <LoRa.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO 26
#define BAND 870E6 // Fréquence bluetooth utilisée
#define sf 9       // Facteur d'étalement
#define sb 33E3    // Bande passante

union pack
{
  uint8_t frame[16];
  float data[4];
} sdp;

float d1, d2;
int rssi, i = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(DIO, INPUT);
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.setSpreadingFactor(sf);
  LoRa.setSignalBandwidth(sb);
  Serial.println("Starting LoRa...!");
}

void loop()
{
  int packetLen;
  packetLen = LoRa.parsePacket();
  i = 0;
  while (LoRa.available())
  {
    Serial.println("Lora available");
    // Serial.println(LoRa.read());
    sdp.frame[i] = LoRa.read();
    i++;
  }
  delay(1000);
  d1 = sdp.data[0];
  d2 = sdp.data[1];
  // rssi = LoRa.packetRssi();
  Serial.println(d1);
  Serial.println(d2);
  // Serial.println(rssi);
}
