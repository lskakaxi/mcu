#ifndef _TYPEDEF_H
#define _TYPEDEF_H

typedef char s8;
typedef short s16;
typedef long s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef u8 bool;

#define true 1
#define false 0
#define HIGH 1
#define LOW 0

#ifdef _KEIL_C_
/* for Keil C */
#define DEFINE_CODE_VAR(type,name)	\
	type code name 
#define DECLARE_CODE_VAR(type,name)	\
	extern type code name 

#define DEFINE_BIT_VAR(name)	\
	 bit name 
#define DECLARE_BIT_VAR(name)	\
	extern bit name 

#include <intrins.h>
#define NOP() _nop_()
#else
/* for sdcc */
#define DEFINE_CODE_VAR(type,name)	\
	__code type name 
#define DECLARE_CODE_VAR(type,name)	\
	extern __code type name 

#define DEFINE_BIT_VAR(name)	\
	 __bit name 
#define DECLARE_BIT_VAR(name)	\
	extern __bit name 

#define NOP() __asm nop __endasm
#endif

#endif
