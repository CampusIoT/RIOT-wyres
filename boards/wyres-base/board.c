/*
 * Copyright (C) 2023 Université Grenoble Alpes
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_wyres_base
 * @{
 *
 * @file
 * @brief       Board specific definitions for the wyres_base board
 *
 * @author      Tristan Lailler <tristan.lailler@etu.univ-grenoble-alpes.fr>
 */

#include "board.h"
#include "periph/gpio.h"

void board_init(void)
{    /* initialize the boards LEDs */
    gpio_init(LED_RED_PIN, GPIO_OUT);  /* PIN 3 Port A */
    gpio_init(LED_GREEN_PIN, GPIO_OUT);  /* PIN 0 Port A */
    gpio_init(LIGHT_SENSOR_SUPPLY_PIN, GPIO_OUT);  /* PIN 6 Port B */
}
