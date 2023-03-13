#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "SHT2x.h"
#include <iostream>
#include <string>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO 26

using namespace std;

WiFiClient espClient;
PubSubClient client(espClient);

union pack
{
    uint8_t frame[16];
    float data[4];
} sdp;

float d1, d2;
int rssi, i = 0;
const char *ssid = "Auschwitfi";
const char *password = "WifiZyklonique";
const char *mqtt_server = "test.mosquitto.org";
long lastMsg = 0;
char msg[50];
int value = 0;
SHT2x SHT2x;

int freq, sf, sb;

void setup()
{
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(get_mqtt_server);
    Wire.begin(21, 22);
    SHT2x.begin();
}

void setup_wifi()
{
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void get_mqtt_server(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived on topic: ");
    String mqtt_val;
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
        mqtt_val += payload[i];
    }
    Serial.println(mqtt_val);
    char delim = ',';
    int pos = mqtt_val.indexOf(delim);
    String freq_str = mqtt_val.substring(0, pos);
    mqtt_val = mqtt_val.substring(pos + 1);
    pos = mqtt_val.indexOf(delim);
    String sf_str = mqtt_val.substring(0, pos);
    mqtt_val = mqtt_val.substring(pos + 1);
    String sb_str = mqtt_val;
    freq = freq_str.toInt();
    sf = sf_str.toInt();
    sb = sb_str.toInt();
    Serial.print(freq);
    Serial.print(sf);
    Serial.print(sb);
}

void setup_lora(char freq, char sf, char sb)
{
    pinMode(DIO, INPUT);
    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO);
    if (!LoRa.begin(freq))
    {
        Serial.println("Starting LoRa failed!");
        while (1)
            ;
    }
    LoRa.setSpreadingFactor(sf);
    LoRa.setSignalBandwidth(sb);
    Serial.println("Starting LoRa...!");
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("espClient"))
        {
            Serial.println("connected");
            client.subscribe("srt/victor");
            Serial.println("Subscribed to srt/victor");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(3000);
        }
    }
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
    setup_lora(freq, sf, sb);
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
    Serial.println("LoRa value:");
    Serial.println(d1);
    Serial.println(d2);
    // Serial.println(rssi);
}
