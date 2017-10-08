#ifndef BSP_LED_H
#define BSP_LED_H

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm8s.h"

/* 类型定义 ------------------------------------------------------------------*/
typedef enum
{
  LED_OFF = 0,
  LED_ON,
}LEDState_TypeDef;

/* 宏定义 --------------------------------------------------------------------*/
#define LED1                          (uint8_t)0x01
  
/*
 * 以下宏定义内容跟开发板硬件息息相关，需要查看开发板电路原理图才能正确编写。
 * 例如，查原理图可在LED1灯接在stm32f103芯片的PE5引脚上，所以有关LED1的宏定义
 * 都是与GPIOE，GPIO_Pin_5相关的，我们专门把这些与开发板硬件相关的内容定义为宏，
 * 这对于修改或者移植程序非常方便。
 */

#define LED1_GPIO_PIN                 GPIO_PIN_5
#define LED1_GPIO                     GPIOE

/* 调用标准库函数方法 */
#define LED1_ON                       GPIO_WriteHigh(LED1_GPIO, (GPIO_Pin_TypeDef)LED1_GPIO_PIN)
#define LED1_OFF                      GPIO_WriteLow(LED1_GPIO, (GPIO_Pin_TypeDef)LED1_GPIO_PIN)
#define LED1_TOGGLE                   GPIO_WriteReverse(LED1_GPIO, (GPIO_Pin_TypeDef)LED1_GPIO_PIN);

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
void LED_GPIO_Init(void);
void LEDx_StateSet(uint8_t LEDx,LEDState_TypeDef state);

#endif /*BSP_LED_H*/
