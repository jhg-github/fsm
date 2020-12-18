/* Includes ------------------------------------------------------------------*/
#include "hsm_test.h"
#include "hsm_led.h"
#include "main.h"
#include "assert.h"
#include "static_allocator.h"
#include "queue.h"
#include "swtimer.h"

hsmLed_Hsm led_hsm;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	static hsmLed_Event led_evt;
	if(GPIO_Pin == GPIO_PIN_13){
		hsm_EventSetSignal(&led_evt.base, hsmLed_BUTT_PRESSED_SIG);
	}
	hsmLed_SendEvent( &led_hsm, &led_evt  );
}


/**
 * Call this from main
 */
void hsm_test(void){
	hsmLed_Ctor(&led_hsm,5);
	hsmLed_Init(&led_hsm);
//	swtimer_test();
	salloc_disable();
	while(1){
		swtimer_UpdateTimers();
		hsmLed_Run(&led_hsm);
	}
}
