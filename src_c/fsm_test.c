/* Includes ------------------------------------------------------------------*/
#include "fsm_test.h"
#include "fsm_led.h"
#include "main.h"
#include "assert.h"
#include "static_allocator.h"
#include "queue.h"


fsmLed_Fsm led_fsm;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	static fsmLed_Event led_evt;
	if(GPIO_Pin == GPIO_PIN_13){
		if( led_evt.base.signal == fsmLed_TURN_OFF_SIG){
			fsm_EventSetSignal(&led_evt.base, fsmLed_TURN_ON_SIG);
		} else {
			fsm_EventSetSignal(&led_evt.base, fsmLed_TURN_OFF_SIG);
		}
		Led_SendEvent( &led_fsm, &led_evt  );
	}
}


/**
 * Call this from main
 */
void fsm_test(void){
	LedCtor(&led_fsm,5);
	Led_Init(&led_fsm);
	while(1){
		Led_Run(&led_fsm);
	}
}
