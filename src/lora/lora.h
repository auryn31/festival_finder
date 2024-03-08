#include <gps/gps.h>
class Lora {
 public:
  void init();
  void send(Location location);
  Location read();

 private:
  int timeout = 200;
};