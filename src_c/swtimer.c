/* Includes ------------------------------------------------------------------*/
#include "swtimer.h"
#include "static_allocator.h"
#include "assert.h"


/* Constants -----------------------------------------------------------------*/
#define SWTIMER_N_TIMERS	(2)


/* Types ---------------------------------------------------------------------*/
struct swtimer_t {
  bool enabled;
	uint32_t period;
	uint32_t startTime;
	swtimer_Callback_t callback;
	bool periodic;
};


/* Vaiables ------------------------------------------------------------------*/
static swtimer_t * swtimer_timersArray[SWTIMER_N_TIMERS];
static int swtimer_timersCounter = 0;


/* Public Functions ----------------------------------------------------------*/
void swtimer_UpdateTimers(void){
	int i;
	uint32_t now = HAL_GetTick();
	for(i=0;i<swtimer_timersCounter;i++){		
		if(swtimer_timersArray[i]->enabled){
			if( now >= (swtimer_timersArray[i]->startTime + swtimer_timersArray[i]->period)){
				if( swtimer_timersArray[i]->periodic){
					swtimer_timersArray[i]->startTime = now;
				} else {
					swtimer_timersArray[i]->enabled = false;
				}
				swtimer_timersArray[i]->callback();
			}
		}
	}
}

swtimer_t * swtimer_Constructor(void){
  swtimer_t * timer;  
	
	ASSERT(swtimer_timersCounter<SWTIMER_N_TIMERS);	// check limit of timers
  timer = salloc_4bytes(sizeof(swtimer_t));
	timer->enabled = false;
	swtimer_timersArray[swtimer_timersCounter] = timer;
	swtimer_timersCounter++;
  return timer;
}

void swtimer_Start(swtimer_t * me, uint32_t period, swtimer_Callback_t callback, bool periodic){
	ASSERT(me);
	me->startTime = HAL_GetTick();
	me->period = period;
	me->callback = callback;
	me->periodic = periodic;
	me->enabled = true;
}

void swtimer_Stop(swtimer_t * me){
	ASSERT(me);
	me->enabled = false;
}


/* Public Test Functions -------------------------------------------------------*/
static swtimer_t * swtimer_test_timer;

static void swtimer_test_callback(void){
	static int counter = 0;
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	if(++counter >= 100){
		swtimer_Stop(swtimer_test_timer);
	}
}

void swtimer_test(void){
	swtimer_test_timer = swtimer_Constructor();
	swtimer_Start(swtimer_test_timer, 100, swtimer_test_callback, true);
}

