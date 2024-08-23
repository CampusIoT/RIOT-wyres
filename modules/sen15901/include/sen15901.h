/**
 * @ingroup     drivers_sen15901
 * @{
 *
 * @defgroup    drivers_SEN15901 Spark Fun SEN15901 Weather Meter Kit
 * @ingroup     drivers_sensors
 *
 * @brief       Spark fun meteo station driver
 *
 * @author      Pieau Maxime <maxime.pieau@etu.univ-grenoble-alpes.fr>
 *		Abelkalon Arthur <arthur.anelkalon@etu.univ-grenoble-alpes.fr>
 *		Lailler Tristan <tristan.lailler@etu.univ-grenoble-alpes.fr>
 *
 * @}
 */



#ifndef SEN15901_H
#define SEN15901_H

#ifdef __cplusplus
extern "C" {
#endif

#include "periph/adc.h"
#include "periph/gpio.h"


/**
 * @brief   SEN15901 driver parameters
 */
typedef struct SEN15901_PARAMS {

/* ADC - GPIO parameters, used for wind vane */
    adc_t adc;                  /* adc line */
    adc_res_t res; 			/* adc resolution */
    gpio_t sensor0_pin;     	  /* GPIO_PIN  */
    gpio_mode_t sensor0_mode;   /*  GPIO_MODE setting  */
/* GPIO parameters, used for anemometer */
    gpio_t sensor1_pin;           /*  GPIO_PIN  */
    gpio_mode_t sensor1_mode;       /*  GPIO_MODE setting  */
    gpio_flank_t sensor1_flank;       /*  Flank */
/* GPIO parameters, used for rain meter */
    gpio_t sensor2_pin;			 /*  GPIO_PIN  */
    gpio_mode_t sensor2_mode;       /*  GPIO_MODE setting */
    gpio_flank_t sensor2_flank;       /*  GPIO_FLANK setting */
    

} sen15901_params_t;

/**
 * @brief   SEN15901 device descriptor
 */
typedef struct {
    sen15901_params_t params; /**< driver parameters */
} sen15901_t;


/**
 * @brief   Named return values
 */
enum {
    SEN15901_OK = 0,             /**< all good */
    SEN15901_ERROR_ADC,          /**< ADC error */
    SEN15901_ERROR_GPIO,	/**< GPIO error */
    SEN15901_ERROR_CNF,          /**< Config error */
    SEN15901_ERROR_DEV,          /**< device error */
};

/**
 * @brief   Initialize a SEN15901 device
 *
 * @param[out] dev     device to initialize
 * @param[in] params  driver parameters
 *
 * @return SEN15901_OK on success
 * @return < 0 on error
 */
int sen15901_init(sen15901_t *dev, const sen15901_params_t *params);

/**
 * @brief   Read ADC value and get corresponding wind direction
 *
 * @param[in] dev    device to read
 * @param[out] data  wind direction
 *
 * @return SEN15901_OK on success
 * @return < 0 on error
 */
int sen15901_get_wind_direction(const sen15901_t *dev, uint16_t *data);

/**
 * @brief   Read wind ticks
 *
 *
 * @param[in] dev    device to read
 * @param[out] data  amount of interrupts
 *
 * @return SEN15901_OK on success
 * @return < 0 on error
 */
int sen15901_get_wind_ticks(const sen15901_t *dev, uint16_t *data);

/**
 * @brief   Read water ticks
 *
 * @param[in] dev    device to read
 * @param[out] data  amount of interrupts
 *
 * @return SEN15901_OK on success
 * @return < 0 on error
 */
 
int sen15901_get_water_ticks(const sen15901_t *dev, uint16_t  *data);


/**
 * @brief   callback function for interrupts
 *
 * @param[in] arg    pin that was called by interrupt
 *
 */


#ifdef __cplusplus
}
#endif

#endif /* SEN15901_H */
/** @} */
