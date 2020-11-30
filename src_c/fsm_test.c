/* Includes ------------------------------------------------------------------*/
#include "fsm_test.h"
#include "fsm_led.h"
#include "main.h"
#include "assert.h"
#include "static_allocator.h"
#include "queue.h"
#include "swtimer.h"

fsmLed_Fsm led_fsm;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	static fsmLed_Event led_evt;
	if(GPIO_Pin == GPIO_PIN_13){
		fsm_EventSetSignal(&led_evt.base, fsmLed_BUTT_PRESSED_SIG);
	}
	Led_SendEvent( &led_fsm, &led_evt  );
}


/**
 * Call this from main
 */
void fsm_test(void){
	LedCtor(&led_fsm,5);
	Led_Init(&led_fsm);
//	swtimer_test();
	salloc_disable();
	while(1){
		swtimer_UpdateTimers();
		Led_Run(&led_fsm);
	}
}
