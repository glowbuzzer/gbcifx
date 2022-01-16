/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: OS_SPICustom.c 12305 2018-08-09 12:54:55Z Robert $:

  Description:
    Implementation of the custom SPI abstration layer

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2018-07-26  Added return value to OS_SpiInit()
    2014-08-27  created

**************************************************************************************/

/*****************************************************************************/
/*! \file OS_SPICustom.c
*    Sample SPI abstraction layer. Implementation must be done
*    according to used target system                                         */
/*****************************************************************************/

#include "OS_Spi.h"

#ifdef CIFX_TOOLKIT_HWIF
//  #error "Implement SPI target system abstraction in this file"
#endif

/*****************************************************************************/
/*!  \addtogroup CIFX_TK_OS_ABSTRACTION Operating System Abstraction
*    \{                                                                      */
/*****************************************************************************/


/*****************************************************************************/
/*! Initialize SPI components
*   \param pvOSDependent OS Dependent parameter
*   \return CIFX_NO_ERROR on success                                         */
/*****************************************************************************/
long OS_SpiInit(void* pvOSDependent)
{
  /* initialize SPI device */

    if (bcm2835_init()){

    } else {
        return CIFX_FUNCTION_FAILED;
    }



    if (bcm2835_spi_begin()) {

        // Set SPI bit order
        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
        // Set SPI data mode BCM2835_SPI_MODE0 = 0, CPOL = 0, CPHA = 0,
        // Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
            // Raspberry 4 due to a higher CPU speed this value is to change to: BCM2835_SPI_CLOCK_DIVIDER_16
            bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);
            UM_INFO(GBCIFX_UM_EN, "GBNETX: bcm2835_spi_setClockDivider set to 16");

        // Disable management of CS pin

        UM_INFO(GBCIFX_UM_EN, "GBNETX: Configuring CS pin");
        bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
        bcm2835_gpio_fsel(RPI_CS_PIN, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(RPI_CS_PIN, HIGH);

        return CIFX_NO_ERROR;


    } else {
        return CIFX_FUNCTION_FAILED;
    }


}

/*****************************************************************************/
/*! Assert chip select
*   \param pvOSDependent OS Dependent parameter to identify card             */
/*****************************************************************************/
void OS_SpiAssert(void* pvOSDependent)
{
  /* assert chip select */
    bcm2835_gpio_write(RPI_CS_PIN, LOW);

}

/*****************************************************************************/
/*! Deassert chip select
*   \param pvOSDependent OS Dependent parameter to identify card             */
/*****************************************************************************/
void OS_SpiDeassert(void* pvOSDependent)
{
  /* deassert chip select */
    bcm2835_gpio_write(RPI_CS_PIN, HIGH);
}

/*****************************************************************************/
/*! Lock the SPI bus
*   \param pvOSDependent OS Dependent parameter                              */
/*****************************************************************************/
void OS_SpiLock(void* pvOSDependent)
{
  /* lock access to SPI device */
}

/*****************************************************************************/
/*! Unlock the SPI bus
*   \param pvOSDependent OS Dependent parameter                              */
/*****************************************************************************/
void OS_SpiUnlock(void* pvOSDependent)
{
  /* unlock access to SPI device */
}

/*****************************************************************************/
/*! Transfer byte stream via SPI
*   \param pvOSDependent OS Dependent parameter to identify card
*   \param pbSend        Send buffer (NULL for polling)
*   \param pbRecv        Receive buffer (NULL if discard)
*   \param ulLen         Length of SPI transfer                              */
/*****************************************************************************/
void OS_SpiTransfer(void* pvOSDependent, uint8_t* pbSend, uint8_t* pbRecv, uint32_t ulLen)
{

    if (pbRecv==NULL){
        //transmit onlu
        uint8_t *dummy_buffer_r = calloc(ulLen, sizeof(uint8_t));

        bcm2835_spi_transfernb( pbSend,dummy_buffer_r, (uint32_t) ulLen);

        free(dummy_buffer_r);
    } else if (pbSend==NULL){
        //receive only
        uint8_t *dummy_buffer_t = calloc(ulLen, sizeof(uint8_t));

        bcm2835_spi_transfernb( dummy_buffer_t,  pbRecv, (uint32_t) ulLen);
        free(dummy_buffer_t);

    } else {
        // transmit and receive
        bcm2835_spi_transfernb(pbSend, pbRecv, (uint32_t) ulLen);

    }


}
/*****************************************************************************/
/*! \}                                                                       */
/*****************************************************************************/
