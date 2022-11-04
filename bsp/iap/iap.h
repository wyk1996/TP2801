/*
 * @Author: your name
 * @Date: 2020-08-31 18:49:02
 * @LastEditTime: 2020-09-01 21:18:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \bootloaderÒýµ¼³ÌÐò\Src\iap.c
 */

#ifndef _IAP_H_
#define _IAP_H_

#include "main.h"

void iap_load_app(uint32_t app_addr);

int iap_recv_proc(uint8_t *data, uint16_t *length,uint32_t timeout);

void iap_ack(uint8_t *p_msg, uint16_t msg_len, uint16_t data_len);

void iap_write_flash(uint8_t *msg, uint16_t lenght);

void iap_done(void);

#endif
