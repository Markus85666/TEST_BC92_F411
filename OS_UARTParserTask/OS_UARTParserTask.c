#include "OS_UARTParserTask.h"

#warning Need refactoring code!

extern UART_HandleTypeDef 	huart2;

uint8_t rxBuffer[UART_DMA_BUFFER_SIZE];		/* Буфер приема данных UART_DMA */

size_t 	dma_head = 0;						/* Начало команды */
size_t	dma_tail = 0;						/* Конец команды */

size_t 	cur_msg_sz = 0;						/* Размер принятой команды */
size_t 	cur_msg = 0;							/* Индекс текущей принятая команда по UART */

uint8_t found = 0;							/* Флаг обнаружения конца команды (\r\n) */


uint8_t msg_list[PARSER_MESSAGE_LIST_SIZE][PARSER_MESSAGE_SIZE];		/* Массив для хранения принятых команд */


void OS_UARTParserTask(void *argument)
{
    while(1)
    {
    	do
    	{
    	    dma_tail = UART_DMA_BUFFER_SIZE - huart2.hdmarx->Instance->NDTR;

            if(dma_tail!=dma_head)
            {
            	if(dma_head < dma_tail)
            	{
					for(register size_t i=dma_head; i<dma_tail; i++)
					{
								found = (found == 0 && rxBuffer[i] == '\r') ? 1
								  : (found == 1 && rxBuffer[i] == '\n') ? 2
								  : 0;
						msg_list[cur_msg][cur_msg_sz++]= rxBuffer[i];

						if(found==2)
							{
								cur_msg = cur_msg == PARSER_MESSAGE_LIST_SIZE-1 ? 0 : cur_msg + 1;
								memset(msg_list[cur_msg],0,PARSER_MESSAGE_SIZE);
								cur_msg_sz=0;
//								HC05_RxCommandCallback();
							}
					}
					if(found != 2)
					{
//						osQItem_t messageHC05;
//						messageHC05 = OS_MessageConstructor(0, OS_CMD_HC05_GET_COMMAND, OS_HC05_CMD_ERROR, 0);
//						xQueueSend (OS_HC05QueueHandle, &messageHC05, ( TickType_t ) portMAX_DELAY);
						cur_msg = cur_msg == PARSER_MESSAGE_LIST_SIZE-1 ? 0 : cur_msg + 1;
						memset(msg_list[cur_msg],0,PARSER_MESSAGE_SIZE);
						cur_msg_sz=0;
					}

            	}
            	else
            	{
            	    for(register size_t i=dma_head; i<UART_DMA_BUFFER_SIZE; i++)
            	    {
							found = (found == 0 && rxBuffer[i] == '\r') ? 1
							  : (found == 1 && rxBuffer[i] == '\n') ? 2
							  : 0;
						msg_list[cur_msg][cur_msg_sz++]= rxBuffer[i];

						if(found==2)
						{
							cur_msg = cur_msg == PARSER_MESSAGE_LIST_SIZE-1 ? 0 : cur_msg + 1;
							memset(msg_list[cur_msg],0,PARSER_MESSAGE_SIZE);
									cur_msg_sz=0;
						}

            	    }

            	    for(register size_t i=0; i<dma_tail; i++)
            	    {
							found = (found == 0 && rxBuffer[i] == '\r') ? 1
							  : (found == 1 && rxBuffer[i] == '\n') ? 2
							  : 0;

						msg_list[cur_msg][cur_msg_sz++]= rxBuffer[i];

						if(found==2)
						{
							cur_msg = cur_msg == PARSER_MESSAGE_LIST_SIZE-1 ? 0 : cur_msg + 1;
							memset(msg_list[cur_msg],0,PARSER_MESSAGE_SIZE);
									cur_msg_sz=0;
//									HC05_RxCommandCallback();
						}
            	    }
					if(found != 2)
					{
//						osQItem_t messageHC05;
//						messageHC05 = OS_MessageConstructor(0, OS_CMD_HC05_GET_COMMAND, OS_HC05_CMD_ERROR, 0);
//						xQueueSend (OS_HC05QueueHandle, &messageHC05, ( TickType_t ) portMAX_DELAY);
						cur_msg = cur_msg == PARSER_MESSAGE_LIST_SIZE-1 ? 0 : cur_msg + 1;
						memset(msg_list[cur_msg],0,PARSER_MESSAGE_SIZE);
						cur_msg_sz=0;
					}
            	}
            	dma_head=dma_tail;
            }
        }while(dma_head!=(UART_DMA_BUFFER_SIZE- huart2.hdmarx->Instance->NDTR));

        osDelay(100); // this should be the minimum time difference between each frame
    }
}
