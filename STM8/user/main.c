/**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: 
  * 版    本: V1.0
  * 编写日期: 
  * 功    能: 
  ******************************************************************************
  * 说明：
  * 
  * 
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm8s.h"
#include "stdlib.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_uart.h"
#include "bsp_esp8266.h"
#include "delay.h"
    
/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
#define User_ESP8266_ApSsid                       "LAB"              //要连接的热点的名称
#define User_ESP8266_ApPwd                        "lab141516"           //要连接的热点的密钥

#define User_ESP8266_TcpServer_IP                 "192.168.31.196"       //要连接的服务器的 IP
#define User_ESP8266_TcpServer_Port               "1234"                 //要连接的服务器的端口

/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
extern __IO uint8_t ucTcpClosedFlag;

/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/

/**
  * 函数功能: 主函数.
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void main(void)
{
    uint8_t pCH;
    //LED初始化
    LED_GPIO_Init();
    //按键中断初始化
    EXIT_GPIO_Init();
    //串口初始化
    ESP8266_Init();
    printf("正在配置 ESP8266 ......\n" );
    
    if(ESP8266_AT_Test())
  {
    printf("AT test OK\n");
  }
  printf("\n< 1 >\n");
	if(ESP8266_Net_Mode_Choose(STA))
  {
    printf("ESP8266_Net_Mode_Choose OK\n");
  }  
  printf("\n< 2 >\n");
  while(!ESP8266_JoinAP(User_ESP8266_ApSsid,User_ESP8266_ApPwd));		
	printf("\n< 3 >\n");
  ESP8266_Enable_MultipleId(DISABLE);	
	while(!ESP8266_Link_Server(enumTCP,User_ESP8266_TcpServer_IP,User_ESP8266_TcpServer_Port,Single_ID_0));	
	printf("\n< 4 >\n");
  while(!ESP8266_UnvarnishSend());	
	printf("配置 ESP8266 完毕\n");
  
  /* 无限循环 */
    while (1)
    {
        ESP8266_ReceiveString(ENABLE);
        printf("hello world!\n");
        
        if ( strEsp8266_Fram_Record .InfBit .FramFinishFlag )
		{
            strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
            printf ( "\r\n%s\r\n", strEsp8266_Fram_Record .Data_RX_BUF );
            /*将接收到的字符串转成整形数*/
            pCH=atoi(strEsp8266_Fram_Record .Data_RX_BUF);

            switch(pCH)
            {
                case 0:
                LED1_ON;
                break;
          
                case 1:
                LED1_OFF;
                break;
            }
//LED1_TOGGLE;
//delay_s(1);          
        }
    }
}


/* 
 *	库函数使用了C编译器的断言功能，如果定义了USE_FULL_ASSERT(在
 *  stm8s_conf.h定义，默认被注释掉)，那么所有的HAL库函数将检查函数形参是
 *  否正确。如果不正确将调用 assert_failed() 函数，这个函数是一个死循环，便于用
 *  户检查代码。
 *
 *	关键字 __LINE__ 表示源代码行号。
 *	关键字__FILE__表示源代码文件名。
 *
 *  断言功能使能后将增大代码大小，推荐用户仅在调试时使能，在正式发布软件是禁止。
 *
 *	用户可以选择是否使能HAL库的断言供能。使能断言的方法有两种：
 * 	(1) 在C编译器的预定义宏选项中定义USE_FULL_ASSERT。
 *	(2) 在stm32f1xx_hal_conf.h文件取消"#define USE_FULL_ASSERT    1"行的注释。	
*/
#ifdef USE_FULL_ASSERT
/**
  * 函数功能: 断言失败服务函数
  * 输入参数: file : 源代码文件名称。关键字__FILE__表示源代码文件名。
  *           line ：代码行号。关键字 __LINE__ 表示源代码行号
  * 返 回 值: 无
  * 说    明: 无
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* 
	 *	用户可以添加自己的代码报告源代码文件名和代码行号，比如将错误文件和行号打印到串口
	 *	printf("Wrong parameters value: file %s on line %d\r\n", file, line)
	 */
	
	/* 这是一个死循环，断言失败时程序会在此处死机，以便于用户查错 */
    while (1)
    {
    }
}
#endif /*USE_FULL_ASSERT*/

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
