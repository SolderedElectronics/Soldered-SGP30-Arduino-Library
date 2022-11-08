/**
 **************************************************
 *
 * @file        AirQuality.ino
 * @brief       This example shows how to read eCO2 i TVOC values from the SGP30-2.5K sensor air quality sensor
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

    // If we have previous baseline values, we can immediately enter them to the sensor
    // If not, leave this commented
    // sgp.setIAQBaseline(0x8E68, 0x8F41);
    // NOTE: The values listed here are just an example and are not supposed to be entered, because it will lead to
    // wrong readings.
}

void loop()
{
    if (!sgp.IAQmeasure()) // Try reading the eCO2 i TVOC values from the sensor and display them on the Serial Monitor
    {
        Serial.println(F("Unsuccessful reading of the sensor values! :("));
        return;
    }
    else
    {
        // Print baseline values on the serial monitor
        Serial.print(F("TVOC: "));
        Serial.print(sgp.TVOC);
        Serial.print(F(" ppb\t"));
        Serial.print(F("eCO2: "));
        Serial.print(sgp.eCO2);
        Serial.println(F(" ppm"));
    }

    delay(1000);
}
