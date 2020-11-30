#ifndef __SWTIMER_H
#define __SWTIMER_H


/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Types ---------------------------------------------------------------------*/
typedef struct swtimer_t swtimer_t;
typedef void (*swtimer_Callback_t)(void);


/* Public Functions ----------------------------------------------------------*/

void swtimer_UpdateTimers(void);

swtimer_t * swtimer_Constructor(void);
void swtimer_Start(swtimer_t * me, uint32_t period, swtimer_Callback_t callback, bool periodic);
void swtimer_Stop(swtimer_t * me);


/* Public Test Functions -------------------------------------------------------*/
void swtimer_test(void);

#endif // #ifndef __SWTIMER_H
