/**
 **************************************************
 *
 * @file        SGP30-SOLDERED.cpp
 * @brief       Arduino library wraper for SGP30-2.5K air quality sensor.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for Soldered.com
 ***************************************************/


#include "SGP30-SOLDERED.h"

/**
 * @brief                   Overloaded function for virtual in base class to initialize sensor specific.
 */
void SGP30::initializeNative()
{
    pinMode(pin, INPUT);
}
