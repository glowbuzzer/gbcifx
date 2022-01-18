/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: OS_Includes.h 6603 2014-10-02 14:57:53Z stephans $:

  Description:
    Headerfile for specific target system includes, data types and definitions

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2006-08-08  initial version (special OS dependencies must be added)

**************************************************************************************/

#ifndef __OS_INCLUDES__H
#define __OS_INCLUDES__H

#include <memory.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>

#define UNREFERENCED_PARAMETER(a) (a=a)

#ifndef NV
#define NV(var) #var,var
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef ZERO_MEMORY
#define ZERO_MEMORY(pX) memset(pX, 0, sizeof(*pX))
#endif

#ifndef SEC_TO_MSEC
#define SEC_TO_MSEC(sec) (sec*1000)
#endif

#ifndef SEC_TO_USEC
#define SEC_TO_USEC(sec) (SEC_TO_MSEC(sec)*1000)
#endif

#ifndef SEC_TO_NSEC
#define SEC_TO_NSEC(sec) (SEC_TO_USEC(sec)*1000)
#endif

#ifndef NSEC_TO_USEC
#define NSEC_TO_USEC(nsec) (nsec/1000)
#endif

#ifndef NSEC_TO_MSEC
#define NSEC_TO_MSEC(nsec) (NSEC_TO_USEC(nsec)/1000)
#endif


//  #error "Insert needed Target system definitions, data types and header files here"
/*
  #define APIENTRY

  #ifndef NULL
    #define NULL 0
  #endif

  #define UNREFERENCED_PARAMETER(a) (a=a)
*/
#endif /* __OS_INCLUDES__H */
