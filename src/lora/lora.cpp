#include "lora.h"

#include <LoRa.h>

#define ss 32
#define rst 12
#define dio0 2
#define localAddress 0x01

Location parseLocation(String loc);
String locationToString(Location location);

void Lora::init() {
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}

unsigned long loraReadStart = 0;
Location Lora::read() {
  int packetSize = LoRa.parsePacket();  // try to parse packet
  loraReadStart = millis();
  String loRaData;
  if (packetSize) {
    Serial.print("Received packet '");
    while (LoRa.available()) {
      if (millis() - loraReadStart > 200) {
        Serial.println("Timeout");
        break;
      }
      loRaData += LoRa.readString();
      Serial.println(loRaData);
    }
    Serial.print("' with RSSI ");  // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }
  return parseLocation(loRaData);
}

Location parseLocation(String loc) {
  Location location;
  int semicolonIndex = loc.indexOf(";");
  String lat = loc.substring(0, semicolonIndex);
  String lon = loc.substring(semicolonIndex + 1);
  location.lat = lat.toFloat();
  location.lon = lon.toFloat();
  return location;
}

String locationToString(Location location) {
  String lat = String(location.lat, 6);
  String lon = String(location.lon, 6);
  return lat + ";" + lon;
}

void Lora::send(Location location) {
  String locString = locationToString(location);
  LoRa.beginPacket();
  LoRa.print(locString);
  LoRa.endPacket();
  Serial.print("Sending packet ");
  Serial.println(locString);
}
