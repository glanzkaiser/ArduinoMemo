#include "ML8511.h"

ML8511::ML8511(uint8_t analogPin, uint8_t enablePin)
{
  _analogPin    = analogPin;
  _enablePin    = enablePin;
  if (enablePin != 0xFF)
  {
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin, LOW);
    _enabled = false;
    enable();
  }
  else 
  {
    _enabled = true;
  }
  reset();
};


void ML8511::reset()
{
  _voltsPerStep = 3.3/4095;
  _DUVfactor    = 1.61;    
}


float ML8511::getUV(uint8_t energyMode)
{
  if (!_enabled)
  {
    enable();
    uint32_t start = micros();
    while (micros() - start < 1000) yield();
  }
  float voltage = analogRead(_analogPin) * _voltsPerStep;
  if (energyMode == LOW)
  {
    disable();
  }

  return voltage2mW(voltage);
}


float ML8511::voltage2mW(float voltage)
{
  if (voltage <= 1.0) 
  {
    return 0.0;
  }
  voltage -= 1.0;    // subtract for zero point.
  float mWcm2 = voltage * (15.0 / 1.8);
  return mWcm2;
}

float ML8511::estimateDUVindex(float mWcm2)
{
  return mWcm2 * _DUVfactor;
};


bool ML8511::setDUVfactor(float factor)
{
  if (factor < 0.01) return false;  
  _DUVfactor = factor; 
  return true;
};


void  ML8511::setVoltsPerStep(float voltage, uint32_t steps)
{
  if (steps == 0) return;
  if (voltage > 0.0) _voltsPerStep = voltage / steps;
}


void ML8511::enable()
{
  if (_enablePin != 0xFF) digitalWrite(_enablePin, HIGH);
  _enabled = true;
};


void ML8511::disable()
{
  if (_enablePin != 0xFF) digitalWrite(_enablePin, LOW);
  _enabled = false;
};
