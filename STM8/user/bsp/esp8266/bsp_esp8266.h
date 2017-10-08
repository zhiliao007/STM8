#ifndef  __BSP_ESP8266_H__
#define	 __BSP_ESP8266_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm8s.h"
#include "IOSTM8S105K4.h"
#include <stdio.h>
#include <stdbool.h>

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
/* ���Ͷ��� ------------------------------------------------------------------*/
/******************************* ESP8266 �������Ͷ��� ***************************/
typedef enum{
	STA,
  AP,
  STA_AP  
} ENUM_Net_ModeTypeDef;

typedef enum{
	 enumTCP,
	 enumUDP,
} ENUM_NetPro_TypeDef;

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;
	
typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef;

/* �궨�� --------------------------------------------------------------------*/
#define RX_BUF_MAX_LEN     1024                                     //�����ջ����ֽ���

/******************************** ESP8266 �������Ŷ��� ***********************************/
#define ESP8266_RST_CLK                               RCC_APB2Periph_GPIOD
#define ESP8266_RST_PORT                              GPIOD
#define ESP8266_RST_PIN                               GPIO_Pin_5

#define ESP8266_USART_BAUD_RATE                       115200
#define ESP8266_USARTx                                USART1

#define ESP8266_USART_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define ESP8266_USART_CLK                             RCC_APB1Periph_USART2
#define ESP8266_USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define ESP8266_USART_GPIO_CLK                        RCC_APB2Periph_GPIOA     
#define ESP8266_USART_TX_PORT                         GPIOD   
#define ESP8266_USART_TX_PIN                          GPIO_Pin_6
#define ESP8266_USART_RX_PORT                         GPIOD
#define ESP8266_USART_RX_PIN                          GPIO_Pin_7
#define ESP8266_USART_IRQ                             USART1_IRQn
#define ESP8266_USART_INT_FUN                         USART1_IRQHandler

/*********************************************** ESP8266 �����궨�� *******************************************/
#define ESP8266_Usart( fmt, ... )           USART_printf ( fmt, ##__VA_ARGS__ ) 
#define PC_Usart( fmt, ... )                printf ( fmt, ##__VA_ARGS__ )
//#define PC_Usart( fmt, ... )                

#define ESP8266_RST_LOW_LEVEL()             PE_ODR^=0x00;//GPIO_SetBits(ESP8266_RST_PORT,ESP8266_RST_PIN )
#define ESP8266_RST_HIGH_LEVEL()            PE_ODR^=0x20;//GPIO_ResetBits(ESP8266_RST_PORT,ESP8266_RST_PIN )

/* ��չ���� ------------------------------------------------------------------*/
/******************************* ESP8266 �ⲿȫ�ֱ������� ***************************/
extern struct  STRUCT_USARTx_Fram                                  //��������֡�Ĵ���ṹ��
{
	char  Data_RX_BUF [ RX_BUF_MAX_LEN ];
  union {
    __IO u16 InfAll;
    struct {
		  __IO u16 FramLength       :15;                               // 14:0 
		  __IO u16 FramFinishFlag   :1;                                // 15 
	  } InfBit;
  }; 	
} strEsp8266_Fram_Record;


/* �������� ------------------------------------------------------------------*/
void  ESP8266_Init( void );
void  ESP8266_stop( void );
void  ESP8266_Rst( void );
bool  ESP8266_Cmd( char * cmd, char * reply1, char * reply2, u32 waittime );
bool  ESP8266_AT_Test( void );
bool  ESP8266_Net_Mode_Choose( ENUM_Net_ModeTypeDef enumMode );
bool  ESP8266_JoinAP( char * pSSID, char * pPassWord );
bool  ESP8266_BuildAP( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode );
bool  ESP8266_Enable_MultipleId( FunctionalState enumEnUnvarnishTx );
bool  ESP8266_Link_Server( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool  ESP8266_StartOrShutServer( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
uint8_t ESP8266_Get_LinkStatus( void );
uint8_t ESP8266_Get_IdLinkStatus( void );
uint8_t ESP8266_Inquire_ApIp( char * pApIp, uint8_t ucArrayLength );
bool ESP8266_UnvarnishSend( void );
void ESP8266_ExitUnvarnishSend( void );
bool ESP8266_SendString( FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId );
char * ESP8266_ReceiveString( FunctionalState enumEnUnvarnishTx );

void  USART_printf(char * Data, ... );

#endif

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
