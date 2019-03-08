_systemInit:
;Click_Alcohol3_STM.c,29 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Alcohol3_STM.c,31 :: 		mikrobus_i2cInit( _MIKROBUS1, &_ALCOHOL3_I2C_CFG[0] );
MOVW	R0, #lo_addr(__ALCOHOL3_I2C_CFG+0)
MOVT	R0, #hi_addr(__ALCOHOL3_I2C_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_i2cInit+0
;Click_Alcohol3_STM.c,32 :: 		mikrobus_logInit( _LOG_USBUART_A, 9600 );
MOVW	R1, #9600
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_Alcohol3_STM.c,33 :: 		mikrobus_logWrite("--- System Init ---", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr1_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_Alcohol3_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,34 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_systemInit0:
SUBS	R7, R7, #1
BNE	L_systemInit0
NOP
NOP
NOP
;Click_Alcohol3_STM.c,35 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_Alcohol3_STM.c,37 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_Alcohol3_STM.c,39 :: 		alcohol3_i2cDriverInit( (T_ALCOHOL3_P)&_MIKROBUS1_GPIO, (T_ALCOHOL3_P)&_MIKROBUS1_I2C, _ALCOHOL3_DEVICE_SLAVE_ADDRESS );
MOVS	R2, __ALCOHOL3_DEVICE_SLAVE_ADDRESS
MOVW	R1, #lo_addr(__MIKROBUS1_I2C+0)
MOVT	R1, #hi_addr(__MIKROBUS1_I2C+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_alcohol3_i2cDriverInit+0
;Click_Alcohol3_STM.c,40 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_Alcohol3_STM.c,42 :: 		void applicationTask()
SUB	SP, SP, #56
STR	LR, [SP, #0]
;Click_Alcohol3_STM.c,48 :: 		mikrobus_logWrite(" --- Alcohol diagnostics ----", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr2_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_Alcohol3_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,50 :: 		CO_ppm = alcohol3_getCOinPPM();
BL	_alcohol3_getCOinPPM+0
;Click_Alcohol3_STM.c,51 :: 		WordToStr(CO_ppm, demoText);
ADD	R1, SP, #4
BL	_WordToStr+0
;Click_Alcohol3_STM.c,52 :: 		mikrobus_logWrite(" CO in ppm      | ", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr3_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr3_Click_Alcohol3_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,53 :: 		mikrobus_logWrite(demoText, _LOG_LINE);
ADD	R0, SP, #4
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,55 :: 		pBAC = alcohol3_getPercentageBAC() * 1000;
BL	_alcohol3_getPercentageBAC+0
MOVW	R2, #0
MOVT	R2, #17530
BL	__Mul_FP+0
BL	__FloatToUnsignedIntegral+0
UXTH	R0, R0
; pBAC start address is: 24 (R6)
UXTH	R6, R0
;Click_Alcohol3_STM.c,56 :: 		WordToStr(pBAC, demoText);
ADD	R1, SP, #4
BL	_WordToStr+0
;Click_Alcohol3_STM.c,57 :: 		if( 10 > pBAC && pBAC < 100 )
CMP	R6, #10
IT	CS
BCS	L__applicationTask19
CMP	R6, #100
IT	CS
BCS	L__applicationTask18
; pBAC end address is: 24 (R6)
L__applicationTask17:
;Click_Alcohol3_STM.c,59 :: 		mikrobus_logWrite(" BAC            | 0.00", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr4_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr4_Click_Alcohol3_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,60 :: 		LTrim(demoText);
ADD	R0, SP, #4
BL	_Ltrim+0
;Click_Alcohol3_STM.c,61 :: 		mikrobus_logWrite(demoText, _LOG_LINE);
ADD	R0, SP, #4
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,62 :: 		}
IT	AL
BAL	L_applicationTask5
;Click_Alcohol3_STM.c,57 :: 		if( 10 > pBAC && pBAC < 100 )
L__applicationTask19:
; pBAC start address is: 24 (R6)
L__applicationTask18:
;Click_Alcohol3_STM.c,63 :: 		else if(100 <= pBAC && 1000 > pBAC)
CMP	R6, #100
IT	CC
BCC	L__applicationTask21
CMP	R6, #1000
IT	CS
BCS	L__applicationTask20
; pBAC end address is: 24 (R6)
L__applicationTask16:
;Click_Alcohol3_STM.c,65 :: 		mikrobus_logWrite(" BAC            | 0.0", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr5_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr5_Click_Alcohol3_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,66 :: 		LTrim(demoText);
ADD	R0, SP, #4
BL	_Ltrim+0
;Click_Alcohol3_STM.c,67 :: 		mikrobus_logWrite(demoText, _LOG_LINE);
ADD	R0, SP, #4
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,68 :: 		}
IT	AL
BAL	L_applicationTask9
;Click_Alcohol3_STM.c,63 :: 		else if(100 <= pBAC && 1000 > pBAC)
L__applicationTask21:
; pBAC start address is: 24 (R6)
L__applicationTask20:
;Click_Alcohol3_STM.c,69 :: 		else if ( pBAC >= 1000)
CMP	R6, #1000
IT	CC
BCC	L_applicationTask10
; pBAC end address is: 24 (R6)
;Click_Alcohol3_STM.c,71 :: 		mikrobus_logWrite(" BAC            | 0.", _LOG_TEXT);
MOVW	R0, #lo_addr(?lstr6_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr6_Click_Alcohol3_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,72 :: 		LTrim(demoText);
ADD	R0, SP, #4
BL	_Ltrim+0
;Click_Alcohol3_STM.c,73 :: 		mikrobus_logWrite(demoText, _LOG_LINE);
ADD	R0, SP, #4
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,74 :: 		}
IT	AL
BAL	L_applicationTask11
L_applicationTask10:
;Click_Alcohol3_STM.c,77 :: 		mikrobus_logWrite(" BAC            | 0.0000", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr7_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr7_Click_Alcohol3_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,78 :: 		}
L_applicationTask11:
L_applicationTask9:
L_applicationTask5:
;Click_Alcohol3_STM.c,79 :: 		mikrobus_logWrite(" ----------------------------", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr8_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr8_Click_Alcohol3_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,80 :: 		mikrobus_logWrite( " " , _LOG_LINE);
MOVW	R0, #lo_addr(?lstr9_Click_Alcohol3_STM+0)
MOVT	R0, #hi_addr(?lstr9_Click_Alcohol3_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_Alcohol3_STM.c,81 :: 		Delay_ms( 1000 );
MOVW	R7, #6911
MOVT	R7, #183
NOP
NOP
L_applicationTask12:
SUBS	R7, R7, #1
BNE	L_applicationTask12
NOP
NOP
NOP
;Click_Alcohol3_STM.c,82 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #56
BX	LR
; end of _applicationTask
_main:
;Click_Alcohol3_STM.c,84 :: 		void main()
;Click_Alcohol3_STM.c,86 :: 		systemInit();
BL	_systemInit+0
;Click_Alcohol3_STM.c,87 :: 		applicationInit();
BL	_applicationInit+0
;Click_Alcohol3_STM.c,89 :: 		while (1)
L_main14:
;Click_Alcohol3_STM.c,91 :: 		applicationTask();
BL	_applicationTask+0
;Click_Alcohol3_STM.c,92 :: 		}
IT	AL
BAL	L_main14
;Click_Alcohol3_STM.c,93 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
