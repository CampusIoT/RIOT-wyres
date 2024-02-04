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
 * @author      Didier Donsez <didier.donsez@univ-grenoble-alpes.fr
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H


#ifdef __cplusplus
extern "C" {
#endif

//#ifdef TODO
//#error To be implemented
/* This board provides a LSE, marked as X1 (32.768 KHz) on the board */
#ifndef CONFIG_BOARD_HAS_LSE
#define CONFIG_BOARD_HAS_LSE 1
#endif

/* This board provides a HSE, marked as X2 (16 MHz) on the board */
#ifndef CONFIG_BOARD_HAS_HSE
#define CONFIG_BOARD_HAS_HSE 1
#endif

/* The HSE provides a 16 MHz clock */
#ifndef CONFIG_CLOCK_HSE
#define CONFIG_CLOCK_HSE MHZ(16)
#endif
//#endif

#include "periph_cpu.h"
#include "clk_conf.h"

/**
 * @name    Timer configuration
 * @{
 */
#if 0
static const timer_conf_t timer_config[] = {
    {
        .dev      = TIM2,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM2EN,
        .bus      = APB1,
        .irqn     = TIM2_IRQn
    }
};

#define TIMER_0_ISR         isr_tim2

#define TIMER_NUMOF         ARRAY_SIZE(timer_config)

#else

static const timer_conf_t timer_config[] = {
    {
        .dev      = TIM3,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM3EN,
        .bus      = APB1,
        .irqn     = TIM3_IRQn
    }
};

#define TIMER_0_ISR         (isr_tim3)

#define TIMER_NUMOF         (sizeof(timer_config) / sizeof(timer_config[0]))


#endif


/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev        = USART1,
        .rcc_mask   = RCC_APB2ENR_USART1EN,
        .rx_pin     = GPIO_PIN(PORT_A, 10),
        .tx_pin     = GPIO_PIN(PORT_A, 9),
        .rx_af      = GPIO_AF7,
        .tx_af      = GPIO_AF7,
        .bus        = APB2,
        .irqn       = USART1_IRQn
    }
};

#define UART_0_ISR          (isr_usart1)

#define UART_NUMOF          ARRAY_SIZE(uart_config)
/** @} */

/**
 * @name   PWM configuration
 * @{
 */
static const pwm_conf_t pwm_config[] = {
    {
        .dev      = TIM2,
        .rcc_mask = RCC_APB1ENR_TIM2EN,
        .chan     = { { .pin = GPIO_PIN(PORT_A, 1) ,           .cc_chan = 1 },
                      { .pin = GPIO_UNDEF,                    .cc_chan = 0 },
                      { .pin = GPIO_UNDEF,                    .cc_chan = 0 },
                      { .pin = GPIO_UNDEF,                    .cc_chan = 0 } },
        .af       = GPIO_AF1,
        .bus      = APB1
    }
#if 0    
    ,
    {
        .dev      = TIM3,
        .rcc_mask = RCC_APB1ENR_TIM3EN,
        .chan     = { { .pin = GPIO_PIN(PORT_B, 4) /* D5 */, .cc_chan = 0 },
                      { .pin = GPIO_PIN(PORT_C, 7) /* D9 */, .cc_chan = 1 },
                      { .pin = GPIO_PIN(PORT_C, 8),          .cc_chan = 2 },
                      { .pin = GPIO_PIN(PORT_C, 9),          .cc_chan = 3 } },
        .af       = GPIO_AF2,
        .bus      = APB1
    }
#endif
};

#define PWM_NUMOF           ARRAY_SIZE(pwm_config)
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_conf_t spi_config[] = {
    {
    	// SPI bus dedicated to SX1272/SX1261
        .dev      = SPI1,
        .mosi_pin = GPIO_PIN(PORT_A,7),
        .miso_pin = GPIO_PIN(PORT_A,6),
        .sclk_pin = GPIO_PIN(PORT_A,5),
        .cs_pin   = GPIO_PIN(PORT_B,0),
        .mosi_af  = GPIO_AF5,
        .miso_af  = GPIO_AF5,
        .sclk_af  = GPIO_AF5,
        .rccmask  = RCC_APB2ENR_SPI1EN,
        .apbbus   = APB2
    }
#if 0
    ,
    {
    	// SPI bus for one external sensors (CN5 connector)
        .dev      = SPI2,
        .mosi_pin = GPIO_PIN(PORT_B, 15),   // I2S2_SD on Microphone (U4)
        .miso_pin = GPIO_PIN(PORT_B, 14),   
        .sclk_pin = GPIO_PIN(PORT_B, 13),  // I2S2_CLK on Microphone (U4)
        .cs_pin   = GPIO_PIN(PORT_B, 12),
        .mosi_af  = GPIO_AF5,
        .miso_af  = GPIO_AF5,
        .sclk_af  = GPIO_AF5,
        .cs_af    = GPIO_AF5,
        .rccmask  = RCC_APB1ENR_SPI2EN,
        .apbbus   = APB1
    },
#endif
};

#define SPI_NUMOF           ARRAY_SIZE(spi_config)
/** @} */

/**
 * @name I2C configuration
  * @{
 */
static const i2c_conf_t i2c_config[] = {
//#ifdef TODO
//#error To be implemented
    {
        .dev            = I2C1,
        .speed          = I2C_SPEED_NORMAL,
        .scl_pin        = GPIO_PIN(PORT_B, 8),
        .sda_pin        = GPIO_PIN(PORT_B, 9),
        .scl_af         = GPIO_AF4,
        .sda_af         = GPIO_AF4,
        .bus            = APB1,
        .rcc_mask       = RCC_APB1ENR_I2C1EN,
        .clk            = CLOCK_APB1,
        .irqn           = I2C1_EV_IRQn
    }
#if 0
    ,
    {
        .dev            = I2C2,
        .speed          = I2C_SPEED_NORMAL,
        .scl_pin        = GPIO_PIN(PORT_B, 10),
        .sda_pin        = GPIO_PIN(PORT_B, 11),
        .scl_af         = GPIO_AF4,
        .sda_af         = GPIO_AF4,
        .bus            = APB1,
        .rcc_mask       = RCC_APB1ENR_I2C2EN,
        .clk            = CLOCK_APB1,
        .irqn           = I2C2_EV_IRQn
    }
#endif    
//#endif
};

//#ifdef TODO
//#error To be implemented
#define I2C_0_ISR           isr_i2c1_ev
#if 0
#define I2C_1_ISR           isr_i2c2_ev
#endif

#define I2C_NUMOF           ARRAY_SIZE(i2c_config)
/** @} */


/**
 * @name    ADC configuration
 * @{
 */
static const adc_conf_t adc_config[] = {
    { GPIO_PIN(PORT_A, 3), 3} // Light sensor
};

#define ADC_NUMOF           ARRAY_SIZE(adc_config)

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
