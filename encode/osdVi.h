/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**	�ļ���: osdVi.h
**  description  : for osdVi.cpp
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/

#ifndef __OSD_VI_H__
#define __OSD_VI_H__
#include "hi_comm_region.h"
#define OSD_ALIGN_X 8  // ������8 �����ض���
#define OSD_ALIGN 	2  // 2 �����ض���

#if defined MCU_HI3515A

typedef unsigned int REGION_HANDLE;
typedef struct OsdViParamBuf
{
	RGN_HANDLE bufHandle;
	int bufWidth;
	int bufHeight;    
	void *bufData;    
}OSD_VI_PARAM_BUF;


/*��ʼ��OSD��*/
int FiOsdViInitOsdLib(void);
/*���ʼ��OSD�� */
int FiOsdViDeinitOsdLib(void);
int FiOsdViInitOsd( VENC_GRP VeGroup,OSD_RECT rc, unsigned int color,  
                	uchar bgTransparence, RGN_HANDLE *handle );

int FiOsdViDestroyOsd(RGN_HANDLE handle);

/*���õ�ǰ���Ӳ���ʾ��������.
bshow :  1����ʾ 0������ */
int FiOsdViSetShow(RGN_HANDLE handle, int bshow);

/*дһ���ַ���.  */
int FiOsdViDrawString(RGN_HANDLE handle, int color, int x, int y, 
            	const char *string, int font_size, int lace);
int FiOsdViInitOsdBgClrEx( VENC_GRP VeGroup,OSD_RECT rc, unsigned int color,  
                        	uchar bgTransparence, REGION_HANDLE *handle );


int SVOsdViInitOsdBgClrEx( VI_CHN VeGroup,OSD_RECT rc, unsigned int color,  
            	RGN_HANDLE *handle ,eOSDTYPE eosdtype);

int SVOsdViInitOsd( VI_CHN VeGroup,OSD_RECT rc, unsigned int color,  
            	RGN_HANDLE *handle ,eOSDTYPE eosdtype);

int SVOsdViDestroyOsd(REGION_HANDLE handle);

int SVOsdViSetShow(RGN_HANDLE handle, int bshow,OSD_RECT rc,VI_CHN ViChn,
uchar  bgTransparence,eOSDTYPE eosdtype);

int SVOsdViDrawString(RGN_HANDLE handle, int color, int x, int y, 
            	const char *string, int font_size, int lace);

#endif //#if defined MCU_HI3515
#endif //__OSD_VI_H__



