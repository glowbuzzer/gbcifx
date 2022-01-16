/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: OS_Custom.c 13037 2019-08-07 07:25:25Z LuisContreras $:

  Description:
    Target system abstraction layer

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2011-12-13  added OS_Time() function body
    2006-08-07  initial version

**************************************************************************************/

/*****************************************************************************/
/*! \file OS_Custom.c
*    Sample Target system abstraction layer. Implementation must be done
*    according to used target system                                         */
/*****************************************************************************/

#include "OS_Dependent.h"
#include "cifXErrors.h"
#include "cifXHWFunctions.h"
#include "OS_Includes.h"

#define NSEC_PER_SEC (1000U * 1000U * 1000U)

//#error "Implement target system abstraction in this file"

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_OS_ABSTRACTION Operating System Abstraction
*    \{                                                                      */
/*****************************************************************************/

/*****************************************************************************/
/*! Memory allocation function
*   \param ulSize    Length of memory to allocate
*   \return Pointer to allocated memory                                      */
/*****************************************************************************/
void* OS_Memalloc(uint32_t ulSize)
{
    return malloc(ulSize);
}

/*****************************************************************************/
/*! Memory freeing function
*   \param pvMem Memory block to free                                        */
/*****************************************************************************/
void OS_Memfree(void* pvMem)
{
    free(pvMem);
}

/*****************************************************************************/
/*! Memory reallocating function (used for resizing dynamic toolkit arrays)
*   \param pvMem     Memory block to resize
*   \param ulNewSize new size of the memory block
*   \return pointer to the resized memory block                              */
/*****************************************************************************/
void* OS_Memrealloc(void* pvMem, uint32_t ulNewSize)
{
    return realloc(pvMem, ulNewSize);
}

/*****************************************************************************/
/*! Memory setting
*   \param pvMem     Memory block
*   \param bFill     Byte to use for memory initialization
*   \param ulSize    Memory size for initialization)                         */
/*****************************************************************************/
void OS_Memset(void* pvMem, uint8_t bFill, uint32_t ulSize)
{
    memset(pvMem, bFill, ulSize);
}

/*****************************************************************************/
/*! Copy memory from one block to another
*   \param pvDest    Destination memory block
*   \param pvSrc     Source memory block
*   \param ulSize    Copy size in bytes                                      */
/*****************************************************************************/
void OS_Memcpy(void* pvDest, void* pvSrc, uint32_t ulSize)
{
    memcpy(pvDest, pvSrc, ulSize);
}

/*****************************************************************************/
/*! Compare two memory blocks
*   \param pvBuf1    First memory block
*   \param pvBuf2    Second memory block
*   \param ulSize    Compare size in bytes
*   \return 0 if both buffers are equal                                      */
/*****************************************************************************/
int OS_Memcmp(void* pvBuf1, void* pvBuf2, uint32_t ulSize)
{
    return memcmp(pvBuf1, pvBuf2, ulSize);
}

/*****************************************************************************/
/*! Move memory
*   \param pvDest    Destination memory
*   \param pvSrc     Source memory
*   \param ulSize    Size in byte to move                                    */
/*****************************************************************************/
void OS_Memmove(void* pvDest, void* pvSrc, uint32_t ulSize)
{
    memmove(pvDest, pvSrc, ulSize);
}


/*****************************************************************************/
/*! Sleep for a specific time
*   \param ulSleepTimeMs  Time in ms to sleep for                            */
/*****************************************************************************/
void OS_Sleep(uint32_t ulSleepTimeMs)
{
    usleep(ulSleepTimeMs * 1000);
}

/*****************************************************************************/
/*! Retrieve a counter based on millisecond used for timeout monitoring
*   \return Current counter value (resolution of this value will influence
*           timeout monitoring in driver/toolkit functions(                  */
/*****************************************************************************/
uint32_t OS_GetMilliSecCounter(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    return (uint32_t)( SEC_TO_MSEC(now.tv_sec) + NSEC_TO_MSEC(now.tv_nsec));
}

/*****************************************************************************/
/*! Create an auto reset event
*   \return handle to the created event                                      */
/*****************************************************************************/
void* OS_CreateEvent(void)
{
    return NULL;
}

/*****************************************************************************/
/*! Set an event
*   \param pvEvent Handle to event being signalled                           */
/*****************************************************************************/
void OS_SetEvent(void* pvEvent)
{
    UNREFERENCED_PARAMETER(pvEvent);
}

/*****************************************************************************/
/*! Reset an event
*   \param pvEvent Handle to event being reset                               */
/*****************************************************************************/
void OS_ResetEvent(void* pvEvent)
{
    UNREFERENCED_PARAMETER(pvEvent);
}

/*****************************************************************************/
/*! Delete an event
*   \param pvEvent Handle to event being deleted                             */
/*****************************************************************************/
void OS_DeleteEvent(void* pvEvent)
{
    UNREFERENCED_PARAMETER(pvEvent);
}

/*****************************************************************************/
/*! Wait for the signalling of an event
*   \param pvEvent   Handle to event being wait for
*   \param ulTimeout Timeout in ms to wait for event
*   \return 0 if event was signalled                                         */
/*****************************************************************************/
uint32_t OS_WaitEvent(void* pvEvent, uint32_t ulTimeout)
{
    UNREFERENCED_PARAMETER(pvEvent);
    UNREFERENCED_PARAMETER(ulTimeout);

    return CIFX_EVENT_SIGNALLED;
}

/*****************************************************************************/
/*! Compare two ASCII string
*   \param pszBuf1   First buffer
*   \param pszBuf2   Second buffer
*   \return 0 if strings are equal                                           */
/*****************************************************************************/
int OS_Strcmp(const char* pszBuf1, const char* pszBuf2)
{
    return strcmp(pszBuf1, pszBuf2);
}

/*****************************************************************************/
/*! Compare characters of two strings without regard to case
*   \param pszBuf1   First buffer
*   \param pszBuf2   Second buffer
*   \param ulLen     Number of characters to compare
*   \return 0 if strings are equal                                           */
/*****************************************************************************/
int OS_Strnicmp(const char* pszBuf1, const char* pszBuf2, uint32_t ulLen)
{
    return strncasecmp(pszBuf1, pszBuf2, ulLen);
}  

/*****************************************************************************/
/*! Query the length of an ASCII string
*   \param szText    ASCII string
*   \return character count of szText                                        */
/*****************************************************************************/
int OS_Strlen(const char* szText)
{
    return (int32_t) strlen(szText);
}

/*****************************************************************************/
/*! Copies one string to another monitoring the maximum length of the target
*   buffer.
*   \param szDest    Destination buffer
*   \param szSource  Source buffer
*   \param ulLength  Maximum length to copy
*   \return pointer to szDest                                                */
/*****************************************************************************/
char* OS_Strncpy(char* szDest, const char* szSource, uint32_t ulLength)
{
    return strncpy(szDest, szSource, ulLength);
}


/*****************************************************************************/
/*! Create an interrupt safe locking mechanism (Spinlock/critical section)
*   \return handle to the locking object                                     */
/*****************************************************************************/
void* OS_CreateLock(void)
{
    return OS_CreateMutex();
}

/*****************************************************************************/
/*! Enter a critical section/spinlock
*   \param pvLock Handle to the locking object                               */
/*****************************************************************************/
void OS_EnterLock(void* pvLock)
{
}

/*****************************************************************************/
/*! Leave a critical section/spinlock
*   \param pvLock Handle to the locking object                               */
/*****************************************************************************/
void OS_LeaveLock(void* pvLock)
{
}

/*****************************************************************************/
/*! Delete a critical section/spinlock object
*   \param pvLock Handle to the locking object being deleted                 */
/*****************************************************************************/
void OS_DeleteLock(void* pvLock)
{
    OS_DeleteMutex(pvLock);
}

/*****************************************************************************/
/*! Create an Mutex object for locking code sections 
*   \return handle to the mutex object                                       */
/*****************************************************************************/
void* OS_CreateMutex(void)
{
    return (void*)0x12345678;
}

/*****************************************************************************/
/*! Wait for mutex
*   \param pvMutex    Handle to the Mutex locking object
*   \param ulTimeout  Wait timeout                                           
*   \return !=0 on succes                                                    */
/*****************************************************************************/
int OS_WaitMutex(void* pvMutex, uint32_t ulTimeout)
{
    return 1;
}

/*****************************************************************************/
/*! Release a mutex section section
*   \param pvMutex Handle to the locking object                              */
/*****************************************************************************/
void OS_ReleaseMutex(void* pvMutex)
{
    return;
}

/*****************************************************************************/
/*! Delete a Mutex object
*   \param pvMutex Handle to the mutex object being deleted                  */
/*****************************************************************************/
void OS_DeleteMutex(void* pvMutex)
{
}

/*****************************************************************************/
/*! Opens a file in binary mode
*   \param szFile     Full file name of the file to open
*   \param pulFileLen Returned length of the opened file
*   \return handle to the file, NULL mean file could not be opened           */
/*****************************************************************************/
void* OS_FileOpen(char* szFile, uint32_t* pulFileLen)
{
    assert(szFile != NULL);
    assert(pulFileLen != NULL);

    char pwd[200];
    getcwd(pwd, sizeof(pwd));
    int32_t iFile;
    void* pvRet = NULL;

    USER_Trace(NULL, TRACE_LEVEL_DEBUG, "OS_FileOpen(%s)", szFile);

    iFile = open(szFile, O_RDONLY);
    if (iFile != -1)
    {
        struct stat tBuffer;
        ZERO_MEMORY(&tBuffer);

        if (fstat(iFile, &tBuffer) != -1)
        {
            *pulFileLen = (uint32_t) tBuffer.st_size;
            pvRet = (void*) iFile;
        }
    }

    return pvRet;
}

/*****************************************************************************/
/*! Closes a previously opened file
*   \param pvFile Handle to the file being closed                            */
/*****************************************************************************/
void OS_FileClose(void* pvFile)
{
    assert(pvFile);

    int32_t iFile = (int32_t) pvFile;
    USER_Trace(NULL, TRACE_LEVEL_DEBUG, "OS_FileClose");

    close(iFile);
}

/*****************************************************************************/
/*! Read a specific amount of bytes from the file
*   \param pvFile   Handle to the file being read from
*   \param ulOffset Offset inside the file, where read starts at
*   \param ulSize   Size in bytes to be read
*   \param pvBuffer Buffer to place read bytes in
*   \return number of bytes actually read from file                          */
/*****************************************************************************/
uint32_t OS_FileRead(void* pvFile, uint32_t ulOffset, uint32_t ulSize, void* pvBuffer)
{
    assert(pvFile != NULL);
    assert(pvBuffer != NULL);

    int32_t iFile = (int32_t) pvFile;
    uint32_t ulRet = 0;

    USER_Trace( NULL, TRACE_LEVEL_DEBUG, "%s ()", __func__);

    if (ulOffset == (uint32_t) lseek(iFile, (int32_t) ulOffset, SEEK_SET))
    {
        ulRet = (uint32_t) read(iFile, pvBuffer, ulSize);
    }

    return ulRet;

}

/*****************************************************************************/
/*! OS specific initialization (if needed), called during cifXTKitInit()     
/*!  \return CIFX_NO_ERROR on success                                        */
/*****************************************************************************/
int32_t OS_Init()
{
//    s_fOSInitDone = 1;

    return CIFX_NO_ERROR;
}

/*****************************************************************************/
/*! OS specific de-initialization (if needed), called during cifXTKitInit()  */
/*****************************************************************************/
void OS_Deinit()
{
}

/*****************************************************************************/
/*! This functions is called for PCI cards in the toolkit. It is expected to
* write back all BAR's (Base address registers), Interrupt and Command
* Register. These registers are invalidated during cifX Reset and need to be
* re-written after the reset has succeeded
*   \param pvOSDependent OS Dependent Variable passed during call to
*                        cifXTKitAddDevice
*   \param pvPCIConfig   Configuration returned by OS_ReadPCIConfig
*                        (implementation dependent)                          */
/*****************************************************************************/
void OS_WritePCIConfig(void* pvOSDependent, void* pvPCIConfig)
{
  /* TODO: Implement PCI register accesss, needed for cifX cards, */
}

/*****************************************************************************/
/*! This functions is called for PCI cards in the toolkit. It is expected to
* read all BAR's (Base address registers), Interrupt and Command Register.
* These registers are invalidated during cifX Reset and need to be
* re-written after the reset has succeeded
*   \param pvOSDependent OS Dependent Variable passed during call to
*                        cifXTKitAddDevice
*   \return pointer to stored register copies (implementation dependent)     */
/*****************************************************************************/
void* OS_ReadPCIConfig(void* pvOSDependent)
{
  /* TODO: Implement PCI register accesss, needed for cifX cards. */
}

/*****************************************************************************/
/*! This function Maps a DPM pointer to a user application if needed.
*   This example just returns the pointer valid inside the driver.
*   \param pvDriverMem   Pointer to be mapped
*   \param ulMemSize     Size to be mapped
*   \param ppvMappedMem  Returned mapped pointer (usable by application)
*   \param pvOSDependent OS Dependent variable passed during call to
*                        cifXTKitAddDevice
*   \return Handle that is needed for unmapping NULL is a mapping failure    */
/*****************************************************************************/
void* OS_MapUserPointer(void* pvDriverMem, uint32_t ulMemSize, void** ppvMappedMem, void* pvOSDependent)
{
    UNREFERENCED_PARAMETER(ulMemSize);
    UNREFERENCED_PARAMETER(pvOSDependent);
    /* We are running in user mode, so it is not necessary to map anything to user space */
    *ppvMappedMem = pvDriverMem;

    return pvDriverMem;
}

/*****************************************************************************/
/*! This function unmaps a previously mapped user application pointer 
*   \param phMapping      Handle that was returned by OS_MapUserPointer
*   \param pvOSDependent  OS Dependent variable passed during call to
*                         cifXTKitAddDevice
*   \return !=0 on success                                                   */
/*****************************************************************************/
int OS_UnmapUserPointer(void* phMapping, void* pvOSDependent)
{
    UNREFERENCED_PARAMETER(phMapping);
    UNREFERENCED_PARAMETER(pvOSDependent);
    /* We are running in user mode, so it is not necessary to map anything to user space */
    return 1;
}

/*****************************************************************************/
/*! This function enables the interrupts for the device physically
*   \param pvOSDependent OS Dependent Variable passed during call to
*                        cifXTKitAddDevice                                   */
/*****************************************************************************/
void OS_EnableInterrupts(void* pvOSDependent)
{
}

/*****************************************************************************/
/*! This function disables the interrupts for the device physically
*   \param pvOSDependent OS Dependent Variable passed during call to
*                        cifXTKitAddDevice                                   */
/*****************************************************************************/
void OS_DisableInterrupts(void* pvOSDependent)
{
}

#ifdef CIFX_TOOLKIT_TIME
/*****************************************************************************/
/*! Get System time
*   \param ptTime   Pointer to store the time value
*   \return actual time value in seconds sincd 01.01.1970
/*****************************************************************************/
uint32_t OS_Time( uint32_t *ptTime)
{
  if (NULL != ptTime)
    *ptTime = 0;
  
  return 0;
}
#endif

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/
