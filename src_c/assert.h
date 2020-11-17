#ifndef __ASSERT_H
#define __ASSERT_H


/*
https://barrgroup.com/Embedded-Systems/How-To/Define-Assert-Macro
*/

/* Macros --------------------------------------------------------------------*/
#define ASSERT(expr) \
    if (expr) \
        {} \
    else \
        assert_AssertionFailed(__FILE__, __LINE__)


/* Public Functions -----------------------------------------------------------------*/    
void assert_AssertionFailed( char *file, int line );

    
#endif /* __ASSERT_H */


