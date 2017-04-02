/*
*******************************************************************************
**  Copyright (c) 2013, �����пƼ����������Զ������޹�˾
**  All rights reserved.
**	�ļ���: encComm.h
**  description  : ����һЩ����⹫�õĺ�ͳ���
**  date           :  2013.10.18
**
**  version       :  1.0
**  author        :  sven
*******************************************************************************
*/
#ifndef __ENC_COMM_H__
#define __ENC_COMM_H__

#include "const.h"

/******ADоƬ����******/
#define AD_NOCHIP		0
#define AD_TVP5150		1
#define AD_TW2815A     	2
#define AD_TW2815AB		3
#define AD_TW2815ABCD	4
#define	AD_CMOS_MT9D131	5
#define AD_TW2865A      6
/******��Ƶ��ʽ******/
typedef enum VideoStandard
{
	HI_PAL = 0,
	HI_NTSC = 1
}VIDEO_STANDARD_E;

/******��Ƶ�ֱ���******/
typedef enum PictureFormat 
{
	HI_QCIF = 0,
	HI_CIF,
	HI_2CIF,
	HI_HD1,
	HI_D1,
	HI_MD1,
	HI_QVGA,
	HI_VGA,
	HI_SXGA
}PICTURE_FORMAT_E;

/******��Ƶ��������******/
typedef enum VideoBitrateMode
{
	HI_CBR = 0,
	HI_VBR = 1
}VIDEO_BITRATE_MODE;

/******������������******/
typedef enum
{
	HI_AUDIO = 0,
	HI_VIDEO = 1,
	HI_AUDIO_VIDEO = 2
}VideoEncMode;

#define DEFAULT_ENCODE_STANDARD	    	HI_PAL         //PAL
#define DEFAULT_ENCODE_RESOLUTION		HI_D1	    //cif
#define DEFAULT_ENCODE_SUB_RESOLUTION	HI_CIF         //cif
#define DEFAULT_ENCODE_BITRATE_TYPE		HI_CBR         //CBR
#define DEFAULT_ENCODE_LEVEL	    	128	        //����(������32~4000 kbits) 
#define DEFAULT_ENCODE_FRAME_RATE		25	        //֡��(PAL:1~25,NTSC:1~30)
#define DEFAULT_ENCODE_FRAME_INTERVAL	50	        //I֡���(1~149)
#define DEFAULT_ENCODE_PREFER_FRAME		1              //0 ��������, 1 �������� ,3512�Ѿ���֧��
#define DEFAULT_ENCODE_MAX_QP	    	32	        //QP,3512�Ѿ���֧��
#define DEFAULT_ENCODE_TYPE	        	HI_VIDEO    //0: ����Ƶ��, 1: ��Ƶ��, 2: ��Ƶ��
#define DEFAULT_AUDIO_SAMPLE_RATE		0	        //8K	
#define DEFAULT_AUDIO_BIT_WIDTH	    	1	        //16bit
#define DEFAULT_AUDIO_ENCODE_TYPE		5	        //g726_24k
#define DEFAULT_AMR_MODE	        	0	        //MIME
#define DEFAULT_AMR_FORMAT	        	0	        //4.75K

#define MAX_CHANNEL_PER_DEV	        	4	        // һ��videv ֧��4��ͨ��ʱ�ָ���
#define MAX_JPEG_SIZE                     (512*1024)        /*ץ�����֧��512KbytesJPEG*/

#endif //__ENC_COMM_H__

