/*
 * Copyright (C) 2023 Université Grenoble Alpes
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_wyres-base
 * @{
 *
 * @file
 * @brief       Board specific definitions for the Wyres Base board.
 *
 * @author      Tristan Lailler <tristan.lailler@etu.univ-grenoble-alpes.fr
 * @author      Didier Donsez <didier.donsez@univ-grenoble-alpes.fr
 */

#ifndef GPIO_PARAMS_H
#define GPIO_PARAMS_H

#include "board.h"
#include "saul/periph.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief    GPIO pin configuration
 */
static const  saul_gpio_params_t saul_gpio_params[] =
{
    {
        .name = "LED_RED",
        .pin = LED_RED_PIN,
        .mode = GPIO_OUT
    },
    {
        .name = "LED_GREEN",
        .pin = LED_GREEN_PIN,
        .mode = GPIO_OUT
    },
    {
        .name = "LIGHT_SENSOR_SUPPLY",
        .pin  = LIGHT_SENSOR_SUPPLY_PIN,
        .mode = GPIO_OUT
    },
    {
        .name = "BTN0",
        .pin  = BTN0_PIN,
        .mode = BTN0_MODE
    },
};

#ifdef __cplusplus
}
#endif

#endif /* GPIO_PARAMS_H */
/** @} */
