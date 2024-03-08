class Orientation {
 public:
  int getAzimuth();
  void init(int degrees, int minutes);
  void read();
  void calibrate();

 private:
  float _magneticDeclinationDegrees = 0;
};