/*
 * @Author: your name
 * @Date: 2020-08-31 18:07:20
 * @LastEditTime: 2020-09-01 21:19:45
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \bootloader????????\Inc\user_init.h
 */
#ifndef __USER_INIT_H__
#define __USER_INIT_H__

#include "main.h"

// 8M: LL_RCC_RCHF_FREQUENCY_8MHZ
// 16M: LL_RCC_RCHF_FREQUENCY_16MHZ
// 24M: LL_RCC_RCHF_FREQUENCY_24MHZ
#define RCHF_CLOCK  LL_RCC_RCHF_FREQUENCY_8MHZ

extern uint32_t systemClock;

void user_init(void);

#endif
