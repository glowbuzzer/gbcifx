/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: cifXToolkit.h 13792 2020-11-18 08:44:49Z AMinor $:

  Description:
    cifX toolkit function declaration.

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2018-10-10  - Updated header and definitions to new Hilscher defines
                - Added chip type definitions for netX90/netX4000 (eCHIP_TYPE_NETX90 / eCHIP_TYPE_NETX4000)
                - Derived from cifX Toolkit V1.6.0.0

**************************************************************************************/

/*****************************************************************************/
/*!  \file                                                                   *
*    cifX toolkit function declaration                                       */
/*****************************************************************************/

#ifndef CIFX_TOOLKIT__H
#define CIFX_TOOLKIT__H

#ifdef __cplusplus
extern "C"
{
#endif

#include "cifXHWFunctions.h"
#include "Hil_FileHeaderV3.h"


#ifndef min
  #define min(a,b)  ((a > b)? b : a)
#endif

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_STRUCTURE Toolkit Structure Definitions
*    \{                                                                      */
/*****************************************************************************/

#define TOOLKIT_VERSION       "cifX Toolkit 2.6.0.0"

typedef struct DEVICE_CHANNEL_DATAtag
{
  int       fModuleLoaded;                          /* Module loaded */
  int       fCNFLoaded;                             /* CNF file loaded */
  char      szFileName[16];                         /* Module short file name 8.3 */
  uint32_t  ulFileSize;
} DEVICE_CHANNEL_DATA;

typedef struct DEVICE_CHANNEL_CONFIGtag
{
  int                 fFWLoaded;                /* FW file loaded */
  DEVICE_CHANNEL_DATA atChannelData[CIFX_MAX_NUMBER_OF_CHANNELS];
} DEVICE_CHANNEL_CONFIG, *PDEVICE_CHANNEL_CONFIG;

#define CIFXTKIT_DOWNLOAD_NONE      0x00 /*!< Set when file download was skipped. Only valid if CIFX_NO_ERROR is returned */
#define CIFXTKIT_DOWNLOAD_FIRMWARE  0x01 /*!< Successfully downloaded a firmware */
#define CIFXTKIT_DOWNLOAD_MODULE    0x02 /*!< Successfully downloaded a firmware */
#define CIFXTKIT_DOWNLOAD_EXECUTED  0x80 /*!< Download was executed */

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

/* Toolkit Global Functions */
int32_t cifXTKitInit         (void);
void    cifXTKitDeinit       (void);
int32_t cifXTKitAddDevice    (PDEVICEINSTANCE ptDevInstance);
int32_t cifXTKitRemoveDevice (char* szBoard, int fForceRemove);

void cifXTKitDisableHWInterrupt(PDEVICEINSTANCE ptDevInstance);
void cifXTKitEnableHWInterrupt(PDEVICEINSTANCE ptDevInstance);

void cifXTKitCyclicTimer  (void);

/* Toolkit Internal Functions */
int DEV_RemoveChannelFiles    (PCHANNELINSTANCE ptChannel, uint32_t ulChannel,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                               void*                  pvUser,
                               char*                  szExceptFile);

int  DEV_RemoveFWFiles        (PCHANNELINSTANCE   ptChannel,    uint32_t ulChannel,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                               void*                  pvUser);

int32_t DEV_DeleteFile        (void* pvChannel, uint32_t ulChannelNumber, char* pszFileName,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                               void*                  pvUser);

int32_t DEV_CheckForDownload  (void* pvChannel,   uint32_t ulChannelNumber, int*      pfDownload,
                               char* pszFileName, void*    pvFileData,      uint32_t  ulFileSize,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                               void*                  pvUser);


int  DEV_IsFWFile             (char* pszFileName);
int  DEV_IsNXFFile            (char* pszFileName);
int  DEV_IsNXOFile            (char* pszFileName);

int32_t DEV_GetFWTransferTypeFromFileName (char* pszFileName, uint32_t* pulTransperType);

int32_t DEV_ProcessFWDownload (PDEVICEINSTANCE        ptDevInstance,
                               uint32_t               ulChannel,
                               char*                  pszFullFileName,
                               char*                  pszFileName,
                               uint32_t               ulFileLength,
                               uint8_t*               pbBuffer,
                               uint8_t*               pbLoadState,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_PROGRESS_CALLBACK  pfnCallback,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPktCallback,
                               void*                  pvUser);

int32_t DEV_DownloadFile      (void*                  pvChannel,
                               uint32_t               ulChannel,
                               uint32_t               ulMailboxSize,
                               uint32_t               ulTransferType,
                               char*                  szFileName,
                               uint32_t               ulFileLength,
                               void*                  pvData,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_PROGRESS_CALLBACK  pfnCallback,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                               void*                  pvUser);

int32_t DEV_UploadFile        (void*                  pvChannel,
                               uint32_t               ulChannel,
                               uint32_t               ulMailboxSize,
                               uint32_t               ulTransfertype,
                               char*                  szFilename,
                               uint32_t*              pulFileLength,
                               void*                  pvData,
                               PFN_TRANSFER_PACKET    pfnTransferPacket,
                               PFN_PROGRESS_CALLBACK  pfnCallback,
                               PFN_RECV_PKT_CALLBACK  pfnRecvPacket,
                               void*                  pvUser);

/*****************************************************************************/
/*! \addtogroup CIFX_TK_STRUCTURE Toolkit Structure Definitions
*   \{                                                                       */
/*****************************************************************************/

/*****************************************************************************/
/*! Global driver information structure used internally in the toolkit       */
/*****************************************************************************/
typedef struct TKIT_DRIVER_INFORMATIONtag
{
  uint32_t ulOpenCount;  /*!< Number of xDriverOpen calls */
  int      fInitialized; /*!< !=1 if the toolkit was initialized successfully */

} TKIT_DRIVER_INFORMATION;


/*****************************************************************************/
/*! Structure passed to USER implemented function, for reading device        *
* specific configuration options                                             */
/*****************************************************************************/
typedef struct CIFX_DEVICE_INFORMATIONtag
{
  uint32_t   ulDeviceNumber;   /*!< Device number of the cifX card */
  uint32_t   ulSerialNumber;   /*!< Serial number                  */
  uint32_t   ulChannel;        /*!< Channel number (0..6)          */
  PDEVICEINSTANCE ptDeviceInstance; /*!< Pointer to device instance     */

} CIFX_DEVICE_INFORMATION, *PCIFX_DEVICE_INFORMATION;

/*****************************************************************************/
/*! Structure passed to USER implemented function, for getting device        *
*   specific configuration files                                             */
/*****************************************************************************/
typedef struct CIFX_FILE_INFORMATIONtag
{
  char  szShortFileName[16];                        /*!< Short filename (8.3) of the file       */
  char  szFullFileName[CIFX_MAX_FILE_NAME_LENGTH];  /*!< Full filename (including path) to file */
} CIFX_FILE_INFORMATION, *PCIFX_FILE_INFORMATION;

/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/

/******************************************************************************
* Functions to be implemented by USER                                         *
******************************************************************************/

void      USER_GetBootloaderFile        (PDEVICEINSTANCE ptDevInstance, PCIFX_FILE_INFORMATION ptFileInfo);
int       USER_GetOSFile                (PCIFX_DEVICE_INFORMATION ptDevInfo, PCIFX_FILE_INFORMATION ptFileInfo);

uint32_t  USER_GetFirmwareFileCount     (PCIFX_DEVICE_INFORMATION ptDevInfo);
int       USER_GetFirmwareFile          (PCIFX_DEVICE_INFORMATION ptDevInfo, uint32_t ulIdx, PCIFX_FILE_INFORMATION ptFileInfo);
uint32_t  USER_GetConfigurationFileCount(PCIFX_DEVICE_INFORMATION ptDevInfo);
int       USER_GetConfigurationFile     (PCIFX_DEVICE_INFORMATION ptDevInfo, uint32_t ulIdx, PCIFX_FILE_INFORMATION ptFileInfo);

int       USER_GetWarmstartParameters   (PCIFX_DEVICE_INFORMATION ptDevInfo, CIFX_PACKET* ptPacket);
void      USER_GetAliasName             (PCIFX_DEVICE_INFORMATION ptDevInfo, uint32_t ulMaxLen, char* szAlias);
int       USER_GetInterruptEnable       (PCIFX_DEVICE_INFORMATION ptDevInfo);
int       USER_GetDMAMode               (PCIFX_DEVICE_INFORMATION ptDevInfo);

void      USER_Trace                    (PDEVICEINSTANCE ptDevInstance, uint32_t ulTraceLevel, const char* szFormat, ...);

extern uint32_t g_ulTraceLevel;


#ifdef __cplusplus
}
#endif

#endif /* CIFX_TOOLKIT__H */
