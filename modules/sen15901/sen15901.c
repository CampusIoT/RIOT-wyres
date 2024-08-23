/**
 * @ingroup     drivers_sen15901
 * @{
 *
 * @file
 * @brief       Spark fun meteo station functions 
 *
 * @author      Pieau Maxime <maxime.pieau@etu.univ-grenoble-alpes.fr>
 *		Abelkalon Arthur <arthur.anelkalon@etu.univ-grenoble-alpes.fr>
 *		Lailler Tristan <tristan.lailler@etu.univ-grenoble-alpes.fr>
 *
 * @}
 */
 
 
  
#include "sen15901.h"
#include <string.h>
#include "xtimer.h"
#include "board.h"

uint32_t last_button_change = 0;
uint32_t last_ext_gpio_change = 0;

uint32_t button_cnt = 0;
uint32_t gpio_cnt = 0;

#define DEBOUNCE_INTERVAL_BUTTON 10
#define DEBOUNCE_INTERVAL_EXT_GPIO 10


const float adc_values[] = { 
3143.44186, // 0 °
1624.06276, // 22.5 °
1845.45055,
335.096502,
372.363636,
263.664671,
738.622951,
506.166521,
1149.23741,
978.800609,
2520.61538,
2397.82421,
3780.92308,
3310.12126,
3549.13752,
2811.18193  // 337.5 °
};
const float angle_resolution = 22.5;

/**
 * @brief   Data constants for anemometer
 */

extern int SEN15901_INTERRUPT_COUNT1; // Variable used to count interrupts for anomometer
const int SEN15901_INTERRUPT_TO_SPEED = 666; // switch. A wind speed of 2.4km/h causes the switch to close once per second. -> 666 mm/s
/**
 * @brief   Data constants for rain meter
 */

extern int SEN15901_INTERRUPT_COUNT2; // Variable used to count interrupts for rain meter
const int SEN15901_INTERRUPT_TO_UM = 279; // milimeter of water for an interrupt (rising edge) = 0.2794 mm -> 279 µm
 
static void cb_boutton(void *arg){ //callback for interrupts
	uint32_t current_time;
	current_time = xtimer_now_usec();
	switch ((int)arg) {
		case 2:
			if ((current_time - last_button_change) > DEBOUNCE_INTERVAL_BUTTON) { // Bounce filtering by checking the time elapsed since the last change
				last_button_change = current_time;
				printf("INT: external interrupt from BTN1_PIN pin\n");
				button_cnt++;
				LED_RED_TOGGLE;
			}
			break;
			
		case 1:
			if ((current_time - last_ext_gpio_change) > DEBOUNCE_INTERVAL_EXT_GPIO) { // Bounce filtering by checking the time elapsed since the last change
				last_ext_gpio_change = current_time;
				gpio_cnt++;
				printf("INT: external interrupt from EXTERNAL_GPIO_PIN pin\n");
				LED_GREEN_TOGGLE;
			}
			break;
	}
}
 
 
 
 int sen15901_init(sen15901_t *dev, const sen15901_params_t *params){
 
 	memcpy(dev, params, sizeof(sen15901_params_t));
 
 	printf("\r\nConnecting to Meteo Station...\r\n");
	
	// Sensor 0 init
	if (gpio_init(params->sensor1_pin, params->sensor1_mode) < 0) {
		printf("error: init_int of SENSOR_0\n");
		return SEN15901_ERROR_GPIO;
	}

	// Sensor 0 adc init
	if (adc_init(params->adc) < 0) {
	        printf("\rerror: initialization of ADC failed\r\n");
		return SEN15901_ERROR_ADC;
	}
	printf("SENSOR (1/3) init succeed\n");
	
	
	//Sensor 1 init
	if (gpio_init_int(params->sensor1_pin, params->sensor1_mode, params->sensor1_flank, &cb_boutton, (void *)1) < 0) {
		printf("error: init_int of SENSOR_1\n");
		return SEN15901_ERROR_GPIO;
	}
	gpio_irq_enable(params->sensor1_pin);
	printf("SENSOR (2/3) init succeed\n");
	
	
	//Sensor 2 init
	if (gpio_init_int(params->sensor2_pin, params->sensor2_mode, params->sensor2_flank, &cb_boutton, (void *)2) < 0) {
		printf("error: init_int of SENSOR_2\n");
		return SEN15901_ERROR_GPIO;
	}
	gpio_irq_enable(params->sensor2_pin);
	printf("SENSOR (3/3) init succeed\n");

 	return SEN15901_OK;
 }

/**
 * @brief   Read ADC value and get corresponding wind direction
 *
 * @param[in] dev    device to read
 * @param[out] data  wind direction
 *
 * @return SEN15901_OK on success
 * @return < 0 on error
 */
int sen15901_get_wind_direction(const sen15901_t *dev, uint16_t *data){
	float mesure;
	mesure = adc_sample(dev->params.adc,dev->params.res);

	//Max diff(2^12-1)
	float min_dif = 4095;
	int index = 0;
	
	
	for(int i=0; i < 16; i++){
		float ADC_dif = adc_values[i] - mesure;

		ADC_dif = ADC_dif < 0 ? -ADC_dif : ADC_dif;

		if(ADC_dif < min_dif){ // Get the closest value from known ADC values
		    min_dif = ADC_dif;
		    index = i;
		}
	}
	
    	*data = index*angle_resolution;	
	return SEN15901_OK;
}

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
int sen15901_get_wind_ticks(const sen15901_t *dev, uint16_t *data){
	if (dev==NULL) return SEN15901_ERROR_DEV;
	*data=gpio_cnt;
	gpio_cnt=0;
	return SEN15901_OK;
}

/**
 * @brief   Read water ticks
 *
 * @param[in] dev    device to read
 * @param[out] data  amount of interrupts
 *
 * @return SEN15901_OK on success
 * @return < 0 on error
 */
 
 
int sen15901_get_water_ticks(const sen15901_t *dev, uint16_t  *data){
	if (dev==NULL) return SEN15901_ERROR_DEV;
	*data=button_cnt;
	button_cnt=0;
	return SEN15901_OK;
}
