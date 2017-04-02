/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.09.16
**  description  : ֧��һ��������->��������ߵ���
         �ƶ����ץ��ר�õ�������������ģ��
********************************************************************************/

#if 1
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "debug.h"
#include "procon.h"
#include "malloc.h"
#include "thread.h"

static CProcon g_mdProcon( BLOCK_NO, DATA_TYPE_NOMAL );

void ProconMdInit( int chNum, int dataNode )
{
	g_mdProcon.Init( chNum, dataNode );
}

uint ProconMdOpen( int channel, int flag )
{
	return g_mdProcon.Open( channel, flag );
}

void ProconMdClose( uint fd )
{
	g_mdProcon.Close( fd );
}

int ProconMdWrite( uint fd, DATA_PIECE_T proDataInfo )
{
	int ret;    
    
	ret = g_mdProcon.Write( fd, proDataInfo );    

	return ret;
}

PROCON_NODE_T *ProconMdRead( uint fd )
{
	return g_mdProcon.Read( fd );
}

void ProconMdFree( PROCON_NODE_T *pcpNode )
{
	g_mdProcon.Tfree( pcpNode );
}

#endif

