#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "app.h"

#define RCHF_CLOCK  LL_RCC_RCHF_FREQUENCY_8MHZ //8m

// #define RCHF_CLOCK  LL_RCC_RCHF_FREQUENCY_16MHZ //16m
// #define RCHF_CLOCK  LL_RCC_RCHF_FREQUENCY_24MHZ //24m


extern uint32_t systemClock;

void User_Systick_Init(void);

#endif

