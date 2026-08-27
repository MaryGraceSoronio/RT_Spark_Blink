#include "stm32f4xx_hal.h"

/* RT-Spark RGB LED Pins */
#define LED_RED_PIN    GPIO_PIN_12
#define LED_GREEN_PIN  GPIO_PIN_11
#define LED_BLUE_PIN   GPIO_PIN_10
#define LED_ALL_PINS   (LED_RED_PIN | LED_GREEN_PIN | LED_BLUE_PIN)
#define LED_PORT       GPIOF

static void GPIO_Init(void);

int main(void)
{
    /* Reset peripherals, initialize Flash interface and Systick */
    HAL_Init();

    /* Initialize GPIO Port F pins */
    GPIO_Init();

    while (1)
    {
        /* Turn ON all colors (Active-LOW: Pull LOW to light up) */
        HAL_GPIO_WritePin(LED_PORT, LED_ALL_PINS, GPIO_PIN_RESET);
        HAL_Delay(500);

        /* Turn OFF all colors (Pull HIGH to turn off) */
        HAL_GPIO_WritePin(LED_PORT, LED_ALL_PINS, GPIO_PIN_SET);
        HAL_Delay(500);
    }
}

static void GPIO_Init(void)
{
    /* Enable Clock for GPIOF */
    __HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_ALL_PINS;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

/* Required by HAL for HAL_Delay() */
void SysTick_Handler(void)
{
    HAL_IncTick();
}