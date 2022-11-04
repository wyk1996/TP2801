/*
 * @Author: your name
 * @Date: 2020-08-31 18:07:20
 * @LastEditTime: 2020-09-01 21:46:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \bootloader��������\Src\uart.c
 */
#include "app.h" 
#include "systick.h"

/* ����ԭ�� ----------------------------------------------------------*/
/* ��  ---------------------------------------------------------------*/
/* ���� --------------------------------------------------------------*/
static uart_t usb_uart;
static uint8_t usb_buff[USB_BUF_SIZE];
/* ���Ͷ��� ----------------------------------------------------------*/
/* �������� ----------------------------------------------------------*/
static void uart_recv_irq_proc(void);
static void uart_isr_rx_timeout(void);
/**
 * @description: ���ڳ�ʼ��
 * @param {type} 
 * @return {type} 
 */
void uart_init(void)
{
    LL_GPIO_InitTypeDef io_config = {0};
    LL_UART_InitTypeDef uart_config = {0};   
    
    io_config.Pin        = LL_GPIO_PIN_2 | LL_GPIO_PIN_3;
    io_config.Mode       = LL_GPIO_MODE_DIGITAL;
    io_config.OutputType = LL_GPIO_OUTPUT_PUSHPULL;		
    LL_GPIO_Init(GPIOA, &io_config);

    usb_uart.rx_size            = USB_BUF_SIZE;
    usb_uart.rx_buf             = usb_buff;
    usb_uart.rx_count           = 0;
    usb_uart.rx_end             = 0;
    usb_uart.read_pos           = 0;
    usb_uart.write_pos          = 0;

	uart_config.BaudRate           = 115200;								//������
	uart_config.DataWidth          = LL_UART_DATAWIDTH_8B;				//����λ��
	uart_config.StopBits           = LL_UART_STOPBITS_1;					//ֹͣλ
	uart_config.Parity             = LL_UART_PARITY_NONE;					//��żУ��
	uart_config.TransferDirection  = LL_UART_DIRECTION_TX_RX;	//����-����ʹ��
	uart_config.InfraredModulation = DISABLE;	
	uart_config.ClockSrc           = LL_RCC_UART_OPERATION_CLOCK_SOURCE_APBCLK1;			        
	LL_UART_Init(UART0, &uart_config);


	NVIC_DisableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_EnableIRQ(UART0_IRQn);

	LL_UART_SetRxTimeOut(UART0, 50);//���ճ�ʱ
	
	LL_UART_Enable_ReceiveTimeOut(UART0);
	
	LL_UART_EnableIT_ReceiveTimeOut(UART0);
	LL_UART_EnableIT_ReceiveBuffFull(UART0);
}

/**
 * @description: ���ڷ���BUF
 * @param  ���ڵ�ID
 * @param  Ҫ���͵�buff 
 * @param  ���͵ĳ���
 * @return None
 **/
void uart_transmit_buf(uint8_t *tx_buf, uint16_t tx_size)
{
    uart_t *uart;
    uint16_t tx_cnt = 0;

    if(uart == NULL)
        return;

	while(tx_cnt < tx_size) {
		LL_UART_TransmitData(UART0, tx_buf[tx_cnt++]);
		while(SET != LL_UART_IsActiveFlag_TXSE(UART0));
	}
}

/**
 * @description: ��ȡ���հ�����
 * @return �ѽ��յĳ���
 */
uint16_t uart_get_rx_cnt(void)
{
    uint16_t rx_cnt = 0;

    if(usb_uart.rx_end == 1)
    {
        usb_uart.rx_end = 0;
        rx_cnt = usb_uart.rx_count;
    }
    return rx_cnt;
}

/**
 * @description: ���ڽ�������
 * @param  ���ڵ�ID
 * @param  ���ջ�����
 * @param  Ҫ���յ���󳤶�
 * @param  �ȴ�ʱ��
 * @return ���յĳ���
 */
uint16_t uart_recv_data(uint8_t *recv_buf ,uint16_t recv_len, uint16_t wait_tick)
{
	uint16_t rx_count = 0,save_count = 0;

	while(wait_tick--)   /*�ȴ��������ݽ������*/
	{
		if((rx_count = uart_get_rx_cnt()) != 0)
			break;
	}
	
	if(rx_count > 0)
	{
		memset(recv_buf, 0, recv_len);
		
		if(rx_count >= recv_len)
			rx_count = recv_len;
	
		for(; save_count < rx_count; save_count++)
		{
			recv_buf[save_count] = usb_uart.rx_buf[usb_uart.read_pos];
			if(++usb_uart.read_pos >=usb_uart.rx_size)
			{
				usb_uart.read_pos = 0;
			}
		}
		usb_uart.rx_count -= rx_count;
		
		recv_buf[save_count] = '\0';
	}
	return rx_count;
}

/**
 * @description: ���ڳ�ʱ�жϻص�
 * @param  uart_id ���ڵ�ID
 * @return None
 */
static void uart_isr_rx_timeout(void)
{
	usb_uart.rx_end = 1;
}
/**
 * @description: ���ڽ����жϻص�
 * @param  uart_id ���ڵ�ID
 * @return None
 */
static void uart_recv_irq_proc(void)
{
    uint8_t rd;
    rd = LL_UART_ReceiveData(UART0);
    
	if(usb_uart.rx_count < usb_uart.rx_size)
	{
		usb_uart.rx_end = 0;
		usb_uart.rx_count++;
		
		usb_uart.rx_buf[usb_uart.write_pos] = rd;
		
		if(++usb_uart.write_pos >= usb_uart.rx_size)
		{
			usb_uart.write_pos = 0;
		}
	}
	usb_uart.rx_end = 0;
}

/**
 * @description: ����1�ж�̎����
 * @return None
 */
void UART0_IRQHandler(void)
{
	if((ENABLE == LL_UART_IsEnbaledIT_ReceiveBuffFull(UART0))
		&&(SET == LL_UART_IsActiveFlag_RXBF(UART0)))
	{
		//�ж�ת�����յ�������
		uart_recv_irq_proc();
	}
	if((ENABLE == LL_UART_IsActiveFlag_RXTO(UART0)))
	{
		//���ճ�ʱ�ж�
		uart_isr_rx_timeout(); 
		LL_UART_ClearFlag_RXTO(UART0);
	}
}

