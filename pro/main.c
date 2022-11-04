/*
 * @Author: your name
 * @Date: 2020-08-31 18:07:20
 * @LastEditTime: 2020-09-01 21:33:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \bootloaderÒýµ¼³ÌÐò\Src\main.c
 */
#include "main.h"  


int main (void)
{	
	App_Init();
	while(1) {
		App_Handle();
	}
}
