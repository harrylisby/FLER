class Joystick {
  public:
    void Joystick();
    uint16_t readY();
    uint16_t readX();
    uint16_t readYB();
    uint16_t readYX();
    uint8_t dir;
    Adafruit_ADS1115 ads; 
  private:
    uint16_t _adcY;
    uint16_t _adcX;
    uint16_t _adcYB; \\z
    uint16_t _adcXB; \\g
    int _boton;
    bool _value_boton;
    int _adc1;
    int _adc2;
};

