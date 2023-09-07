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
    gpio_init(LED_ROUGE_PIN, GPIO_OUT);  /* PIN 3 Port A */
    gpio_init(LED_VERTE_PIN, GPIO_OUT);  /* PIN 0 Port A */
    gpio_init(LIGHT_SENSOR_SUPPLY_PIN, GPIO_OUT);  /* PIN 6 Port B */
}
