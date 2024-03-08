#include <TFT_eSPI.h>

class Display {
 public:
  void init();
  void drawDistance(int angle, int distance);
  void drawNeedle(int angle);
  void drawString(int angle, String text);

 private:
  TFT_eSPI tft = TFT_eSPI();
  TFT_eSprite spr = TFT_eSprite(&tft);
  void drawNeedleWithColor(int angle, uint16_t color);
  void drawDistanceWithColor(int angle, int distance, uint16_t color);
  void drawStringWithColor(int angle, String text, uint16_t color);
};