/*
 * @Author: your name
 * @Date: 2020-08-31 18:49:02
 * @LastEditTime: 2020-09-01 21:46:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \bootloader引导程序\Src\iap.c
 */
#include "main.h"
#include "iap.h"

static const uint8_t s_CRCH[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
} ;
// CRC 低位字节值表
const uint8_t s_CRCLo[] = {

0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};

uint16_t cal_crc16(const uint8_t* _pBuf, uint32_t _len)
{
	uint8_t ucCRCH = 0xFF;
	uint8_t ucCRCL = 0xFF;
	int usIndex;

	while(_len--)
	{
		usIndex = ucCRCH^*(_pBuf++);  /*计算CRC*/
		ucCRCH = (uint8_t)(ucCRCL ^ s_CRCH[usIndex]);
		ucCRCL = s_CRCLo[usIndex];
	}
	return ((uint16_t)ucCRCH<<8|ucCRCL);
}


void iap_load_app(uint32_t app_addr)
{
    uint32_t jump_addr;
    jump_addr = *(__IO uint32_t*) (app_addr + 4);
    __set_MSP(*(__IO uint32_t*) app_addr);
    (*( void (*)( ) )jump_addr) ();
}

int iap_recv_proc(uint8_t *data, uint16_t *length,uint32_t timeout)
{
    uint16_t recv_size = 0;
		uint16_t crc;
    *length = 0;

    recv_size = uart_recv_data(data, 1040, timeout);
    if(recv_size == 0) //没收到数据
    {
        return 2;
    }

    if(data[0] == 0x7e && data[recv_size -1] == 0x7f)
    {
			if(data[3] != 0X29) 
			{
				*length = ((uint16_t)(data[8] << 8) | data[9] - 1);	//大小端转换  高字节在前低字节在后
			}
			crc = cal_crc16(data, recv_size - 3);
			if(crc == ((uint16_t )(data[recv_size - 2] << 8) | data[recv_size - 3]))
			{
				return 0;
			}
			else 
			{
				return 3;
			}
    }
    return 1;
}

/************
 * 发送应答数据
************/
void iap_ack(uint8_t *p_msg, uint16_t msg_len, uint16_t data_len)
{
		uint8_t boot_info[64] = {0X7E, 0X02, 0X05, 0X01, 0X01};
    uint8_t index = 5;

    uint16_t crc;

    boot_info[index++] = msg_len >> 8;
    boot_info[index++] = msg_len;
    boot_info[index++] = 0x01;
    boot_info[index++] = data_len >> 8;
    boot_info[index++] = data_len;

    memcpy(&boot_info[index], p_msg, data_len);//数据拷贝
	index += data_len;  
    
	crc = cal_crc16(&boot_info[0], index);//计算校验和
	boot_info[index++] = crc;
	boot_info[index++] = crc >> 8;
	boot_info[index++] = 0X7F;
	uart_transmit_buf(boot_info, index);
}

uint8_t flash_buff[1024];

void iap_write_flash(uint8_t *msg, uint16_t lenght)
{
	char write_page[15] = {""};	
	char page[4];	
	
	memcpy(flash_buff, &msg[11], lenght); //拷贝数据
	//程序写进flash 10k空间
	flash_write_buff(APPLICATION_ADDRESS_OFFSET + 1024 * msg[10], (uint32_t *)flash_buff, lenght / 4);

	strcat( write_page, "Page[" ); 
    sprintf(page,"%d",msg[10]);
	strcat(write_page,page); 
    strcat(write_page,"] OK\r\n");
	
	iap_ack((uint8_t *)write_page, strlen(write_page) + 3, strlen(write_page));
}
void iap_done(void)
{
	uint32_t save_flag;
	save_flag = 0X12345678;
	LL_FLASH_PageErase(FLASH, APP_UPDATE_FLAG); //擦除地址内的数据
	flash_write_buff(APP_UPDATE_FLAG, &save_flag, 1);//程序写进地址内
	iap_load_app(APPLICATION_ADDRESS_OFFSET);//跳转并加载
}
