#ifndef __SWTIMER_H
#define __SWTIMER_H


/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Types ---------------------------------------------------------------------*/
typedef struct swtimer_t swtimer_t;
typedef void (*swtimer_Callback_t)(void *);

typedef struct swtimer_fsm_t swtimer_fsm_t;


/* Public Functions ----------------------------------------------------------*/

void swtimer_UpdateTimers(void);

swtimer_t * swtimer_Constructor(void);
void swtimer_Start(swtimer_t * me, uint32_t period, bool periodic, swtimer_Callback_t callback, void * callback_data);
void swtimer_Stop(swtimer_t * me);


/* Public Test Functions -------------------------------------------------------*/
void swtimer_test(void);

#endif // #ifndef __SWTIMER_H
