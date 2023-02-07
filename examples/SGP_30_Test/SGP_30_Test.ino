/**
 **************************************************
 *
 * @file        SGP_30_Test.ino
 * @brief       Example by the Adafruit modified by Soldered.com
 * 
 *              Connect SGP30 sensor to the Dasduino and open the Serial Monitor at 115200 baud rate.
 *              This example will show you how to read TVOC, eCO2 and raw data from the SGP30 sensor
 *              and also print baseline values every 30 readings.
 *
 * @authors     Adafruit, modified by Soldered
 * @link        solde.red/333176
 ***************************************************/

#include "SGP30-SOLDERED.h"
#include <Wire.h>

SGP30 sgp;

/* return absolute humidity [mg/m^3] with approximation formula
 * @param temperature [°C]
 * @param humidity [%RH]
 */
uint32_t getAbsoluteHumidity(float temperature, float humidity)
{
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity =
        216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) /
                  (273.15f + temperature));                                                    // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

void setup()
{
    // Init serial comunication
    Serial.begin(115200);
    Serial.println("SGP30 test");

    // Try to init sensor
    if (!sgp.begin())
    {
        // If sensor init fails, print the message and stop the program using the infinity loop
        Serial.println("Sensor not found :(");
        while (1)
            ;
    }

    // Print the serial number of the sensor if it's found
    Serial.print("Found SGP30 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);

    // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
    sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
}

// Counter variable for counting measurements
int counter = 0; 

void loop()
{
    // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy
    // compensation for the air quality signals
    // float temperature = 22.1; // [°C]
    // float humidity = 45.2; // [%RH]
    // sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

    // Try to take measurements
    if (!sgp.IAQmeasure())
    {
        // If measurements fail, print an error message and restart the loop
        Serial.println("Measurement failed");
        return;
    }

    // If the measurement was done, print the results
    Serial.print("TVOC ");
    Serial.print(sgp.TVOC);
    Serial.print(" ppb\t");
    Serial.print("eCO2 ");
    Serial.print(sgp.eCO2);
    Serial.println(" ppm");

    // Try to take raw measurements data
    if (!sgp.IAQmeasureRaw())
    {
        // If measurements fail, print an error message and restart the loop
        Serial.println("Raw Measurement failed");
        return;
    }

    // If the measurement was done, print the results
    Serial.print("Raw H2 ");
    Serial.print(sgp.rawH2);
    Serial.print(" \t");
    Serial.print("Raw Ethanol ");
    Serial.print(sgp.rawEthanol);
    Serial.println("");

    // Delay between measurements
    delay(1000);

    // Counting measurements and printing IAQ baseline every 30 measurement
    counter++;
    if (counter == 30)
    {
        counter = 0;

        // According to Adafruit, The 'problem' with these sensors is that the baseline changes, often with humidity, temperature, and other nongas-related-events.
        // To keep the values coming out reasonable, you'll need to calibrate the sensor.
        // Sensor must to work for 12 hours until the baseline can be stored.
        // This will ensure an optimal behavior for the next time it starts up.
        // Once the baseline is properly initialized or restored, the current baseline value should be stored once per hour.
        // You should store theese in EEPROM, FLASH or hard-coded. Then, next time you start up the sensor, you can pre-fill the calibration words with
        // sgp.setIAQBaseline(eCO2_baseline, TVOC_baseline);
        // More detail about setting and getting baseline is on page 12: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-sgp30-gas-tvoc-eco2-mox-sensor.pdf

        // Try to get baseline values
        uint16_t TVOC_base, eCO2_base;
        if (!sgp.getIAQBaseline(&eCO2_base, &TVOC_base))
        {
            // If it fails, print an error message and restart the loop
            Serial.println("Failed to get baseline readings");
            return;
        }

        // Print baseline values in hex format
        Serial.print("****Baseline values: eCO2: 0x");
        Serial.print(eCO2_base, HEX);
        Serial.print(" & TVOC: 0x");
        Serial.println(TVOC_base, HEX);
    }
}
