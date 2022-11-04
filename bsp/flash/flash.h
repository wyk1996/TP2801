/*
 * @Author: your name
 * @Date: 2020-08-31 18:07:20
 * @LastEditTime: 2020-09-01 16:49:46
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \bootloaderÒýµ¼³ÌÐò\Inc\flash.h
 */
#ifndef	__FLASH_H__
#define __FLASH_H__

#include "define_all.h"  

void FlashInit(void);
uint8_t flash_erase_sector( uint16_t SectorNum);
uint8_t flash_write_buff( uint32_t prog_addr,uint32_t* prog_data, uint16_t Len);
uint32_t flash_read_word(uint32_t faddr);

#endif
