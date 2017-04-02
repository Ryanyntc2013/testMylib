/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**	�ļ���: osdViVo.h
**  description  : for osdViVo.cpp
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __OSD_VI_VO_H__
#define __OSD_VI_VO_H__

#if defined MCU_HI3515
#include "hi_comm_vpp.h"
#endif

#if defined MCU_HI3515A
#include "hi_comm_vpss.h"
#include "hi_comm_region.h"
#endif
#include "osdComm.h"



int FiOsdInitOsdLib();

/*
* ���ʼ��������
* type:0-VI;1-VO
*/
int FiOsdDeinitOsdLib(void);


int FiOsdInitOsd( int type, int ch, OSD_RECT rc, unsigned int color, 
                	uchar  bgTransparence, HI_U32  *handle );

/*
* ����ָ��OSD
* type:0-VI;1-VO
* ch:vegroup 0~31
*/
int FiOsdDestroyOsd(int type,int ch);

/*
* ���õ�ǰ���Ӳ���ʾ��������
* type:0-VI;1-VO
* ch:vegroup 0~31
* bshow:0-����;1-��ʾ
*/
int FiOsdSetShow(int type,int ch, int bshow);

/*
* дһ���ַ���
* type:0-VI;1-VO
* ch:vegroup 0~31
* color:��ɫ
* x��y:�����OSD������
* string:����
* font_size:���ִ�С,Ŀǰֻ֧��0
* lace:�Ƿ�Բ����ɫ
*/
int FiOsdDrawString( int type,int ch, int color, int x, int y, 
            	const char *string, int font_size, int lace);

/*�������ֿ�*/
int SVOsdInitFont(void);

/*ж�����ֿ�*/
int SVOsdDestroyFont(void);

int FiOsdCheckAscFont();
int FiOsdCheckChineseFont();


int SVOsdInitOsd(int type,VI_CHN ViChannel,OSD_RECT rc,unsigned int color,
 RGN_HANDLE *handle ,eOSDTYPE eosdtype);

int SVOsdDestroyOsd(int type,int ch);

int SVOsdSetShow(int type,int ch, int bshow,OSD_RECT rc,VI_CHN ViChn,uchar  
bgTransparence,eOSDTYPE eosdtype);

int SVOsdDrawString( int type,int ch, int color, int x, int y, 
            	const char *string, int font_size, int lace);

#endif //__OSD_VI_VO_H__



