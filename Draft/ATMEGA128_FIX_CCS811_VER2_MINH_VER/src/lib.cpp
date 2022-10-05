/**
 *  @file MinhVHN.h
 *
 *  @section introduction
 *
 *  @section author
 *
 *  Vu Huy Nhat Minh 20191973
 *
 *  @section library:
 *
 *  Sensor: TCS34725
 *  Vendor: Adafruit TCS34725
 *  Github: https://github.com/adafruit/Adafruit_TCS34725
 *
 *  Sensor: MAX9814
 *  Vendor: Adafruit MAX9814
 *  Github: https://github.com/adafruit/Adafruit-MAX9814-AGC-Microphone-PCB/
 *
 *  Sensor: CCS811
 *  Vendor: Adafruit CCS811
 *  Github: https://github.com/adafruit/Adafruit_CCS811
 *
 *  Sensor: TSL2561
 *  Vendor Adafruit TSL2561
 *  Github: https://github.com/adafruit/Adafruit_TSL2561
 */

#ifndef _MINHVHN_H_
#define _MINHVHN_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#include <SPI.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_CCS811.h>
#include <Adafruit_TSL2561_U.h>

/* Initialize tcs object */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
Adafruit_CCS811 ccs;
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

/**
 *  @brief  Read tcs sensor value and add to message
 *
 *  @param  mes
 *          Instance of obj
 */
void readTCS(JsonObject mes)
{
    // Read raw data from sensor
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    // Add to message json object
    mes["red"] = r;
    mes["green"] = g;
    mes["blue"] = b;
}

/**
 *  @brief  Read MAX9814 sensor value and add to message
 *
 *  @ref    https://learn.adafruit.com/adafruit-agc-electret-microphone-amplifier-max9814/downloads
 *          Example Sound Level Sketch for the Adafruit Microphone Amplifier
 *          https://forums.adafruit.com/viewtopic.php?t=94374
 *          https://sites.google.com/site/myscratchbooks/home/projects/project-19-using-max9812-mensaure-decibels-db-db-spl
 *
 *  @param  mes
 *          Instance of obj
 *
 *  @bug    noise variable need to check again, its value remains constantly
 */
void readMAX(JsonObject mes)
{
    // Start sampling time
    unsigned long startMillis = millis();

    // Max, min value of sound level
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    // Variable to count noise over 60dB
    unsigned int noise = 0;

    // Collect data for 50 ms (Sufficient lowest frequency 20Hz = 50ms)
    while (millis() - startMillis < 50)
    {
        unsigned int sample = analogRead(0);
        // Toss out spurious readings
        if (sample < 1024)
        {
            if (sample > signalMax)
            {
                // save just the max levels
                signalMax = sample;
            }
            else if (sample < signalMin)
            {
                // save just the min levels
                // if not the sample would compare with point zero only
                signalMin = sample;
            }
        }
    }

    // Peak-to-peak sound level/amplitude
    unsigned int peakToPeak = signalMax - signalMin;

    // Convert to volts (0 - 3.3) (ADC 10 bit: 0 - 1023)
    double volts = (peakToPeak * 3.3) / 1024;

    // Covert to decibel (approximately)
    // with the microphone sensitivity is -44db, so V RMS / PA is 0.006309
    double db = 20 * log10(volts / 0.006309);

    if (db > 60.0)
    {
        noise = noise + 1;
    }

    mes["sound"] = noise;
}

/**
 *  @brief  Read data from CCS811 sensor and add value to mes
 *
 *  @param  mes
 *          Instance of obj
 *
 *  @bug    The value read is not changeable
 */
void readCCS(JsonObject mes)
{
    if (ccs.available())
    {
        if (!ccs.readData())
        {
            mes["eco2"] = ccs.geteCO2();
            mes["tvoc"] = ccs.getTVOC();
        }
    }
}

/**
 *  @brief  Read data from TSL2561 sensor and add value to mes
 *
 *  @param  mes
 *          Instance of obj
 */
void readTSL(JsonObject mes)
{
    /* Get a new sensor event */
    sensors_event_t event;
    tsl.getEvent(&event);

    if (event.light)
    {
        mes["lux"] = event.light;
    }
}

#endif