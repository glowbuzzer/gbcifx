/**
 ******************************************************************************
 * @file           :  app
 * @brief          :
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 Glowbuzzer.
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 */
#ifndef GBCIFX_APP_H
#define GBCIFX_APP_H

#include "cifXToolkit.h"

typedef struct APP_INPUT_DATA_Ttag {
    uint8_t abApp_Inputdata[200];
} APP_INPUT_DATA_T;


typedef struct APP_OUTPUT_DATA_Ttag {
    uint8_t abApp_Outputdata[200];
} APP_OUTPUT_DATA_T;

typedef struct APP_DATA_Ttag {
    int fRunning;

    CIFXHANDLE hChannel[1];  /* handle to channel */
    CIFX_PACKET tPkt;       /** Buffer for mailbox packets, dual usage send and receive */
    uint32_t ulSendPktCnt;  /** global send packet counter*/

    APP_INPUT_DATA_T tInputData;
    APP_OUTPUT_DATA_T tOutputData;
} APP_DATA_T;


#endif //GBCIFX_APP_H
