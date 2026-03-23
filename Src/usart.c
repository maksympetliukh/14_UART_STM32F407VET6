/*
 * uart.c
 *
 *  Created on: Mar 23, 2026
 *      Author: maksym
 */

#include "usart.h"

void USART_Init(USART_Handle_t *pUSART_Handle);
/*********************************************
 * @fn              USART_DeInit
 *
 * @brief           This function disables and resets USARTx peripheral
 *
 * @param[in]       Pointer to the structure with USARTx peripheral register base addresses
 *
 * @return          none
 */
void USART_DeInit(USART_REG_t *pUSARTx){
	if(pUSARTx == NULL){return;}

	if(pUSARTx == USART1){
		USART1_REG_RESET();
	}else if(pUSARTx == USART2){
		USART2_REG_RESET();
	}else if(pUSARTx == USART3){
		USART3_REG_RESET();
	}else if(pUSARTx == UART4){
		UART4_REG_RESET();
	}else if(pUSARTx == UART5){
		UART5_REG_RESET();
	}else if(pUSARTx == USART6){
		USART6_REG_RESET();
	}
}

/**************************************************************
 * @fn           USART_ClockCOntrol
 *
 * @brief        This function enables/disables USARTx peripheral Clock
 *
 * @param[in]    Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]    Enable/Disable variable
 *
 * @return       none
 */
void USART_ClockControl(USART_REG_t *pUSARTx, uint8_t enDi){
	if(enDi == ENABLE){
		if(pUSARTx == USART1){
			RCC_USART1_CLK_ENABLE();
		}else if(pUSARTx == USART2){
			RCC_USART2_CLK_ENABLE();
		}else if(pUSARTx == USART3){
			RCC_USART3_CLK_ENABLE();
		}else if(pUSARTx == UART4){
			RCC_UART4_CLK_ENABLE();
		}else if(pUSARTx == UART5){
			RCC_UART5_CLK_ENABLE();
		}else if(pUSARTx == USART6){
			RCC_USART6_CLK_ENABLE();
		}
	}else{
		if(pUSARTx == USART1){
			RCC_USART1_CLK_DISABLE();
		}else if(pUSARTx == USART2){
			RCC_USART2_CLK_DISABLE();
		}else if(pUSARTx == USART3){
			RCC_USART3_CLK_DISABLE();
		}else if(pUSARTx == UART4){
			RCC_UART4_CLK_DISABLE();
		}else if(pUSARTx == UART5){
			RCC_UART5_CLK_DISABLE();
		}else if(pUSARTx == USART6){
			RCC_USART6_CLK_DISABLE();
		}
	}
}

/**************************************************************
 * @fn           USART_PeripheralControl
 *
 * @brief        This function enables or disables USARTx peripheral
 *
 * @param[in]    Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]    enable/disable variable
 *
 * @return       none
 */
void USART_PeripheralControl(USART_REG_t *pUSARTx, uint8_t enDi){
	if(enDi == ENABLE){
		pUSARTx->CR1 |= (1 << 13);
	}else{
		pUSARTx->CR1 &= ~(1 << 13);
	}
}

void USART_Transmit(USART_REG_t *pUSARTx, uint8_t *pTxBuffer, uint32_t len);
void USART_Receive(USART_REG_t *pUSARTx, uint8_t *pRxBuffer, uint32_t len);
uint8_t USART_TransmitIT(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t len);
uint8_t USART_ReceiveIT(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t len);
/*******************************************************************
 * @fn               USART_GetFlagStatus
 *
 * @brief            This function checks the flag status
 *
 * @param[in]        Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]        variable which contains the status flag of the USARTx peripheral
 *
 * @return           T or F
 */
uint8_t USART_GetFlagStatus(USART_REG_t *pUSARTx, uint32_t flag){
	if(pUSARTx->SR & flag){
		return SET;
	}
	return RESET;
}

void USART_ClearFlag(USART_REG_t *pUSARTx, uint16_t statusFlag);
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t enDi);
void USART_IRQIPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandle(USART_Handle_t *pUSART_Handle);
void USART_ApplicationEventCallback(USART_Handle_t *pUSART_Handle, uint8_t event);
