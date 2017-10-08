/**
  ******************************************************************************
  * �ļ�����: bsp_esp8266.c 
  * ��    ��: ӲʯǶ��ʽ�����Ŷ�
  * ��    ��: V1.0
  * ��д����: 2015-10-04
  * ��    ��: WiFi(ESP8266)�ײ�����ʵ��
  ******************************************************************************
  * ˵����
  * ����������Ӳʯstm32������YS-F1Proʹ�á�
  * 
  * �Ա���
  * ��̳��http://www.ing10bbs.com
  * ��Ȩ��ӲʯǶ��ʽ�����Ŷ����У��������á�
  ******************************************************************************
  */
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "bsp_esp8266.h"
#include "bsp_uart.h"
#include "delay.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include <stdarg.h>

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
struct  STRUCT_USARTx_Fram strEsp8266_Fram_Record = { 0 };

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
static char * itoa( int value, char * string, int radix );

/* ������ --------------------------------------------------------------------*/

void Send(uint8_t dat)
{
  while(( UART2_GetFlagStatus(UART2_FLAG_TXE)==RESET));
	
		UART2_SendData8(dat);
	
}

/**
  * ��������: ��ʼ��ESP8266�õ���GPIO����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
//static void ESP8266_GPIO_Config ( void )
//{
//	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	/* ���� CH_PD ����*/
//	RCC_APB2PeriphClockCmd( ESP8266_RST_CLK, ENABLE ); 	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//	
//	/* ���� RST ����*/									   
//	GPIO_InitStructure.GPIO_Pin = ESP8266_RST_PIN;
//	GPIO_Init ( ESP8266_RST_PORT, & GPIO_InitStructure );		
  
//  /* ����WiFiģ��ĸ�λ��������	*/
//  GPIO_ResetBits( ESP8266_RST_PORT, ESP8266_RST_PIN );
  
//}


/**
  * ��������: ��ʼ��ESP8266�õ��� USART
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
static void ESP8266_USART_Config ( void )
{
      SerialInit();
	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;	
//	
//	/* config USART clock */
//	ESP8266_USART_APBxClock_FUN ( ESP8266_USART_CLK, ENABLE );
//	ESP8266_USART_GPIO_APBxClock_FUN ( ESP8266_USART_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE );
//	
//	/* USART GPIO config */
//	/* Configure USART Tx as alternate function push-pull */
//	GPIO_InitStructure.GPIO_Pin =  ESP8266_USART_TX_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(ESP8266_USART_TX_PORT, &GPIO_InitStructure);  
//  
//	/* Configure USART Rx as input floating */
//	GPIO_InitStructure.GPIO_Pin = ESP8266_USART_RX_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(ESP8266_USART_RX_PORT, &GPIO_InitStructure);
//	
//	/* USART1 mode config */
//	USART_InitStructure.USART_BaudRate = ESP8266_USART_BAUD_RATE;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(ESP8266_USARTx, &USART_InitStructure);
//	
//	/* �ж����� */
//	USART_ITConfig ( ESP8266_USARTx, USART_IT_RXNE, ENABLE ); //ʹ�ܴ��ڽ����ж� 
//	USART_ITConfig ( ESP8266_USARTx, USART_IT_IDLE, ENABLE ); //ʹ�ܴ������߿����ж� 	
//
//	ESP8266_USART_NVIC_Configuration();	
//	
//	USART_Cmd(ESP8266_USARTx, ENABLE);	
//
//      /* ���������ɱ�־ */
//	USART_ClearFlag(ESP8266_USARTx, USART_FLAG_TC|USART_FLAG_TXE|USART_FLAG_RXNE);
}

/**
  * ��������: ��ʽ�������������C���е�printf��������û���õ�C��
  * �������: USARTx ����ͨ��������ֻ�õ��˴���2����USART2
  *		        Data   Ҫ���͵����ڵ����ݵ�ָ��
  *			      ...    ��������
  * �� �� ֵ: ��
  * ˵    ��������Ӧ�� USART2_printf( USART2, "\r\n this is a demo \r\n" );
  *            		     USART2_printf( USART2, "\r\n %d \r\n", i );
  *            		     USART2_printf( USART2, "\r\n %s \r\n", j );
  */
void USART_printf(char * Data, ... )
{
	const char *s;
	int d;   
	char buf[16];
	
	va_list ap;
	va_start(ap, Data);
	while ( * Data != 0 )     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( * Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
//					USART_SendData(USARTx, 0x0d);
                                        Send(0x0d);
					Data ++;
				break;
				case 'n':							          //���з�
//					USART_SendData(USARTx, 0x0a);
                                        Send(0x0a);
					Data ++;
				break;
				default:
					Data ++;
				break;
			}			 
		}
		else if ( * Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
					for ( ; *s; s++) 
					{
//						USART_SendData(USARTx,*s);
                                                Send(*s);
//						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
                                                while(UART2_GetFlagStatus(UART2_FLAG_TXE)==RESET);
                                        }				
					Data++;				
				break;
				case 'd':			
					//ʮ����
					d = va_arg(ap, int);					
					itoa(d, buf, 10);					
					for (s = buf; *s; s++) 
					{
//						USART_SendData(USARTx,*s);
                                                Send(*s);
//						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
                                                while(UART2_GetFlagStatus(UART2_FLAG_TXE)==RESET);
					}					
					Data++;				
				break;				
				default:
					Data++;				
				break;				
			}		 
		}		
//		else USART_SendData(USARTx, *Data++);
                else Send(*Data++);
//		while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXE ) == RESET );
                while(UART2_GetFlagStatus(UART2_FLAG_TXE)==RESET);
	}
}

/**
  * ��������: ����������ת�����ַ���
  * �������: radix =10 ��ʾ10���ƣ��������Ϊ0
  *           value Ҫת����������
  *           buf ת������ַ���
  *           radix = 10
  * �� �� ֵ: ��
  * ˵    ������USART_printf()����
  */
static char * itoa( int value, char *string, int radix )
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;
	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
		*ptr = 0;
		return string;
	}
	if (!value)
	{
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}
	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
		*ptr++ = '-';
		/* Make the value positive. */
		value *= -1;
	}
	for (i = 10000; i > 0; i /= 10)
	{
		d = value / i;
		if (d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
	}
	/* Null terminate the string. */
	*ptr = 0;
	return string;
} /* NCL_Itoa */

/**
  * ��������: ESP8266��ʼ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void ESP8266_Init ( void )
{
	//ESP8266_GPIO_Config ();	
	ESP8266_USART_Config ();	
}

/**
  * ��������: ֹͣʹ��ESP8266
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void  ESP8266_stop( void )
{
	ESP8266_RST_LOW_LEVEL();
	
        UART2_DeInit();	
        UART2_ITConfig(UART2_IT_RXNE_OR, DISABLE);
      
//	USART_ITConfig ( ESP8266_USARTx, USART_IT_RXNE, DISABLE ); //ʹ�ܴ��ڽ����ж� 
//	USART_ITConfig ( ESP8266_USARTx, USART_IT_IDLE, DISABLE ); //ʹ�ܴ������߿����ж� 	
//	USART_Cmd( ESP8266_USARTx, DISABLE);
//	ESP8266_USART_APBxClock_FUN ( ESP8266_USART_CLK, DISABLE );
}

/**
  * ��������: ����ESP8266ģ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������ESP8266_AT_Test����
  */
void ESP8266_Rst ( void )
{
#if 0
	 ESP8266_Cmd ( "AT+RST", "OK", "ready", 2500 );   	
#else
	 ESP8266_RST_LOW_LEVEL();
	 delay_ms(250); 
     delay_ms(250);
	 ESP8266_RST_HIGH_LEVEL(); 
#endif
}

/**
  * ��������: ��ESP8266ģ�鷢��ATָ��
  * �������: cmd�������͵�ָ��
  *           reply1��reply2���ڴ�����Ӧ��ΪNULL������Ӧ������Ϊ���߼���ϵ
  *           waittime���ȴ���Ӧ��ʱ��
  * �� �� ֵ: 1��ָ��ͳɹ�
  *           0��ָ���ʧ��
  * ˵    ������
  */
bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, u32 waittime )
{    
	strEsp8266_Fram_Record .InfBit .FramLength = 0;               //���¿�ʼ�����µ����ݰ�

	ESP8266_Usart ( "%s\r\n", cmd );

	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //����Ҫ��������
		return true;
	
	delay_ms( waittime );                 //��ʱ
	
	strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';

	PC_Usart ( "%s", strEsp8266_Fram_Record .Data_RX_BUF );
//  printf("%s->%s\n",cmd,strEsp8266_Fram_Record .Data_RX_BUF);
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply1 ) || 
						 ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply1 ) );
	
	else
		return ( ( bool ) strstr ( strEsp8266_Fram_Record .Data_RX_BUF, reply2 ) );
	
}

/**
  * ��������: ��ESP8266ģ�����AT��������
  * �������: ��
  * �� �� ֵ: 1��ѡ��ɹ�
  *           0��ѡ��ʧ��
  * ˵    ������
  */
bool ESP8266_AT_Test ( void )
{
	char count=0;
	
	ESP8266_RST_HIGH_LEVEL();	
	delay_s ( 1 );
	while(count<10)
	{
		if(ESP8266_Cmd("AT","OK",NULL,1000)) return 1;
		ESP8266_Rst();
    delay_s ( 1 );
		++count;
	}
	return 0;
}

/**
  * ��������: ѡ��ESP8266ģ��Ĺ���ģʽ
  * �������: enumMode������ģʽ
  * �� �� ֵ: 1��ѡ��ɹ�
  *           0��ѡ��ʧ��
  * ˵    ������
  */
bool ESP8266_Net_Mode_Choose ( ENUM_Net_ModeTypeDef enumMode )
{
	bool result=0;
	char count=0;
	while(count<10)
	{
		switch ( enumMode )
		{
			case STA:
				result=ESP8266_Cmd ( "AT+CWMODE=1", "OK", "no change", 2500 ); 
			break;
			case AP:
				result=ESP8266_Cmd ( "AT+CWMODE=2", "OK", "no change", 2500 ); 
			break;
			case STA_AP:
				result=ESP8266_Cmd ( "AT+CWMODE=3", "OK", "no change", 2500 ); 
			break;
			default:
				result=false;
			break;
		}
		if(result) return result;
		++count;
	}
	return 0;
}

/**
  * ��������: ESP8266ģ�������ⲿWiFi
  * �������: pSSID��WiFi�����ַ���
  *           pPassWord��WiFi�����ַ���
  * �� �� ֵ: 1�����ӳɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_JoinAP ( char * pSSID, char * pPassWord )
{
	char cCmd [120];
	char count=0;
	sprintf ( cCmd, "AT+CWJAP=\"%s\",\"%s\"", pSSID, pPassWord );
	while(count<10)
	{
		if(ESP8266_Cmd(cCmd,"OK",NULL,5000))return 1;
		++count;
	}
	return 0;	
}

/**
  * ��������: ESP8266ģ�鴴��WiFi�ȵ�
  * �������: pSSID��WiFi�����ַ���
  *           pPassWord��WiFi�����ַ���
  *           enunPsdMode��WiFi���ܷ�ʽ�����ַ���
  * �� �� ֵ: 1�������ɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_BuildAP ( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode )
{
	char cCmd [120];
	char count=0;
	sprintf ( cCmd, "AT+CWSAP=\"%s\",\"%s\",1,%d", pSSID, pPassWord, enunPsdMode );
	while(count<10)
	{
		if(ESP8266_Cmd(cCmd,"OK",0,1000))return 1;
		++count;
	}
	return 0;	
}

/**
  * ��������: ESP8266ģ������������
  * �������: enumEnUnvarnishTx�������Ƿ������
  * �� �� ֵ: 1�����óɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_Enable_MultipleId ( FunctionalState enumEnUnvarnishTx )
{
	char cStr [20];
	char count=0;
	sprintf ( cStr, "AT+CIPMUX=%d", ( enumEnUnvarnishTx ? 1 : 0 ) );
	while(count<10)
	{
		if(ESP8266_Cmd(cStr,"OK",0,500))return 1;
		++count;
	}
	return 0;		
}

/**
  * ��������: ESP8266ģ�������ⲿ������
  * �������: enumE������Э��
  *           ip��������IP�ַ���
  *           ComNum���������˿��ַ���
  *           id��ģ�����ӷ�������ID
  * �� �� ֵ: 1�����ӳɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_Link_Server ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id)
{
	char cStr [100] = { 0 }, cCmd [120];

  switch (  enumE )
  {
		case enumTCP:
		  sprintf ( cStr, "\"%s\",\"%s\",%s", "TCP", ip, ComNum );
		  break;
		
		case enumUDP:
		  sprintf ( cStr, "\"%s\",\"%s\",%s", "UDP", ip, ComNum );
		  break;
		
		default:
			break;
  }

  if ( id < 5 )
    sprintf ( cCmd, "AT+CIPSTART=%d,%s", id, cStr);

  else
	  sprintf ( cCmd, "AT+CIPSTART=%s", cStr );

	return ESP8266_Cmd ( cCmd, "OK", "ALREAY CONNECT", 4000 );
	
}

/**
  * ��������: ESP8266ģ�鿪����رշ�����ģʽ
  * �������: enumMode������/�ر�
  *           pPortNum���������˿ں��ַ���
  *           pTimeOver����������ʱʱ���ַ�������λ����
  * �� �� ֵ: 1�������ɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_StartOrShutServer ( FunctionalState enumMode, char * pPortNum, char * pTimeOver )
{
	char cCmd1 [120], cCmd2 [120];

	if ( enumMode )
	{
		sprintf ( cCmd1, "AT+CIPSERVER=%d,%s", 1, pPortNum );
		
		sprintf ( cCmd2, "AT+CIPSTO=%s", pTimeOver );

		return ( ESP8266_Cmd ( cCmd1, "OK", 0, 500 ) &&
						 ESP8266_Cmd ( cCmd2, "OK", 0, 500 ) );
	}
	
	else
	{
		sprintf ( cCmd1, "AT+CIPSERVER=%d,%s", 0, pPortNum );

		return ESP8266_Cmd ( cCmd1, "OK", 0, 500 );
	}
}

/**
  * ��������: ��ȡESP8266 ������״̬�����ʺϵ��˿�ʱʹ��
  * �������: ��
  * �� �� ֵ: 2�����ip
  *           3����������
  *           4��ʧȥ����
  *           0����ȡ״̬ʧ��
  * ˵    ������
  */
uint8_t ESP8266_Get_LinkStatus ( void )
{
	if ( ESP8266_Cmd ( "AT+CIPSTATUS", "OK", 0, 500 ) )
	{
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "STATUS:2\r\n" ) )
			return 2;
		
		else if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "STATUS:3\r\n" ) )
			return 3;
		
		else if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "STATUS:4\r\n" ) )
			return 4;		
	}
	return 0;
}

/**
  * ��������: ��ȡESP8266 �Ķ˿ڣ�Id������״̬�����ʺ϶�˿�ʱʹ��
  * �������: ��
  * �� �� ֵ: �˿ڣ�Id��������״̬����5λΪ��Чλ���ֱ��ӦId5~0��ĳλ����1���Id���������ӣ�������0���Idδ��������
  * ˵    ������
  */
uint8_t ESP8266_Get_IdLinkStatus ( void )
{
	uint8_t ucIdLinkStatus = 0x00;
	
	
	if ( ESP8266_Cmd ( "AT+CIPSTATUS", "OK", 0, 500 ) )
	{
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+CIPSTATUS:0," ) )
			ucIdLinkStatus |= 0x01;
		else 
			ucIdLinkStatus &= ~ 0x01;
		
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+CIPSTATUS:1," ) )
			ucIdLinkStatus |= 0x02;
		else 
			ucIdLinkStatus &= ~ 0x02;
		
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+CIPSTATUS:2," ) )
			ucIdLinkStatus |= 0x04;
		else 
			ucIdLinkStatus &= ~ 0x04;
		
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+CIPSTATUS:3," ) )
			ucIdLinkStatus |= 0x08;
		else 
			ucIdLinkStatus &= ~ 0x08;
		
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+CIPSTATUS:4," ) )
			ucIdLinkStatus |= 0x10;
		else 
			ucIdLinkStatus &= ~ 0x10;	
	}
	return ucIdLinkStatus;
}

/**
  * ��������: ��ȡESP8266 �� AP IP
  * �������: pApIp����� AP IP ��������׵�ַ
  *           ucArrayLength����� AP IP ������ĳ���
  * �� �� ֵ: 1����ȡ�ɹ�
  *           0����ȡʧ��
  * ˵    ������
  */
uint8_t ESP8266_Inquire_ApIp ( char * pApIp, uint8_t ucArrayLength )
{
	char uc;
	
	char * pCh;
	
	
  ESP8266_Cmd ( "AT+CIFSR", "OK", 0, 500 );
	
	pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "APIP,\"" );
	
	if ( pCh )
		pCh += 6;
	
	else
		return 0;
	
	for ( uc = 0; uc < ucArrayLength; uc ++ )
	{
		pApIp [ uc ] = * ( pCh + uc);
		
		if ( pApIp [ uc ] == '\"' )
		{
			pApIp [ uc ] = '\0';
			break;
		}
	}
	return 1;
}

/**
  * ��������: ����ESP8266ģ�����͸������
  * �������: ��
  * �� �� ֵ: 1�����óɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_UnvarnishSend ( void )
{
	
	if ( ! ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 1000 ) )
		return false;
	return  ESP8266_Cmd ( "AT+CIPSEND", "OK", ">", 1000 );
	
}

/**
  * ��������: ����ESP8266ģ���˳�͸��ģʽ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void ESP8266_ExitUnvarnishSend ( void )
{
	delay_s (1);
	
	ESP8266_Usart ( "+++" );
	
	delay_ms( 250 ); 
	delay_ms( 250 );
}

/**
  * ��������: ESP8266ģ�鷢���ַ���
  * �������: enumEnUnvarnishTx�������Ƿ���ʹ����͸��ģʽ
  *           pStr��Ҫ���͵��ַ���
  *           ucId���ĸ�ID���͵��ַ���
  *           ulStrLength��Ҫ���͵��ַ������ֽ���
  * �� �� ֵ: 1�����ͳɹ�
  *           0������ʧ��
  * ˵    ������
  */
bool ESP8266_SendString ( FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId )
{
	char cStr [20];
	bool bRet = false;
	
		
	if ( enumEnUnvarnishTx )
	{
		ESP8266_Usart ( "%s", pStr );
		
		bRet = true;
		
	}

	else
	{
		if ( ucId < 5 )
			sprintf ( cStr, "AT+CIPSEND=%d,%d", ucId, ulStrLength + 2 );

		else
			sprintf ( cStr, "AT+CIPSEND=%d", ulStrLength + 2 );
		
		ESP8266_Cmd ( cStr, "> ", 0, 1000 );

		bRet = ESP8266_Cmd ( pStr, "SEND OK", 0, 1000 );
  }
	
	return bRet;

}

/**
  * ��������: ESP8266ģ������ַ���
  * �������: enumEnUnvarnishTx�������Ƿ���ʹ����͸��ģʽ
  * �� �� ֵ: ���յ����ַ����׵�ַ
  * ˵    ������
  */
char * ESP8266_ReceiveString ( FunctionalState enumEnUnvarnishTx )
{
	char * pRecStr = 0;
	
	
	strEsp8266_Fram_Record .InfBit .FramLength = 0;
	strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;
	
	while ( ! strEsp8266_Fram_Record .InfBit .FramFinishFlag );
	strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ] = '\0';
	
	if ( enumEnUnvarnishTx )
		pRecStr = strEsp8266_Fram_Record .Data_RX_BUF;
	else 
	{
		if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+IPD" ) )
			pRecStr = strEsp8266_Fram_Record .Data_RX_BUF;

	}
	return pRecStr;	
}
/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
