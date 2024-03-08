// display
// needs to be set in lib ;/ => TFT_eSPI/User_Setup_Select.h
#define USER_SETUP_INFO "User_Setup"

#define GC9A01_DRIVER
#define TFT_SDA_READ

#define TFT_WIDTH  240
#define TFT_HEIGHT 240

// The hardware SPI can be mapped to any pins
#define TFT_MOSI 15  // might be written as "SDA"
#define TFT_SCLK 14
#define TFT_CS    5  // Chip select
#define TFT_DC   27  // Data Command
#define TFT_RST  33  // Reset pin
#define TFT_BL   23  // LED back-light (BLK)

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.

#define SPI_FREQUENCY       27000000
#define SPI_READ_FREQUENCY  20000000