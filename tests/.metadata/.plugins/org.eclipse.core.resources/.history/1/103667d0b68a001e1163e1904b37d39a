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


int main(void)
{
	printf("\r\nToogle on board LEDs\r\n");

	LED_GREEN_ON;
	LED_RED_ON;
	
	xtimer_sleep(5);

	while(1){
		LED_GREEN_TOGGLE;
		xtimer_sleep(1);
		LED_GREEN_TOGGLE;
		xtimer_sleep(1);
		LED_RED_TOGGLE;
		xtimer_sleep(1);
		LED_RED_TOGGLE;
		xtimer_sleep(1);
		
		LED_GREEN_TOGGLE;
		xtimer_sleep(1);
		LED_RED_TOGGLE;
		xtimer_sleep(1);
		LED_GREEN_TOGGLE;
		xtimer_sleep(1);
		LED_RED_TOGGLE;
		xtimer_sleep(1);
	}
	
    return 0;
}
