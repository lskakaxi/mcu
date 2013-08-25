#ifndef _DELAY_H
#define _DELAY_H
#include "mycar.h"

/* this delay define is for 89s52 12MHz
 * change them when the target different
 */
#define delay3us(); {NOP();NOP();NOP();}
#define delay5us(); {NOP();NOP();NOP();NOP();NOP();}
#define delay10us(); {delay5us();delay5us();}

#endif
