#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "sys.h"

extern int8 KeyCode;
extern uint8 IO_KeyState;
extern uint8 KEY_MAP[17];

void IO_KeyScan(void);      // 4-4�������ɨ��

#endif
