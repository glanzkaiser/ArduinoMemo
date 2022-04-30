#pragma once
#include <Arduino.h>

#define ML8511_LIB_VERSION (F("0.1.7"))

class ML8511
{
public:
  // if enablePin is omitted, one must connect EN to 3V3.
  ML8511(uint8_t analogPin, uint8_t enablePin = 0xFF);

  void reset();  // reset internal variables to initial value.

  // energyMode = HIGH or LOW;
  // returns mW per cm2
  float    getUV(uint8_t energyMode = HIGH);
  // for external ADC
  float    voltage2mW(float voltage);

  // voltage must be > 0 otherwise it is not set
  void     setVoltsPerStep(float voltage, uint32_t steps);
  float    getVoltsPerStep() { return _voltsPerStep; };

  // manually enable / disable
  void     enable();
  void     disable();
  bool     isEnabled() { return _enabled; };
  float    estimateDUVindex(float mWcm2);
  bool     setDUVfactor(float factor);
  float    getDUVfactor() { return _DUVfactor; };

private:
  uint8_t  _analogPin;
  uint8_t  _enablePin;
  float    _voltsPerStep;
  bool     _enabled;
  float    _DUVfactor;
};
