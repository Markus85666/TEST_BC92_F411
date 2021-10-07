#include "BC92.h"

#include "stdio.h"

/**
 * @brief   Передача команды на GSM/GPRS/LTE модуль BC92 и получение ответа
 * @param	* uart		-	указатель на структуру UART
 * @param	* cmd		-	указатель на передаваемую команду
 * @param	timeout		-	timeout ответа на команду
 * @code	OS_BC92_Send_AT_Cmd(&huart2, "AT\r", 300);
 * @return	bool
 */
bool OS_BC92_Send_AT_Cmd(UART_HandleTypeDef *uart, uint8_t *cmd, uint32_t timeout)
{
	uint32_t responseTime = HAL_GetTick() + timeout;

	HAL_UART_Transmit_DMA(uart, cmd, sizeof(cmd) - 1);

	while(1)
	{
		if(HAL_GetTick() > responseTime)	/* Превышен timeout команды */
		{
			printf("\nTIMEOUT: %s\n", cmd);
			return 1;
		}
	}

	return 0;
}


/**
 * @brief   Аппаратный сброс модуля ( ‾‾‾‾|____reset____|‾‾‾‾‾ )
 * @param	void
 * @return	bool
 */
bool OS_BC92_Hardware_Reset(void)
{
	HAL_GPIO_WritePin(BC92_RESET_GPIO_PORT, BC92_RESET_PIN, GPIO_PIN_SET);

	HAL_Delay(1000);

	HAL_GPIO_WritePin(BC92_RESET_GPIO_PORT, BC92_RESET_PIN, GPIO_PIN_RESET);

	return 0;
}







