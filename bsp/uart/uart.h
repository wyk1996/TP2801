/*
 * @Author: your name
 * @Date: 2020-08-31 18:07:20
 * @LastEditTime: 2020-09-01 21:35:25
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \bootloader��������\Inc\uart.h
 */
#ifndef	__UART_H__
#define __UART_H__

#include "define_all.h"  

#define USB_BUF_SIZE     1040

typedef struct{
    uint8_t *rx_buf;
    uint16_t rx_size;

    volatile uint16_t read_pos;
    volatile uint16_t write_pos;
    volatile uint16_t rx_count;
    volatile uint16_t rx_end;
}uart_t;

void uart_init(void);

void uart_transmit_buf(uint8_t *tx_buf, uint16_t tx_size);

uint16_t uart_recv_data(uint8_t *recv_buf ,uint16_t recv_len, uint16_t wait_tick);

#endif
