/*
Example for Alcohol3 Click

    Date          : nov 2018.
    Author        : Katarina Perendic

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---
Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initialization driver init
- Application Task - (code snippet) - Reads percentage of alcohol in the blood (BAC) and this data logs to USBUART every 1 sec.
*/

#include "Click_Alcohol3_types.h"
#include "Click_Alcohol3_config.h"

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_ALCOHOL3_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    mikrobus_logWrite("--- System Init ---", _LOG_LINE);
    Delay_ms( 100 );
}

void applicationInit()
{
    alcohol3_i2cDriverInit( (T_ALCOHOL3_P)&_MIKROBUS1_GPIO, (T_ALCOHOL3_P)&_MIKROBUS1_I2C, _ALCOHOL3_DEVICE_SLAVE_ADDRESS );
}

void applicationTask()
{
    uint16_t CO_ppm;
    uint16_t pBAC;
    char demoText[ 50 ];

    mikrobus_logWrite(" --- Alcohol diagnostics ----", _LOG_LINE);
        
    CO_ppm = alcohol3_getCOinPPM();
    WordToStr(CO_ppm, demoText);
    mikrobus_logWrite(" CO in ppm      | ", _LOG_TEXT);
    mikrobus_logWrite(demoText, _LOG_LINE);
    
    pBAC = alcohol3_getPercentageBAC() * 1000;
    WordToStr(pBAC, demoText);
    if( 10 > pBAC && pBAC < 100 )
    {
        mikrobus_logWrite(" BAC            | 0.00", _LOG_TEXT);
        LTrim(demoText);
        mikrobus_logWrite(demoText, _LOG_LINE);
    }
    else if(100 <= pBAC && 1000 > pBAC)
    {
        mikrobus_logWrite(" BAC            | 0.0", _LOG_TEXT);
        LTrim(demoText);
        mikrobus_logWrite(demoText, _LOG_LINE);
    }
    else if ( pBAC >= 1000)
    {
        mikrobus_logWrite(" BAC            | 0.", _LOG_TEXT);
        LTrim(demoText);
        mikrobus_logWrite(demoText, _LOG_LINE);
    }
    else
    {
        mikrobus_logWrite(" BAC            | 0.0000", _LOG_LINE);
    }
    mikrobus_logWrite(" ----------------------------", _LOG_LINE);
    mikrobus_logWrite( " " , _LOG_LINE);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}