#line 1 "D:/Clicks_git/A/Alcohol_3_Click/SW/example/c/ARM/STM/Click_Alcohol3_STM.c"
#line 1 "d:/clicks_git/a/alcohol_3_click/sw/example/c/arm/stm/click_alcohol3_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "d:/clicks_git/a/alcohol_3_click/sw/example/c/arm/stm/click_alcohol3_config.h"
#line 1 "d:/clicks_git/a/alcohol_3_click/sw/example/c/arm/stm/click_alcohol3_types.h"
#line 19 "d:/clicks_git/a/alcohol_3_click/sw/example/c/arm/stm/click_alcohol3_config.h"
const uint32_t _ALCOHOL3_I2C_CFG[ 1 ] =
{
 100000
};
#line 1 "d:/clicks_git/a/alcohol_3_click/sw/library/__alcohol3_driver.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 58 "d:/clicks_git/a/alcohol_3_click/sw/library/__alcohol3_driver.h"
extern const uint8_t _ALCOHOL3_DEVICE_SLAVE_ADDRESS ;
#line 71 "d:/clicks_git/a/alcohol_3_click/sw/library/__alcohol3_driver.h"
void alcohol3_i2cDriverInit( const uint8_t*  gpioObj,  const uint8_t*  i2cObj, uint8_t slave);
#line 78 "d:/clicks_git/a/alcohol_3_click/sw/library/__alcohol3_driver.h"
void alcohol3_gpioDriverInit( const uint8_t*  gpioObj);



uint16_t alcohol3_getADCdata();

uint16_t alcohol3_getCOinPPM();

float alcohol3_getCOinMGL();

uint16_t alcohol3_ethanolInPPM();

float alcohol3_getPercentageBAC();
#line 29 "D:/Clicks_git/A/Alcohol_3_Click/SW/example/c/ARM/STM/Click_Alcohol3_STM.c"
void systemInit()
{
 mikrobus_i2cInit( _MIKROBUS1, &_ALCOHOL3_I2C_CFG[0] );
 mikrobus_logInit( _LOG_USBUART_A, 9600 );
 mikrobus_logWrite("--- System Init ---", _LOG_LINE);
 Delay_ms( 100 );
}

void applicationInit()
{
 alcohol3_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, _ALCOHOL3_DEVICE_SLAVE_ADDRESS );
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
