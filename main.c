/**
 ******************************************************************************
 * @file           :  main
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 Glowbuzzer.
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 */

#include <stdio.h>
#include "cifXToolkit.h"
#include "rcX_Public.h"
#include "app.h"
#include "cifXErrors.h"             /** Include cifX driver API error definition */
#include "cifXUser.h"               /** Include cifX driver API definition       */
#include "SystemPackets.h"
#include "SerialDPMInterface.h"

/* Toolkit device instance */
static DEVICEINSTANCE s_tDevInstance = {.pvOSDependent = &s_tDevInstance,
        .ulDPMSize = 0x10000,
        .szName = "cifX0",
        .eDeviceType = eCIFX_DEVICE_AUTODETECT,
        .fPCICard = 0,
        .fIrqEnabled = 0,
        };

#define COM_CHANNEL  0



APP_DATA_T tAppData = {0};

//
///*****************************************************************************/
///*! Displays a hex dump on the debug console (16 bytes per line)
//*   \param pbData     pointer to dump data
//*   \param ulDataLen  length of data dump                                    */
///*****************************************************************************/
//void DumpData(unsigned char* pbData, unsigned long ulDataLen)
//{
//    unsigned long ulIdx;
//
//    if(CIFX_MAX_DATA_SIZE < ulDataLen)
//    {
//        ulDataLen = CIFX_MAX_DATA_SIZE;
//    }
//
//    for(ulIdx = 0; ulIdx < ulDataLen; ++ulIdx)
//    {
//        if(0 == (ulIdx % 16))
//            printf("\r\n");
//
//        printf("%02X ", pbData[ulIdx]);
//    }
//    printf("\r\n");
//
//} /** DumpData */
//
//
///*****************************************************************************/
///*! Dumps a rcX packet to debug console
//*   \param ptPacket  Packet to be dumped                                     */
///*****************************************************************************/
//void DumpPacket(CIFX_PACKET* ptPacket)
//{
//    printf("Dest   : 0x%08X      ID   : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulDest, (unsigned int) ptPacket->tHeader.ulId);
//    printf("Src    : 0x%08X      Sta  : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulSrc, (unsigned int) ptPacket->tHeader.ulState);
//    printf("DestID : 0x%08X      Cmd  : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulDestId, (unsigned int) ptPacket->tHeader.ulCmd);
//    printf("SrcID  : 0x%08X      Ext  : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulSrcId, (unsigned int) ptPacket->tHeader.ulExt);
//    printf("Len    : 0x%08X      Rout : 0x%08X\r\n", (unsigned int) ptPacket->tHeader.ulLen, (unsigned int) ptPacket->tHeader.ulRout);
//
//    if(ptPacket->tHeader.ulLen) {
//        printf("Data:");
//
//        /** Displays a hex dump on the debug console (16 bytes per line) */
//        DumpData(ptPacket->abData, ptPacket->tHeader.ulLen);
//    }
//
//} /** DumpPacket */




void IODemo(PCHANNELINSTANCE hChannel){
int32_t lRet = 0;

//tAppData.tOutputData.abApp_Outputdata[0]=7;

    if(CIFX_NO_ERROR != (lRet = xChannelIORead(hChannel, 0, 0, sizeof(APP_OUTPUT_DATA_T), tAppData.tOutputData.abApp_Outputdata, 10)))
    {
        if(CIFX_DEV_NO_COM_FLAG != lRet)
        {
            printf("Error reading output data values received from network!\r\n");
        }
    } else
    {
        printf("Read Data:");
        DumpData(tAppData.tOutputData.abApp_Outputdata, sizeof(APP_OUTPUT_DATA_T));

        /* copy inputs to outputs, as most simplest application*/
        memcpy(tAppData.tInputData.abApp_Inputdata,tAppData.tOutputData.abApp_Outputdata, sizeof(APP_OUTPUT_DATA_T));

        /* write data to network */
        if(CIFX_NO_ERROR != (lRet = xChannelIOWrite(hChannel, 0, 0, sizeof(APP_INPUT_DATA_T), tAppData.tInputData.abApp_Inputdata, 10)))
        {
            if(CIFX_DEV_NO_COM_FLAG != lRet)
            {

                printf("Error writing input data values that shall be transferred to the network!\r\n");
            }
        } else
        {
//#ifdef DEBUG
            printf("Write Data:");
              DumpData(tAppData.tInputData.abApp_Inputdata, sizeof(APP_INPUT_DATA_T));
//#endif
        }
    }



}


int main(void) {
    printf("hello\n");
    int32_t lRet = CIFX_NO_ERROR;

    int32_t lTkRet = CIFX_NO_ERROR;

    if(geteuid() != 0)
    {
        printf("Program did not run as root. Exiting now.\n");
        return(-1);
    }

    /* First of all initialize toolkit */
    lTkRet = cifXTKitInit();
    if (CIFX_NO_ERROR == lTkRet) {
        printf("cifXTKitInit successful\n");
        /* Set trace level of toolkit */
        g_ulTraceLevel = TRACE_LEVEL_ERROR   |
                         TRACE_LEVEL_WARNING |
                         TRACE_LEVEL_INFO    |
                         TRACE_LEVEL_DEBUG;

        int iSerDPMType;
        if (SERDPM_UNKNOWN == (iSerDPMType = SerialDPM_Init(&s_tDevInstance))) {
/* Serial DPM protocol could not be recognized! */
        } else {
/* iSerDPMType contains connected netX chip type */
/* Add the device to the toolkits handled device list */
            lTkRet = cifXTKitAddDevice(&s_tDevInstance);
/* If it succeeded do device tests */
            if (CIFX_NO_ERROR != lTkRet) {
/* Uninitialize Toolkit, this will remove all handled boards from the toolkit and
deallocate the device instance */
                cifXTKitDeinit();
            } else {
/* Start working with cifX API */
                printf("here\n");
                PCHANNELINSTANCE ptChannel = s_tDevInstance.pptCommChannels[COM_CHANNEL];

                lRet = DEV_SetHostState( ptChannel, CIFX_HOST_STATE_READY, 1000);

#define DEMO_CYCLES 1000
                printf("lret [%u]\n", lRet);
                uint32_t ulState = 0;
                /* Switch ON the BUS communication */
                lRet = DEV_BusState( ptChannel, CIFX_BUS_STATE_ON, &ulState, 3000);

                printf("lret [0x%x]\n", lRet);

                /* Start cyclic demo with I/O Data-Transfer and packet data transfer */
                unsigned long ulCycCnt = 0;
//uint32_t ulTriggerCount = 0;
/* Cyclic I/O and packet handling for 'ulCycCnt'times */
                while( ulCycCnt < DEMO_CYCLES)
                {
/* Start and trigger watchdog function, if necessary */
//DEV_TriggerWatchdog(ptChannel, CIFX_WATCHDOG_START, &ulTriggerCount);
/* Handle I/O data transfer */
                    IODemo (ptChannel);
/* Handle rcX packet transfer */
//#ifdef FIELDBUS_INDICATION_HANDLING
//                    Fieldbus_HandleIndications( ptChannel);
//#else
//                    PacketDemo ( ptChannel);
//#endif
                    ulCycCnt++;
                }


            }
        }
    } else {
        printf("cifXTKitInit NOT successful\n");
    }

}