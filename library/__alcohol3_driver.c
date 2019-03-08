/*
    __alcohol3_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__alcohol3_driver.h"
#include "__alcohol3_hal.c"

/* ------------------------------------------------------------------- MACROS */

const uint8_t _ALCOHOL3_DEVICE_SLAVE_ADDRESS = 0x4D;

/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __ALCOHOL3_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static float _ppm2mgL(uint16_t ppm);
static float _etanolInCO(uint16_t co);
static uint16_t _map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

/* Convert ppm to mg/L
 *
 * Table:  mg/l | air ppm
 *         1.82 | 1000
 *         0.91 | 500
 *         0.18 | 100
 *         0.09 | 50
 */
static float _ppm2mgL(uint16_t ppm)
{
    float mgL;
    
    mgL = (1.82 * ppm) / 1000.0;
    return mgL;
}

/* Etanol in CO data
 *
 * Table:  CO [ppm] | Equivalent C2H5OH
            0       |    0
           10       |    1
           50       |    6
          100       |    18
          500       |    274
 */
static float _etanolInCO(uint16_t co)
{
    float etanol;

    if (co == 0)
    {
        etanol = 0;
    }
    else if (co <= 10)
    {
        etanol = co / 10.0;
    }
    else if (co > 10 && co <= 50)
    {
        etanol = (float)(6 / 50.0) * co;
    }
    else if (co > 50 && co <= 100)
    {
        etanol = (0.18 * co);
    }
    else if (co > 100)
    {
        etanol = (float)(274 / 500.0) * co;
    }
    return etanol;
}

static long _map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __ALCOHOL3_DRV_SPI__

void alcohol3_spiDriverInit(T_ALCOHOL3_P gpioObj, T_ALCOHOL3_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __ALCOHOL3_DRV_I2C__

void alcohol3_i2cDriverInit(T_ALCOHOL3_P gpioObj, T_ALCOHOL3_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif
#ifdef   __ALCOHOL3_DRV_UART__

void alcohol3_uartDriverInit(T_ALCOHOL3_P gpioObj, T_ALCOHOL3_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

uint16_t alcohol3_getADCdata()
{
    uint8_t writeData;
    uint8_t readData[ 2 ];
    uint16_t ADC_value;
    
    writeData = 0x00;
    
    hal_i2cStart();
    hal_i2cWrite(_slaveAddress, &writeData, 1, END_MODE_RESTART);
    hal_i2cRead(_slaveAddress, readData, 2, END_MODE_STOP);
    
    ADC_value = readData[ 0 ];
    ADC_value <<= 8;
    ADC_value |= readData[ 1 ];
    
    ADC_value = ADC_value & 0x0FFF;
    
    return ADC_value;
}

uint16_t alcohol3_getCOinPPM()
{
    uint16_t CO_ppm;
    uint16_t adcData;
    
    adcData = alcohol3_getADCdata();
    CO_ppm = _map(adcData, 0, 4096, 1, 1000);
    
    return CO_ppm;
}

float alcohol3_getCOinMGL()
{
    uint16_t CO_ppm;
    float CO_mgL;
    
    CO_ppm = alcohol3_getCOinPPM();
    CO_mgL = _ppm2mgL(CO_ppm);
    
    return CO_mgL;
}

uint16_t alcohol3_ethanolInPPM()
{
    uint16_t Ethanol_ppm;
    uint16_t CO_ppm;

    CO_ppm = alcohol3_getCOinPPM();
    Ethanol_ppm = _etanolInCO(CO_ppm);
    
    return Ethanol_ppm;
}

float alcohol3_getPercentageBAC()
{
    float Alcohol_mgL;
    uint16_t Ethanol_ppm;
    uint16_t readData;

    readData = alcohol3_getADCdata();
    Ethanol_ppm = _etanolInCO(readData);
    Alcohol_mgL = _ppm2mgL(Ethanol_ppm);

    return Alcohol_mgL;
}

/* -------------------------------------------------------------------------- */
/*
  __alcohol3_driver.c

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