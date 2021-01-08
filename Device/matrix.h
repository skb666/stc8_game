#ifndef _MATRIX_H
#define _MATRIX_H

#include "sys.h"

#define MATRIX_ROW      P6

void matrix_init(void);     // led阵列初始化
void matrix_display(uint8 index, uint8 *Str_begin, uint8 *Str_end);     // 单屏静态显示
void matrix_run(uint8 *Str, uint8 size_n, uint8 begin);                 // 动态显示

#endif