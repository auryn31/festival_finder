#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "display/display.h"
#include "gps/gps.h"
#include "lora/lora.h"
#include "math.h"
#include "orientation/orientation.h"

Orientation orientation;
GPS gps;
Display display;
Lora lora;
int distance = -1;
Location lastKnownPosition;
Location friendLocation;

void setup() {
  Serial.begin(9600);
  gps.init();
  orientation.init(3, 32);

  // set values before in header of tft e spi
  display.init();

  // delay(3000);
  // orientation.calibrate();

  lora.init();
}

unsigned long prevMillis = 0;
const long interval = 1000;
unsigned long prevDisplayMillig = 0;
const long displayInterval = 100;
unsigned long prevLoraMillis = 0;
const long loraInterval = 1500;
int counter = 0;

void loop() {
  if (millis() - prevDisplayMillig > displayInterval) {
    counter++;
    prevDisplayMillig = millis();
    int angle = orientation.getAzimuth() + 180;
    if (angle < 0) {
      angle = 360 + angle;
    }
    angle += 70;
    int north = angle % 360;
    if (lastKnownPosition.distance != 0 && friendLocation.lat != 0 &&
        friendLocation.lon != 0) {
      int angleToPoint =
          north + gps.calculateAngle(friendLocation.lat, friendLocation.lon,
                                     lastKnownPosition.lat,
                                     lastKnownPosition.lon);
      angleToPoint = angleToPoint % 360;
      display.drawNeedle(angleToPoint);
      display.drawDistance(angleToPoint, distance);
    } else {
      display.drawNeedle(north);
      display.drawString(north, "North");
    }
  }
  if (millis() - prevMillis > interval) {
    // for debugging
    // gps.updateSerial();
    prevMillis = millis();
    // skip for now
    Location location = gps.getLocation();
    if (location.lat != 0 && location.lon != 0) {
      lastKnownPosition = location;
    }
    Serial.print("Last known position: ");
    Serial.print(lastKnownPosition.lat);
    Serial.print(", ");
    Serial.println(lastKnownPosition.lon);
    Serial.print("Friend position: ");
    Serial.print(friendLocation.lat);
    Serial.print(", ");
    Serial.println(friendLocation.lon);

    if (location.lat != 0 && location.lon != 0 && friendLocation.lat != 0 &&
        friendLocation.lon != 0) {
      Serial.print("Calculating distance: ");
      distance = gps.calculateDistance(friendLocation.lat, friendLocation.lon,
                                       location.lat, location.lon);
      location.distance = distance;
      Serial.println(distance);
      lastKnownPosition = location;
    }
  }

  // send location to friend
  if (millis() - prevLoraMillis > loraInterval && lastKnownPosition.lat != 0 &&
      lastKnownPosition.lon != 0) {
    lora.send(lastKnownPosition);
    prevLoraMillis = millis();
  }

  // only accept new locaion if it there is one
  Location updatedLocation = lora.read();
  if (updatedLocation.lat != 0 && updatedLocation.lon != 0) {
    friendLocation = updatedLocation;
  }
}
