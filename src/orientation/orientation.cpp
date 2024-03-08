#include "orientation.h"

#include <QMC5883LCompass.h>

#include "math.h"

QMC5883LCompass compass;

void Orientation::init(int degrees, int minutes) {
  _magneticDeclinationDegrees = degrees + minutes / 60;
  // compass.setCalibrationOffsets(1317.00, -192.00, 2612.00);
  // compass.setCalibrationScales(1.34, 1.29, 0.68);
  // compass.setCalibrationOffsets(179.00, 925.00, -876.00);
  // compass.setCalibrationScales(0.94, 0.89, 1.22);


// cased one 
  compass.setCalibrationOffsets(202.00, 263.00, -433.00);
compass.setCalibrationScales(1.06, 0.95, 0.99);
  // https://www.magnetic-declination.com/
  // compass.setMagneticDeclination(3, 32);
  compass.init();
}

int Orientation::getAzimuth() {
  compass.read();
  int x = compass.getX();
  int y = compass.getY();

  float heading = atan2(x, y) * 180.0 / M_PI;
  heading += _magneticDeclinationDegrees;
  return (int)heading % 360;
};

void Orientation::read() { compass.read(); }

void Orientation::calibrate() {
  Serial.begin(9600);
  compass.init();

  Serial.println(
      "This will provide calibration settings for your QMC5883L chip. When "
      "prompted, move the magnetometer in all directions until the calibration "
      "is complete.");
  Serial.println("Calibration will begin in 5 seconds.");
  delay(5000);

  Serial.println("CALIBRATING. Keep moving your sensor. It will take 10s...");
  compass.calibrate();

  Serial.println(
      "DONE. Copy the lines below and paste it into your projects sketch.);");
  Serial.println();
  Serial.print("compass.setCalibrationOffsets(");
  Serial.print(compass.getCalibrationOffset(0));
  Serial.print(", ");
  Serial.print(compass.getCalibrationOffset(1));
  Serial.print(", ");
  Serial.print(compass.getCalibrationOffset(2));
  Serial.println(");");
  Serial.print("compass.setCalibrationScales(");
  Serial.print(compass.getCalibrationScale(0));
  Serial.print(", ");
  Serial.print(compass.getCalibrationScale(1));
  Serial.print(", ");
  Serial.print(compass.getCalibrationScale(2));
  Serial.println(");");
}