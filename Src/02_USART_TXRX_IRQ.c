/*
 * 02_USART_TXRX_IRQ.c
 *
 *  Created on: Apr 7, 2026
 *      Author: maksym
 */

#include "stm32f407xx.h"
#include "gpio.h"
#include "usart.h"

uint8_t tx[] = "Hello";
uint8_t rx[6];

void Delay(void){for(uint32_t i = 0; i < 250000; i++);}

void Button_Init(void){
    GPIO_Handle_t button;

    button.pGPIOx = GPIOE;
    GPIO_ClockControl(GPIOE, ENABLE);

    button.GPIOx_CFG.pin_number = GPIO_PIN_3;
    button.GPIOx_CFG.pin_mode = GPIO_MODE_IN;
    button.GPIOx_CFG.pin_speed = GPIO_OSPEED_HIGH;
    button.GPIOx_CFG.pin_pu_pd_ctrl = GPIO_PIN_PU;

    GPIO_Init(&button);
}

void USART_GPIO_Init(void){
	GPIO_Handle_t usart_gpio;

	usart_gpio.pGPIOx = GPIOA;
	GPIO_ClockControl(GPIOA, ENABLE);

	usart_gpio.GPIOx_CFG.pin_mode = GPIO_MODE_ALT_FN;
	usart_gpio.GPIOx_CFG.pin_alt_func_mode = 7;
	usart_gpio.GPIOx_CFG.pin_op_type = GPIO_OUT_PP;
	usart_gpio.GPIOx_CFG.pin_pu_pd_ctrl = GPIO_NO_PUPD;
	usart_gpio.GPIOx_CFG.pin_speed = GPIO_OSPEED_HIGH;

	//TX
	usart_gpio.GPIOx_CFG.pin_number = GPIO_PIN_9;
	GPIO_Init(&usart_gpio);

	//RX
	usart_gpio.GPIOx_CFG.pin_number = GPIO_PIN_10;
	GPIO_Init(&usart_gpio);
}

USART_Handle_t usart1;
void USART1_IRQHandler(void){USART_IRQHandle(&usart1);}

void USART1_Init(void){
	usart1.pUSARTx = USART1;

	USART_ClockControl(USART1, ENABLE);

	usart1.USART_Config.USART_Mode = USART_MODE_TXRX;
	usart1.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart1.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart1.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart1.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	usart1.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;

	USART_Init(&usart1);
}

void USART_ApplicationEventCallback(USART_Handle_t *pUSART_Handle, uint8_t event){
	if(event == USART_EV_TX_CMPLT){
		USART_ReceiveIT(&usart1, rx, 6);
	}else if(event == USART_EV_RX_CMPLT){

	}else if(event == USART_EV_IDLE){

	}else if(event == USART_EV_CTS){

	}else if(event == USART_ERR_ORE){

	}else if(event == USART_ERR_PE){

	}else if(event == USART_ERR_FE){

	}else if(event == USART_ERR_NE){

	}
}

int main(void){
	Button_Init();
	USART_GPIO_Init();
	USART1_Init();

	USART_PeripheralControl(USART1, ENABLE);
	USART_IRQInterruptConfig(IRQ_NO_USART1, ENABLE);
	USART_EnableInterrupt(&usart1, USART_FLAG_ORE, ENABLE);

	while(1){
		while(GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 1);
		Delay();

		while(GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 0);
		Delay();

		USART_TransmitIT(&usart1, tx, strlen((char*)tx));
	}
}

