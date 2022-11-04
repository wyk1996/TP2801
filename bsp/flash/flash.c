#include "main.h"  

ErrorStatus flash_program_buff(uint32_t addr, uint32_t *data, uint32_t len)
{
	ErrorStatus ret;
  uint32_t i;
	for(i = 0; i < len; i++)
	{
		ret = LL_FLASH_Program_Word(FLASH, addr + i * 4, data[i]);
		if(ret == FAIL)
			return FAIL;
	}
  return PASS;
}

//����������(ÿ������512�ֽ�) 
//������bootloader����ֹ����boot��
//���������sector_num   ��Ҫ����������������
uint8_t flash_erase_sector( uint16_t sector_num)
{
	uint16_t i;
	uint8_t result = 0;
	uint32_t *p_flash;
	
	if(sector_num < (APPLICATION_ADDRESS_OFFSET / 512)) return 2;//��ֹ����bootloader��
	p_flash = (uint32_t *)(uint32_t)(sector_num * 512);
	LL_FLASH_PageErase(FLASH,sector_num * 512);
	for (i = 0; i < 128; i++ )
	{
		if (p_flash[i] != 0xFFFFFFFF ) 
		{
			result = 1;
			break;
		}
	}
	return result;
}

//����дflash����
//���������prog_addr  ��дflash�׵�ַ
//			prog_data  ��д���ݻ�����
//			Len        д�볤��(һ�β�Ҫд��̫�࣬���⿴�Ź����)
uint8_t flash_write_buff( uint32_t prog_addr,uint32_t* prog_data, uint16_t Len)
{
	uint16_t i;
	uint8_t result = 0;
	uint32_t *p_flash;
	
	#if 0
	if(prog_addr < APPLICATION_ADDRESS_OFFSET) return 2;//��ֹдbootloader��
	#endif
	
  	flash_program_buff(prog_addr, prog_data, Len);
	
	p_flash = (uint32_t*)prog_addr;
	for (i = 0; i < Len; i++)
	{
		if (p_flash[i] != prog_data[i]) 
		{
			result = 1;
			break;
		}
	}
	return result;
}

uint32_t flash_read_word(uint32_t faddr)
{
	return *(__IO uint32_t*) (faddr);
}
