/*
 * Copyright (C) 2023 Université Grenoble Alpes
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Cayenne Low Power Payload example application
 *
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 *
 * @}
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define M_PI  (3.14159265358979323846)

#include "ztimer.h"

#include "cayenne_lpp.h"

static cayenne_lpp_t lpp;

static void _print_buffer(const uint8_t *buffer, size_t len, const char *msg)
{
    printf("%s: ", msg);
    for (uint8_t i = 0; i < len; i++)
    {
        printf("%02X", buffer[i]);
    }
}

/*
 * For emulating a track
 */
static void cassiniOval(double time, double a, double b, double *x, double *y)
{
    // Exemple de paramétrisation (à ajuster en fonction de tes besoins)
    double t = time; // Utilise le temps comme paramètre
    *x = a * cos(t);
    *y = b * sin(t);
}

int main(void)
{

    puts("High altitude balloon track simulator");

    double init_latitude = 45.5;
    double init_longitude = 5.5;
    double init_altitude = 10000;  // meter
    double init_pressure = 500;    // hPa
    double init_temperature = -20; // °C
    double init_humidity = 50;
    double init_luninosity = 500;
    double init_battery_voltage = 3600; // mV

    int t = 0;
    while (true)
    {
        double step = t *  M_PI * 2 / 3600;

        double latitude;
        double longitude;
        cassiniOval(step, 1, 2, &latitude, &longitude);
        latitude += init_latitude;
        longitude += init_longitude;
        double altitude = init_altitude + 8000 * cos(step);     // meter
        double pressure = init_pressure + 400 * cos(step);      // hPa
        double temperature = init_temperature + 40 * cos(step); // °C
        double humidity = init_humidity + 50 * cos(step);
        double luninosity = init_luninosity + 500 * cos(step);
        double battery_voltage = init_battery_voltage - step; // mV

        cayenne_lpp_reset(&lpp);
        cayenne_lpp_add_temperature(&lpp, 1, temperature);
        cayenne_lpp_add_relative_humidity(&lpp, 2, humidity);
        cayenne_lpp_add_barometric_pressure(&lpp, 3, pressure);
        cayenne_lpp_add_luminosity(&lpp, 4, luninosity);
        cayenne_lpp_add_gps(&lpp, 5, latitude, longitude, altitude);
        cayenne_lpp_add_analog_input(&lpp, 6, battery_voltage);

        printf("\n==== Point #%d ====\n",t);

        printf(" temperature:     %.2f °C\n",temperature);
        printf(" humidity:        %.1f RH\n",humidity);
        printf(" pressure:        %.0f hPa\n",pressure);
        printf(" luninosity:      %.1f lux\n",luninosity);
        printf(" position:        lat=%.5f° lon=%.5f° alt=%.0fm\n",latitude, longitude, altitude);
        printf(" battery_voltage: %.1f mV\n",battery_voltage);

        _print_buffer(lpp.buffer, lpp.cursor, "LPP: ");

        ztimer_sleep(ZTIMER_SEC, 1);

        t++;
    }
}
