![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Alcohol3 Click

- **CIC Prefix**  : ALCOHOL3
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : nov 2018.

---

### Software Support

We provide a library for the Alcohol3 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2672/alcohol-3-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library initializes and defines the I2C bus driver and drivers that offer a choice for reads adc data from I2C.
The library includes function for reads CO data in the AIR (in ppm and mg/L), 
function for reads Ethanol data in ppm and reads the percentage of alcohol in the blood (BAC).

Key functions :

- ``` float alcohol3_getPercentageBAC() ``` - Function for read percentage of alcohol in the blood (BAC)
- ``` uint16_t alcohol3_ethanolInPPM() ``` - Function for read Ethanol (C2H5OH) data in ppm
- ``` uint16_t alcohol3_getCOinPPM() ``` - Function for read CO (Carbon monoxide) data in ppm

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module
- Application Initialization - Initialization driver init
- Application Task - (code snippet) - Reads percentage of alcohol in the blood (BAC) and this data logs to USBUART every 1 sec.


```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2672/alcohol-3-click) page.

Other mikroE Libraries used in the example:

- I2C
- Conversions
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
