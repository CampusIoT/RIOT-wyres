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
{
    /* initialize the VCC of Grove connectors  */
    gpio_init(VCC_UART_PIN, VCC_UART_MODE);  /* PA11 */
    gpio_init(VCC_I2C_PIN, VCC_I2C_MODE);  /* PA12 */

#ifdef LOW_POWER_MODE
    VCC_UART_OFF;
    VCC_I2C_OFF;
#else
    VCC_UART_ON;
    VCC_I2C_ON;
#endif

    /* initialize the on boards LEDs */
    gpio_init(LED_RED_PIN, LED_RED_MODE);  /* PA3 */
    gpio_init(LED_GREEN_PIN, LED_GREEN_MODE);  /* PA0 */

    gpio_init(LIGHT_SENSOR_SUPPLY_PIN, LIGHT_SENSOR_SUPPLY_MODE);  /* PB6 */

    gpio_init(BTN0_PIN, BTN0_MODE);  /* PB3 */

#ifdef TODO
#error TODO gpio_init for SPEAKER_PWM_PIN
#error TODO gpio_init for EXTERNAL_GPIO_PIN
#endif
}
