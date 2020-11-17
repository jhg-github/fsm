/* Includes ------------------------------------------------------------------*/
#include "assert.h"



/* Public Functions ----------------------------------------------------------*/

static volatile char * assert_file;
static volatile int assert_line;
void assert_AssertionFailed( char *file, int line ){  
	assert_file = file;
	assert_line = line;
  while(1);
}

