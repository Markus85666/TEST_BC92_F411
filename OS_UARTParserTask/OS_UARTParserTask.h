#include "OS_MainTask.h"


#define UART_DMA_BUFFER_SIZE 128
#define PARSER_MESSAGE_LIST_SIZE 16
#define PARSER_MESSAGE_SIZE 32


void OS_UARTParserTask(void *argument);
