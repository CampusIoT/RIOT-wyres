/**
 * @ingroup   boards_stm32l0538-disco
 * @{
 *
 * @file
 * @brief     Board specific configuration of direct mapped GPIOs
 *
 * @author    Alexandre Abadie <alexandre.abadie@inria.fr>
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
        .name = "LED_ROUGE",
        .pin = LED_ROUGE_PIN,
        .mode = GPIO_OUT
    },
    {
        .name = "LED_VERTE",
        .pin = LED_VERTE_PIN,
        .mode = GPIO_OUT
    },
    {
        .name = "LIGHT_SENSOR_SUPPLY",
        .pin  = LIGHT_SENSOR_SUPPLY_PIN,
        .mode = GPIO_OUT
    },
};

#ifdef __cplusplus
}
#endif

#endif /* GPIO_PARAMS_H */
/** @} */
