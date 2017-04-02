/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ���Դ�ӡ�����ӿ�
********************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/syslog.h>
#include "mutex.h"
#include "debug.h"  

#define PRINTF_BUF_SIZE 16*1024
static char s_MsgBuf[PRINTF_BUF_SIZE];
static ClMutexLock s_PrintfMutex;

extern void logMessage( int pri, char *msg );

void PrintHex( const char *message, unsigned char *data, int len, const char *format, ... )
{
	if ( message != NULL )
    {
    	printf( "%s", message );
    }
	if ( data != NULL )
    {
    	for ( int i = 0; i < len; ++i )
        	printf( "%02X ", data[i] );
    }
	if ( format != NULL )
    {
    	va_list ap;
    	va_start( ap, format );
    	vprintf( format, ap );
    	va_end( ap );
    }    
}

/**********************************************************************
* fn: ��ӡ�ļ���,���� �� ��������
************************************************************************/
void PfDumpPrint(const char *file, int line, const char *format, ... )
{    
	char	*pMsgBuf, *pBasename;
	int		nMsgLen;    
    
	va_list ap;
	va_start( ap, format );
    
	pBasename = (char *)basename( file );
    
	s_PrintfMutex.Lock();
    
	sprintf( s_MsgBuf, "%s %d:", pBasename, line );
	pMsgBuf = s_MsgBuf + strlen(s_MsgBuf);
	nMsgLen = sizeof(s_MsgBuf) - strlen(s_MsgBuf);
	vsnprintf( pMsgBuf, nMsgLen, format, ap );    
	fprintf( stderr, "%s", s_MsgBuf ); 
    
	s_PrintfMutex.Unlock();
    
	va_end( ap );    
}

/************************************************************************
* fn: ��ӡ��������
************************************************************************/
void Print( const char *format, ... )
{
	va_list ap;
	va_start( ap, format );
    
	s_PrintfMutex.Lock();
	vsnprintf( s_MsgBuf, sizeof(s_MsgBuf), format, ap );
	s_PrintfMutex.Unlock();
    
	vfprintf( stderr, format, ap );
	va_end( ap );
}

/*******************************************************************************
* fn: ��ӡ�ļ���,���� �� ��������, �����Ǵ�ӡ����ǰ�ն�,����telnet
********************************************************************************/
void TeDumpPrint(const char *file, int line, const char *format, ... )
{    
	char	*pMsgBuf, *pBasename;
	int		nMsgLen;    
    
	va_list ap;
	va_start( ap, format );
    
	pBasename = (char *)basename( file );
    
	s_PrintfMutex.Lock();
    
	sprintf( s_MsgBuf, "%s %d:", pBasename, line );
	pMsgBuf = s_MsgBuf + strlen(s_MsgBuf);
	nMsgLen = sizeof(s_MsgBuf) - strlen(s_MsgBuf);
	vsnprintf( pMsgBuf, nMsgLen, format, ap );    
	fprintf( stderr, "%s", s_MsgBuf ); 

//	logMessage( LOG_SYSLOG | LOG_INFO, s_MsgBuf );
    
	s_PrintfMutex.Unlock();
    
	va_end( ap );    
}

