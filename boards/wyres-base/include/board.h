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

#ifndef BOARD_H
#define BOARD_H


#include <stdint.h>

#include "cpu.h"
#include "periph_conf.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Xtimer configuration
 * @{
 */
// All timers that are less than XTIMER_BACKOFF ticks in the future will just spin.
//#define XTIMER_BACKOFF              (11)
#define XTIMER_WIDTH                  (16)
/** @} */

/**
 * @name    sx1272 configuration
 * @{
 */

#define SX127X_PARAM_SPI                    (SPI_DEV(0))

#define SX127X_PARAM_SPI_NSS                GPIO_PIN(PORT_B,0)       /* SPI1_CS */
#define SX127X_PARAM_RESET                  GPIO_PIN(PORT_A,2)       /* PA2 */
#define SX127X_PARAM_DIO0                   GPIO_PIN(PORT_B,1)       /* PA10 */
#define SX127X_PARAM_DIO1                   GPIO_PIN(PORT_B,10)      /* PB10 */
#define SX127X_PARAM_DIO2                   GPIO_PIN(PORT_B,11)      /* PB11 */
#define SX127X_PARAM_DIO3                   GPIO_PIN(PORT_B,7)       /* PB7 */
#define SX127X_PARAM_DIO4                   GPIO_PIN(PORT_B,5)       /* PB5 */
#define SX127X_PARAM_DIO5                   GPIO_PIN(PORT_B,4)       /* PB4 */

/**< RFO HF or RFO LF */
#define SX127X_PARAM_PASELECT               (SX127X_PA_RFO)

// antenna rx/tx switch management is independant of the radio type 
// code to manipulate these IO is in the BSP
#define SX127X_PARAM_TX_SWITCH              GPIO_PIN(PORT_A,4)		/* PA4 */
#define SX127X_PARAM_RX_SWITCH              GPIO_PIN(PORT_C,13)		/* PC13 */

/** @} */


/**
 * @name Macros for controlling the on-board LEDs.
 * @{
 */
#define LED_RED_PIN            	GPIO_PIN(PORT_A,15)
#define LED_RED_PORT           	GPIOA
#define LED_RED_MASK           	(1 << 15)
#define LED_RED_MODE           	GPIO_OUT

#define LED_RED_ON             	(LED_RED_PORT->BSRR |= LED_RED_MASK)
#define LED_RED_OFF            	(LED_RED_PORT->BSRR |= LED_RED_MASK<<16)
#define LED_RED_TOGGLE         	(LED_RED_PORT->ODR  ^= LED_RED_MASK)

#define LED_GREEN_PIN           GPIO_PIN(PORT_A,0)
#define LED_GREEN_PORT          GPIOA
#define LED_GREEN_MASK          (1)
#define LED_GREEN_MODE           GPIO_OUT

#define LED_GREEN_ON            (LED_GREEN_PORT->BSRR |= LED_GREEN_MASK)
#define LED_GREEN_OFF           (LED_GREEN_PORT->BSRR |= LED_GREEN_MASK<<16)
#define LED_GREEN_TOGGLE        (LED_GREEN_PORT->ODR  ^= LED_GREEN_MASK)
/** @} */

/**
 * @name Light sensor supply
 * @{
 */
#define LIGHT_SENSOR_SUPPLY_PIN            GPIO_PIN(PORT_A,3)
#define LIGHT_SENSOR_SUPPLY_PORT           GPIOA
#define LIGHT_SENSOR_SUPPLY_MASK           (1 << 3)
#define LIGHT_SENSOR_SUPPLY_MODE           GPIO_OUT

#define LIGHT_SENSOR_SUPPLY_ON             (LIGHT_SENSOR_SUPPLY_PORT->BSRR |= LIGHT_SENSOR_SUPPLY_MASK)
#define LIGHT_SENSOR_SUPPLY_OFF            (LIGHT_SENSOR_SUPPLY_PORT->BSRR |= LIGHT_SENSOR_SUPPLY_MASK<<16)
#define LIGHT_SENSOR_SUPPLY_TOGGLE         (LIGHT_SENSOR_SUPPLY_PORT->ODR  ^= LIGHT_SENSOR_SUPPLY_MASK)

/** @} */


/**
 * @name External GPIO on pad TP3
 * @{
 */
#define EXTERNAL_GPIO_PIN            			GPIO_PIN(PORT_A,8)
#define EXTERNAL_GPI0_PORT           			GPIOA
#define EXTERNAL_GPI0_MASK           			(1 << 8)

/** @} */


/**
 * @name Speaker PWM on pads TP14/1P15
 * @{
 */
#define SPEAKER_PWM_PIN            				GPIO_PIN(PORT_A,1)
#define SPEAKER_PWM_PORT           				GPIOA
#define SPEAKER_PWM_MASK           				(1 << 1)

/** @} */


/**
 * @name Button 0 on pads TP7/TP10
 * @{
 */
#define BTN0_PIN            				GPIO_PIN(PORT_B,3)
#define BTN0_PORT           				GPIOB
#define BTN0_MASK           				(1 << 3)
#define BTN0_MODE           				GPIO_IN_PD

/** @} */


/**
 * @brief Initialize board specific hardware, including clock, LEDs and std-IO
 */
//void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
