/**
 **************************************************
 *
 * @file        GetBaselineValues.ino
 * @brief       This example shows how to get baseline eCO2 i TVOC values from the SGP30-2.5K sensor air quality sensor
 *
 *
 *
 * @authors     Karlo Leksic for Soldered.com
 * @link        solde.red/333176
 ***************************************************/


#include "SGP30-SOLDERED.h"
#include "Wire.h"

SGP30 sgp; // SGP30 sensor library constructor

void setup()
{
    Serial.begin(9600);                // Start serial communication of 9600 baud speed
    Serial.println("SGP30-2.5K test"); // Display a message to see if we are connected to Arduino

    if (!sgp.begin()) // Check if it is possible to find the sensor on the I2C connection
    {
        Serial.println(F("Can not find sensor :(\nCheck the connections!"));
        while (1)
            ; // If it isn't possible to find the sensor, stop further program execution
    }
    Serial.println(F("SGP30 found! :)"));

    uint16_t TVOC_base, eCO2_base; // Variables to which we save the baseline values.
    if (!sgp.getIAQBaseline(&eCO2_base, &TVOC_base))
    {
        Serial.println(F("Unsuccessful reading of the baseline sensor values"));
        return;
    }
    else
    {
        // Print baseline values on the serial monitor
        Serial.print(F(">>>>Baseline values [in HEX format]: eCO2: 0x"));
        Serial.print(eCO2_base, HEX);
        Serial.print(F(" & TVOC: 0x"));
        Serial.println(TVOC_base, HEX);
    }
}

void loop()
{
}
