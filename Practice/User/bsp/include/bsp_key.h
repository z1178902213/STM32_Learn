#ifndef _BSP_KEY_H
#define _BSP_KEY_H
#include "stm32f4xx.h"

#define KEY_ON 1
#define KEY_OFF 0

void init_key(void);
FlagStatus get_key_status(void);

#endif //_BSP_KEY_H

