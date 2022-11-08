/**
 **************************************************
 *
 * @file        SGP30-SOLDERED.h
 * @brief       Header file for SGP30-2.5K air quality sensor.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for Soldered.com
 ***************************************************/

#ifndef __SGP30_H__
#define __SGP30_H__

#include "Arduino.h"
#include "libs/Adafruit_SGP30/Adafruit_SGP30.h"

class SGP30  : public Adafruit_SGP30
{
  public:
  protected:
    void initializeNative();

  private:
    int pin;
};

#endif // __SGP30_H__
