/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       LED test
 *
 * @author      Didier DONSEZ
 *
 * @}
 */

#include "xtimer.h"

#include "board.h"
#include "periph/gpio.h"


int main(void)
{
	printf("\r\nRead button 1 state\r\n");

	uint8_t btn_state = 0;
	

	while(1){
		while(gpio_read(BTN1_PIN) == btn_state);
		btn_state = gpio_read(BTN1_PIN);
		if(btn_state){
			printf("Button 1 has been pressed!\r\n");
		}else{
			printf("Button 1 has been released!\r\n");
		}
	}
	
    return 0;
}
