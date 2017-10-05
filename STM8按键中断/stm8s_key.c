#include "stm8s_key.h"
#include "stm8s_conf.h"

/*******************************************************************************************************************
  * @brief        ��ʼ���ⲿ�жϺ���
  * @param        ��
  * @description  PC5����Ϊ�����������жϣ��жϴ�����ʽΪ�½��ش���
  * @retval       ��
  ******************************************************************************************************************/	
void EXIT_GPIO_Init(void)  
{   
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_FALL_ONLY);
    enableInterrupts();
}  

