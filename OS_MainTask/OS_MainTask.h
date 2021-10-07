#pragma once

#include "main.h"
#include "stdio.h"

#include "OS_UARTParserTask.h"


#pragma pack (push,1)
/** Структура сообщения ОС */
typedef struct
{
    uint32_t   oscmd;  /**< osCommand_t    */
    uint32_t   size;   /**< Размер данных  */
    void       *data;  /**< Данные         */
    uint32_t   param;  /**< osParameters_t */
}osQItem_t;
#pragma pack (pop)



void OS_MainTask(void *argument);
