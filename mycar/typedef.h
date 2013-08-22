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

#define DEFINE_CODE_VAR(type,name)	\
	type code name 
	
#define DECLARE_CODE_VAR(type,name)	\
	extern type code name 

#endif
