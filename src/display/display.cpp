#include "display.h"

#include <string>
int oldAngle = 0;
int oldAngleDistance = 0;
const int mx = TFT_WIDTH / 2;
const int my = TFT_HEIGHT / 2;
const int distanceOffset = 100;
const int textHeight = 30;
const int arrowHeight = distanceOffset - textHeight;

#include <sstream>  // Include the necessary header file

std::string formatDistance(int distanceInMeters) {
  // If the distance is less than 1000 meters, display it in meters.
  if (distanceInMeters < 1000) {
    return std::to_string(distanceInMeters) + "m";
  } else {
    // If the distance is 1 km or more, display it in kilometers with one
    // decimal place.
    double distanceInKilometers =
        static_cast<double>(distanceInMeters) / 1000.0;
    std::ostringstream oss;
    oss.precision(1);  // Set precision to 1 decimal place
    oss << std::fixed << distanceInKilometers << "km";
    return oss.str();
  }
}

void Display::init() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(0);
}

void Display::drawNeedleWithColor(int angle, uint16_t color) {
  auto baseWidth = 10;
  auto tipX = mx + (int)(cos(angle * DEG_TO_RAD) * arrowHeight);
  auto tipY = my + (int)(sin(angle * DEG_TO_RAD) * arrowHeight);
  auto baseX1 = mx + (int)(cos((angle + 120) * DEG_TO_RAD) * baseWidth);
  auto baseY1 = my + (int)(sin((angle + 120) * DEG_TO_RAD) * baseWidth);
  auto baseX2 = mx + (int)(cos((angle - 120) * DEG_TO_RAD) * baseWidth);
  auto baseY2 = my + (int)(sin((angle - 120) * DEG_TO_RAD) * baseWidth);
  tft.fillTriangle(tipX, tipY, baseX1, baseY1, baseX2, baseY2, color);
}

void Display::drawNeedle(int angle) {
  if (angle / 5 != oldAngle / 5) {
    // erase old needle
    drawNeedleWithColor(oldAngle, TFT_BLACK);
    // draw new needle
    drawNeedleWithColor(angle, TFT_RED);
    oldAngle = angle;
  }
}

void Display::drawDistanceWithColor(int angle, int distance, uint16_t color) {
  tft.setPivot(mx, my);
  spr.setColorDepth(8);
  spr.createSprite(64, textHeight);
  spr.setPivot(32, distanceOffset);
  spr.fillSprite(TFT_BLACK);
  spr.setTextColor(color);
  spr.setTextDatum(MC_DATUM);
  String dist = formatDistance(distance).c_str();
  spr.drawString(dist, 32, 15, 4);
  spr.pushRotated(angle);
}

void Display::drawDistance(int angle, int distance) {
  if (angle / 5 != oldAngleDistance / 5) {
    drawDistanceWithColor(oldAngleDistance, distance, TFT_BLACK);
    auto textAngle = (angle + 90) % 360;
    drawDistanceWithColor(textAngle, distance, TFT_RED);
    oldAngleDistance = textAngle;
  }
}

void Display::drawString(int angle, String text) {
  if (angle / 5 != oldAngleDistance / 5) {
    drawDistanceWithColor(oldAngleDistance, 0, TFT_BLACK);
    // display distance
    auto textAngle = (angle + 90) % 360;
    drawStringWithColor(textAngle, text, TFT_RED);
    oldAngleDistance = textAngle;
  }
}

void Display::drawStringWithColor(int angle, String text, uint16_t color) {
  tft.setPivot(mx, my);
  spr.setColorDepth(8);
  spr.createSprite(64, textHeight);
  spr.setPivot(32, distanceOffset);
  spr.fillSprite(TFT_BLACK);
  spr.setTextColor(color);
  spr.setTextDatum(MC_DATUM);
  spr.drawString(text, 32, 15, 4);
  spr.pushRotated(angle);
}