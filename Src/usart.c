/*
 * uart.c
 *
 *  Created on: Mar 23, 2026
 *      Author: maksym
 */

#include "usart.h"

/*******************************************************
 * @fn            USART_Init
 *
 * @brief         This function initializes the USARTx peripheral according to the specified settings in the handle structure
 *
 * @param[in]     Pointer to the structure of USARTx peripheral configurations and settings
 *
 * @return        none
 */
void USART_Init(USART_Handle_t *pUSART_Handle){
	uint32_t tmp = 0;

	/**************************Configuration of CR1***********************************/

	//Enable the USARTx peripheral Clock
	USART_ClockControl(pUSART_Handle->pUSARTx, ENABLE);

	//USART Tx and Rx enable
	if(pUSART_Handle->USART_Config.USART_Mode == USART_MODE_ONLY_RX){
		//RX mode
		tmp |= (1 << USART_CR1_RE);
	}else if(pUSART_Handle->USART_Config.USART_Mode == USART_MODE_ONLY_TX){
		//TX mode
		tmp |= (1 << USART_CR1_TE);
	}else if(pUSART_Handle->USART_Config.USART_Mode == USART_MODE_TXRX){
		//TXRX mode
		tmp |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
	}
	//Configure the Word length

	//Clear the M0 and M1 bits in CR1
	tmp &= ~(1 << USART_CR1_M);

	//set the Word length
	tmp |= (pUSART_Handle->USART_Config.USART_WordLength << USART_CR1_M);

	//Configuration of parity control
	if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN){

		//enable parity control (EVEN parity enabled by default)
		tmp |= (1 << USART_CR1_PCE);

	}else if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD){
		tmp |= (1 << USART_CR1_PCE);

		//Enable Parity ODD mode
		tmp |= (1 << USART_CR1_PS);
	}
	//Program the CR1 register
	pUSART_Handle->pUSARTx->CR1 = tmp;

	/*******************************Configuration of CR2**********************************/
	tmp = 0;

	//Configure the number of the USARTx STOP bits

	//Clear STOP bits
	tmp &= ~(0x3 << USART_CR2_STOP);

	//set STOP bits
	tmp |= (pUSART_Handle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP);

	pUSART_Handle->pUSARTx->CR2 = tmp;

	/**************************************Configuration of CR3*****************************/
	tmp = 0;

	//Configure the USARTx Hardware Flow Control
	if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS){
		//CTS mode
		tmp |= (1 << USART_CR3_CTSE);
	}else if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS){
		//RTS mode
		tmp |= (1 << USART_CR3_RTSE);
	}else if(pUSART_Handle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS){
		//Both CTS and RTS mode

		//Clear CTSE and RTSE bits before setting
		tmp &= ~((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE));

		//set CTSE and RTSE bits
		tmp |= ((1 <<USART_CR3_CTSE) | (1 << USART_CR3_RTSE));
	}

	pUSART_Handle->pUSARTx->CR3 = tmp;

	/**************************************Configure the BRR***********************************/
	tmp = 0;

	//This part will be filled later according to the courses
}
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
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}

/************************************************************************
 * @fn                 USART_Transmit
 *
 * @brief              This function
 *
 * @param[in]          Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]          Pointer to the TX buffer which contains the data that we want to send
 * @param[in]          Length of the data
 *
 * @return             none
 */
void USART_Transmit(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t len){
	uint16_t *pData;
	(void)pData;

	//Loop over until all bytes (data length) are transferred
	for(uint32_t i = 0; i < len; i++){

		//Wait until TXE flag is set in the SR
		while(!USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_FLAG_TXE));

		//Check the Word Length (9 or 8 bits)
		if(pUSART_Handle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS){

			//9BITS, load the DR with 2 bytes masking the bits other than first 9 bits
			pData = (uint16_t *)pTxBuffer;

			//Check for USART Parity Control
			if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
				//no parity is used in this transfer, so, 9 bits of user's data will be sent
				pUSART_Handle->pUSARTx->DR = (*pData & (uint16_t)0x01FF);
				pTxBuffer += 2;
			}else{
			//parity bit is used in this transfer, so, 8 bits of user data will be sent
			//9th bit will be replaced by parity bit by the hardware
			pUSART_Handle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			pTxBuffer++;
		}
	}else{
		//8 bit transfer
		pUSART_Handle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
		pTxBuffer++;
		}
	}
	//Wait until TC flag is set in the SR
	while(!USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_FLAG_TC));
}

/****************************************************************************************
 * @fn              USART_Receive
 *
 * @brief           This function receives the data from another device and writes it in to DR
 *
 * @param[in]       Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]       Pointer to the RX buffer which contains the data that we want to write
 * @param[in]       Length of the data
 */
void USART_Receive(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t len){
	//Loop over until all bytes (data length) are transferred
	for(uint32_t i = 0; i < len; i++){
		while(!USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_BUSY_IN_RX)){
			if(USART_GetFlagStatus(pUSART_Handle->pUSARTx, USART_ERR_ORE)){
				//Read SR (done)
				//Read DR to clear the flag
				uint8_t dummy = pUSART_Handle->pUSARTx->DR;//BUT IN BLOCKING API IT DELETES 1 BYTE OF INFO
				(void)dummy;
			}
		}

		//Check the Word length
		if(pUSART_Handle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS){
			//We are going to receive 9 bits data in a frame

			//Check for parity control
			if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
				//no parity, all 9 bits will be user's data
				//read only first 9 bits, mask the DR with 0x01FF
				*((uint16_t*)pRxBuffer) = (pUSART_Handle->pUSARTx->DR & (uint16_t)0x01FF);
				pRxBuffer += 2;
			}else{
				//parity is used, 8 bits - data, 1 - parity bit
				*pRxBuffer = (pUSART_Handle->pUSARTx->DR & (uint8_t)0xFF);
				pRxBuffer++;
			}
		}else{
			//8 bits reception

			//Check Parity Control
			if(pUSART_Handle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE){
				//no parity, all 8 bits - data
				*pRxBuffer = pUSART_Handle->pUSARTx->DR;
			}else{
				//parity is used, 7 bits - data, 1 - parity bit
				//read 7 bits and mask the DR with 0x7F
				*pRxBuffer = (pUSART_Handle->pUSARTx->DR & (uint8_t)0x7F);
			}
			pRxBuffer++;
		}
	}
}

/**************************************************************************************
 * @fn               USART_TransmitIT
 *
 * @brief            This is a non-blocking API for sending the data with interruptions
 *
 * @param[in]        Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]        Pointer to the TX buffer which contains the data that we want to send
 * @param[in]        Data length
 *
 * @return           State of USARTx peripheral
 */
uint8_t USART_TransmitIT(USART_Handle_t *pUSART_Handle, uint8_t *pTxBuffer, uint32_t len){
	uint8_t tx_state = pUSART_Handle->TxState;

	if(tx_state != USART_BUSY_IN_TX){
		pUSART_Handle->TxLen = len;
		pUSART_Handle->pTxBuffer = pTxBuffer;
		pUSART_Handle->TxState = USART_BUSY_IN_TX;

		//Enable TX interrupt
		pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);

		//Enable TC interrupt
		//pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);
	}

	return tx_state;
}

/************************************************************************************
 * @fn               USART_ReceiveIT
 *
 * @brief            This is a non-blocking API for reception the data with interruptions
 *
 * @param[in]        Pointer to the structure with USARTx peripheral register base addresses
 * @param[in]        Pointer to the RX buffer which contains the data that we want to write
 * @param[in]        Data length
 *
 * @return           State of USARTx peripheral
 */
uint8_t USART_ReceiveIT(USART_Handle_t *pUSART_Handle, uint8_t *pRxBuffer, uint32_t len){
	uint8_t rx_state = pUSART_Handle->RxState;

	if(rx_state != USART_BUSY_IN_RX){
		pUSART_Handle->RxLen = len;
		pUSART_Handle->pRxBuffer = pRxBuffer;
		pUSART_Handle->RxState = USART_BUSY_IN_RX;

		//Enable RX interrupt
		pUSART_Handle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);
	}

	return rx_state;
}

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
