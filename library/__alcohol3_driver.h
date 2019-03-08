/*
    __alcohol3_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __alcohol3_driver.h
@brief    Alcohol3 Driver
@mainpage Alcohol3 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   ALCOHOL3
@brief      Alcohol3 Click Driver
@{

| Global Library Prefix | **ALCOHOL3** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **nov 2018.**      |
| Developer             | **Katarina Perendic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _ALCOHOL3_H_
#define _ALCOHOL3_H_

/** 
 * @macro T_ALCOHOL3_P
 * @brief Driver Abstract type 
 */
#define T_ALCOHOL3_P    const uint8_t*

/** @defgroup ALCOHOL3_COMPILE Compilation Config */              /** @{ */

//  #define   __ALCOHOL3_DRV_SPI__                            /**<     @macro __ALCOHOL3_DRV_SPI__  @brief SPI driver selector */
   #define   __ALCOHOL3_DRV_I2C__                            /**<     @macro __ALCOHOL3_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __ALCOHOL3_DRV_UART__                           /**<     @macro __ALCOHOL3_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup ALCOHOL3_VAR Variables */                           /** @{ */


extern const uint8_t _ALCOHOL3_DEVICE_SLAVE_ADDRESS ;

                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup ALCOHOL3_INIT Driver Initialization */              /** @{ */

#ifdef   __ALCOHOL3_DRV_SPI__
void alcohol3_spiDriverInit(T_ALCOHOL3_P gpioObj, T_ALCOHOL3_P spiObj);
#endif
#ifdef   __ALCOHOL3_DRV_I2C__
void alcohol3_i2cDriverInit(T_ALCOHOL3_P gpioObj, T_ALCOHOL3_P i2cObj, uint8_t slave);
#endif
#ifdef   __ALCOHOL3_DRV_UART__
void alcohol3_uartDriverInit(T_ALCOHOL3_P gpioObj, T_ALCOHOL3_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void alcohol3_gpioDriverInit(T_ALCOHOL3_P gpioObj);
                                                                       /** @} */
/** @defgroup ALCOHOL3_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Function for read ADC data
 *
 * @return 12bit ADC value
 */
uint16_t alcohol3_getADCdata();

/**
 * @brief Function for read CO (Carbon monoxide) data in ppm
 *
 * @return CO (Carbon monoxide) data in ppm (1 ppm - 1000 ppm)
 */
uint16_t alcohol3_getCOinPPM();

/**
 * @brief Function for read CO (Carbon monoxide) data in mg/L
 *
 * @return CO (Carbon monoxide) data in mg/L
 */
float alcohol3_getCOinMGL();

/**
 * @brief Function for read Ethanol (C2H5OH) data in ppm
 *
 * @return Ethanol (C2H5OH) data in ppm (1 ppm - 500 ppm)
 */
uint16_t alcohol3_ethanolInPPM();

/**
 * @brief Function for read percentage of alcohol in the blood (BAC)
 *
 * @return percentage of alcohol in the blood (BAC)
 */
float alcohol3_getPercentageBAC();





                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Alcohol3_STM.c
    @example Click_Alcohol3_TIVA.c
    @example Click_Alcohol3_CEC.c
    @example Click_Alcohol3_KINETIS.c
    @example Click_Alcohol3_MSP.c
    @example Click_Alcohol3_PIC.c
    @example Click_Alcohol3_PIC32.c
    @example Click_Alcohol3_DSPIC.c
    @example Click_Alcohol3_AVR.c
    @example Click_Alcohol3_FT90x.c
    @example Click_Alcohol3_STM.mbas
    @example Click_Alcohol3_TIVA.mbas
    @example Click_Alcohol3_CEC.mbas
    @example Click_Alcohol3_KINETIS.mbas
    @example Click_Alcohol3_MSP.mbas
    @example Click_Alcohol3_PIC.mbas
    @example Click_Alcohol3_PIC32.mbas
    @example Click_Alcohol3_DSPIC.mbas
    @example Click_Alcohol3_AVR.mbas
    @example Click_Alcohol3_FT90x.mbas
    @example Click_Alcohol3_STM.mpas
    @example Click_Alcohol3_TIVA.mpas
    @example Click_Alcohol3_CEC.mpas
    @example Click_Alcohol3_KINETIS.mpas
    @example Click_Alcohol3_MSP.mpas
    @example Click_Alcohol3_PIC.mpas
    @example Click_Alcohol3_PIC32.mpas
    @example Click_Alcohol3_DSPIC.mpas
    @example Click_Alcohol3_AVR.mpas
    @example Click_Alcohol3_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __alcohol3_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */