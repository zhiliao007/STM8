#include "stm8s_key.h"
#include "stm8s_conf.h"

/*******************************************************************************************************************
  * @brief        初始化外部中断函数
  * @param        无
  * @description  PC5配置为上拉输入有中断，中断触发方式为下降沿触发
  * @retval       无
  ******************************************************************************************************************/	
void EXIT_GPIO_Init(void)  
{   
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
    enableInterrupts();
}  

