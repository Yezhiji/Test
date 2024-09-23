#include "stm32f1xx_hal.h"
uint8_t Key_Val, Key_Down, Key_Up, Key_Old;

uint8_t Key_Read(void)
{
	uint8_t KeyNum = 0;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		KeyNum = 12;
	}
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		KeyNum = 15;
	}
	return KeyNum;
}

void Key_Proc(void)
{
	Key_Val = Key_Read();
	Key_Down = Key_Val & (Key_Val ^ Key_Old);
	Key_Up = ~Key_Val & (Key_Val ^ Key_Old);
	Key_Old = Key_Val;
}
