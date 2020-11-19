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
			fsm_EventSetSignal((fsm_Event *)&led_evt, fsmLed_TURN_ON_SIG);
		} else {
			fsm_EventSetSignal((fsm_Event *)&led_evt, fsmLed_TURN_OFF_SIG);
		}
		Led_SendEvent( &led_fsm, (fsm_Event *)&led_evt  );
	}
}


/**
 * Call this from main
 */
void fsm_test(void){

	//fsmLed_Event * led_evt;

	LedCtor(&led_fsm,5);
	fsm_Init((fsm_Fsm *)&led_fsm, 0);

	//queue_test();
	
	while(1){
		Led_Run();
//		fsm_EventSetSignal((fsm_Event *)&led_evt, fsmLed_TURN_ON_SIG);
//		fsm_Dispatch((fsm_Fsm *)&led_fsm, (fsm_Event *)&led_evt);
//		HAL_Delay(50);
//		fsm_EventSetSignal((fsm_Event *)&led_evt, fsmLed_TURN_OFF_SIG);
//		fsm_Dispatch((fsm_Fsm *)&led_fsm, (fsm_Event *)&led_evt);
//		HAL_Delay(50);
	}
}
