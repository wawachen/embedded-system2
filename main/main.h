/*------------------------------------------------------------------*-

  main.h (2014-09-17)

  ------------------------------------------------------------------

  Demonstration for time-trigger architecture on LPC1769.


  This code should purely be used in training and teaching purposes for
  for MSc Reliable Embedded Systems programme.

  This code is copyright (c) University of Leicester 2014.
-*------------------------------------------------------------------*/

#ifndef _MAIN_H
#define _MAIN_H 1

#include "LPC17xx.h"
#include "lpc_types.h"

//#include <cr_section_macros.h>
//#include <NXP/crp.h>


// Required system operating frequency (in Hz)
// Will be checked in the scheduler initialisation file
#define Required_SystemCoreClock (100000000)


//------------------------------------------------------------------
// SHOULD NOT GENERALLY NEED TO EDIT THE SECTIONS BELOW
//------------------------------------------------------------------

#define RETURN_NORMAL 0
#define RETURN_ERROR 1

#endif

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/

