/*
 * @Author: your name
 * @Date: 2020-08-31 18:07:20
 * @LastEditTime: 2020-09-01 15:39:42
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \bootloader��������\Inc\define_all.h
 */
#ifndef	__DEFINEALL_H__
#define __DEFINEALL_H__

//���峣��, ����

//ϵͳʱ��Ĭ��ʹ��RCHF
#define RCHFCLKCFG	8	//8, 16, 24MHz

//define_all.h��RCHFCLKCFG����ϵͳʱ��
#if( RCHFCLKCFG == 8 )//8.0MHz
#define clkmode   1
#define SYSCLKdef RCC_RCHF_CR_FSEL_8MHZ//RCHF����Ƶ��8MHz
#elif( RCHFCLKCFG == 16 )//16.0MHz
#define clkmode   2
#define SYSCLKdef RCC_RCHF_CR_FSEL_16MHZ//RCHF����Ƶ��16MHz
#elif( RCHFCLKCFG == 24 )//24.0MHz
#define clkmode   3
#define SYSCLKdef RCC_RCHF_CR_FSEL_24MHZ//RCHF����Ƶ��24MHz
#endif

#define APP_UPDATE_FLAG                 (1024 * 8)
#define APPLICATION_ADDRESS_OFFSET      (1024 * 10)	//�û�������ʼ��ַ 10K

/* GPIO���ú��������궨�� */
//IO��������� 
//type 0 = ��ͨ 
//type 1 = ����
#define IN_NORMAL	0
#define IN_PULLUP	1

//IO��������� 
//type 0 = ��ͨ 
//type 1 = OD
#define OUT_PUSHPULL	0
#define OUT_OPENDRAIN	1

//IO�������⹦�ܿ� 
//type 0 = ��ͨ 
//type 1 = OD (OD���ܽ��������⹦��֧��)
//type 2 = ��ͨ+���� 
//type 3 = OD+����
#define ALTFUN_NORMAL			0
#define ALTFUN_OPENDRAIN		1
#define ALTFUN_PULLUP			2
#define ALTFUN_OPENDRAIN_PULLUP	3


/*include*/
#include "FM33LC0XX.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "user_init.h"
#include "uart.h"
#include "flash.h"
#include "app.h"

#endif



