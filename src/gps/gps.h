#include <TinyGPSPlus.h>
#include <Wire.h>

#ifndef GPS_H
#define GPS_H
class Location {
 public:
  float lat;
  float lon;
  int distance;
};

class GPS {
 public:
  void init();
  void displayInfo();
  Location getLocation();
  void updateSerial();
  int distance(float lat, float lon);
  int calculateDistance(float lat1, float lon1, float lat2, float lon2);
  int calculateAngle(float lat1, float lon1, float lat2, float lon2);

 private:
  TinyGPSPlus gps;
};
#endif