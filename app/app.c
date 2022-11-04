#include "app.h"
#include "systick.h"
#include "mf_config.h"
#include "iap.h"
#include "user_init.h"


static uint8_t pack_data[1040];
static char boot_resp[] = {"!Find TP2801 OK\r\n ZY Boot Ver2.0\r\n"};
uint8_t  fun_code, cnt = 0;
uint16_t len = 0;



static void deinit_system(void)
{
	__disable_irq();//关闭全局中断使能
	LL_GPIO_ALLPIN_LPM_MODE();//引脚还原
	NVIC_DisableIRQ(UART0_IRQn);//关闭串口中断
	LL_UART_DisableIT_ShiftBuffEmpty(UART0);  //关闭发送中断
	LL_UART_DisableIT_ReceiveBuffFull(UART0);  //关闭接收中断
	LL_UART_DisableDirectionTx(UART0);   	  //关闭发送使能
	LL_UART_DisableDirectionRx(UART0);		  //关闭接收使
}




void App_Init(void)
{
	MF_GPIO_Config();   
    User_Systick_Init();

    /***********
     * 返回flash内存地址
     ***********/
    if (flash_read_word(APP_UPDATE_FLAG) == 0x2801) {
        iap_load_app(APPLICATION_ADDRESS_OFFSET);
    }   
	
	uart_init();
	__enable_irq();	//打开全局中断使能
}



void App_Handle(void)
{
    memset(pack_data, 0, sizeof(pack_data));
    
    if(iap_recv_proc(pack_data, &len, 0x3000) == 0)
    {
        fun_code = pack_data[3];
        switch(fun_code) {
            case 0X2C: {
                if (len % 4) {
                    len += 4;
                }
                iap_write_flash(pack_data, len);
                break;
            }
            case 0X2A: {
                if(++cnt >= 2) {
                    deinit_system();
                    iap_load_app(APPLICATION_ADDRESS_OFFSET);
                }
                break;
            }
            case 0X29: {
                iap_ack((uint8_t *)boot_resp, strlen(boot_resp) + 3, strlen(boot_resp));
                break;
            }
            case 0X2F: {
                //擦除中
                for(uint8_t i = 0; i < 256 - 10; i++) {
                    LL_FLASH_SectorErase(FLASH, (i + 10) * 1024);
                }
                iap_ack((uint8_t *)"Erase OK\r\n",19,16);
                break;
            }
        }
    }  
}

