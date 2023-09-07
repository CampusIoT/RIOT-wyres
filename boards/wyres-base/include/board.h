/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_stm32l0538-disco
 * @{
 *
 * @file
 * @brief       Board specific definitions for the STM32L0538-DISCO evaluation board.
 *
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Xtimer configuration
 * @{
 */
#define XTIMER_WIDTH                (16)
/** @} */

/**
 * @name Macros for controlling the on-board LEDs.
 * @{
 */
#define LED_ROUGE_PIN            GPIO_PIN(PORT_A, 15)
#define LED_ROUGE_PORT           GPIOA
#define LED_ROUGE_MASK           (1 << 15)

#define LED_ROUGE_ON             (LED_ROUGE_PORT->BSRR |= LED_ROUGE_MASK)
#define LED_ROUGE_OFF            (LED_ROUGE_PORT->BSRR |= LED_ROUGE_MASK<<16)
#define LED_ROUGE_TOGGLE         (LED_ROUGE_PORT->ODR  ^= LED_ROUGE_MASK)

#define LED_VERTE_PIN            GPIO_PIN(PORT_A, 0)
#define LED_VERTE_PORT           GPIOA
#define LED_VERTE_MASK           (1)

#define LED_VERTE_ON             (LED_VERTE_PORT->BSRR |= LED_VERTE_MASK)
#define LED_VERTE_OFF            (LED_VERTE_PORT->BSRR |= LED_VERTE_MASK<<16)
#define LED_VERTE_TOGGLE         (LED_VERTE_PORT->ODR  ^= LED_VERTE_MASK)
/** @} */

/**
 * @name Light sensor supply
 * @{
 */
#define LIGHT_SENSOR_SUPPLY_PIN            GPIO_PIN(PORT_B, 6)
#define LIGHT_SENSOR_SUPPLY_PORT           GPIOB
#define LIGHT_SENSOR_SUPPLY_MASK           (1 << 6)

#define LIGHT_SENSOR_SUPPLY_ON             (LIGHT_SENSOR_SUPPLY_PORT->BSRR |= LIGHT_SENSOR_SUPPLY_MASK)
#define LIGHT_SENSOR_SUPPLY_OFF            (LIGHT_SENSOR_SUPPLY_PORT->BSRR |= LIGHT_SENSOR_SUPPLY_MASK<<16)
#define LIGHT_SENSOR_SUPPLY_TOGGLE         (LIGHT_SENSOR_SUPPLY_PORT->ODR  ^= LIGHT_SENSOR_SUPPLY_MASK)

/** @} */


/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
