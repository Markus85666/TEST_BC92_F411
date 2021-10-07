#include "OS_MainTask.h"

#include "cmsis_os.h"
#include "BC92.h"

extern UART_HandleTypeDef 	huart2;

extern uint8_t rxBuffer[UART_DMA_BUFFER_SIZE];

static void OS_Init (void);



osThreadId_t			OS_UARTParserTaskHandle;


static void OS_Init (void)
{

	HAL_UART_Receive_DMA(&huart2, rxBuffer, UART_DMA_BUFFER_SIZE);

	osDelay(100);

	/* Создание задачи OS_UARTParserTask */
	const osThreadAttr_t OS_UARTParserTask_attributes = {
	  .name = "OS_UARTParserTask",
	  .priority = (osPriority_t) osPriorityNormal,
	  .stack_size = 128 * 4
	};

	if( !(OS_UARTParserTaskHandle = osThreadNew(OS_UARTParserTask, NULL, &OS_UARTParserTask_attributes)) )
	{
		printf("\nERROR: OS_UARTParserTask creation failed!\n");
	}
	else
	{
		printf("\nOS_UARTParserTask has been successfully initialized!\n");
	}
}


void OS_MainTask(void *argument)
{

	OS_Init();

	osDelay(100);

	while(1)
	{
		osDelay(1000);
	}

}
