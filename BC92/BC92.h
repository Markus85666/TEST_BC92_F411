#pragma once

#include "main.h"
#include "stdbool.h"

#define 	BC92_RESET_GPIO_PORT	RESET_N_GPIO_Port
#define 	BC92_RESET_PIN			RESET_N_Pin


bool OS_BC92_Send_AT_Cmd(UART_HandleTypeDef *uart, uint8_t *cmd, uint32_t timeout);
bool OS_BC92_Hardware_Reset(void);
