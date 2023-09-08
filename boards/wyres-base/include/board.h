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
#define LED0_PIN            	GPIO_PIN(PORT_A,15)
#define LED_RED_PIN            	GPIO_PIN(PORT_A,15)
#define LED_RED_PORT           	GPIOA
#define LED_RED_MASK           	(1 << 15)

#define LED_RED_ON             	(LED_RED_PORT->BSRR |= LED_RED_MASK)
#define LED_RED_OFF            	(LED_RED_PORT->BSRR |= LED_RED_MASK<<16)
#define LED_RED_TOGGLE         	(LED_RED_PORT->ODR  ^= LED_RED_MASK)

#define LED1_PIN            	GPIO_PIN(PORT_A,0)
#define LED_GREEN_PIN           GPIO_PIN(PORT_A,0)
#define LED_GREEN_PORT          GPIOA
#define LED_GREEN_MASK          (1)

#define LED_GREEN_ON            (LED_GREEN_PORT->BSRR |= LED_GREEN_MASK)
#define LED_GREEN_OFF           (LED_GREEN_PORT->BSRR |= LED_GREEN_MASK<<16)
#define LED_GREEN_TOGGLE        (LED_GREEN_PORT->ODR  ^= LED_GREEN_MASK)
/** @} */

/**
 * @name Light sensor supply
 * @{
 */
#define LIGHT_SENSOR_SUPPLY_PIN            GPIO_PIN(PORT_B,6)
#define LIGHT_SENSOR_SUPPLY_PORT           GPIOB
#define LIGHT_SENSOR_SUPPLY_MASK           (1 << 6)

#define LIGHT_SENSOR_SUPPLY_ON             (LIGHT_SENSOR_SUPPLY_PORT->BSRR |= LIGHT_SENSOR_SUPPLY_MASK)
#define LIGHT_SENSOR_SUPPLY_OFF            (LIGHT_SENSOR_SUPPLY_PORT->BSRR |= LIGHT_SENSOR_SUPPLY_MASK<<16)
#define LIGHT_SENSOR_SUPPLY_TOGGLE         (LIGHT_SENSOR_SUPPLY_PORT->ODR  ^= LIGHT_SENSOR_SUPPLY_MASK)

/** @} */


/**
 * @name Speaker PWM
 * @{
 */
#define SPEAKER_PWM_PIN            			GPIO_PIN(PORT_A,1)
#define SPEAKER_PWM_PORT           			GPIOA
#define SPEAKER_PWM_MASK           			(1 << 1)

/** @} */


/**
 * @name Button
 * @{
 */
#define BTN0_PIN            				GPIO_PIN(PORT_B,3)
#define BTN0_PORT           				GPIOB
#define BTN0_MASK           				(1 << 3)

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
