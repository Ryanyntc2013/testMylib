/*
*********************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.11.06
**  description  : ��װһ��hisi ��mpi �ӿ�, ������ṩ�ӿ�
*********************************************************************
*/

#include "mpi_venc.h"
#include "hi_common.h"
#include "hicomm.h"
#include "const.h"
#include "debug.h"
#include "mutex.h"
#include "vencParamEasy.h"
#include "mpiApp.h"

static CMutexLock g_mympiMutex;
/*
* fn: ǿ��i ֡
*/
int MympiForceIframe( int channel )
{
	return HI_MPI_VENC_RequestIDR( channel << 1 );
}

/*
* fn: ����ͼ��ȼ�,[0,5],
* val: [0..5]. Valid when CBR/VBR.
 	With different RC mode, it means differ.
 	CBR: scope of bitrate fluctuate. 1-5: 10%-50%. 0: SDK optimized, recommended;
 	VBR: Quality of picture. 0: Best; 5: Worst.
*/
int MympiSetLevel( int channel, int val )
{
#if defined MCU_HI3515
	int ret = 0;
	VENC_CHN_ATTR_S stAttr;
	VENC_ATTR_H264_S stH264Attr;
	int vencCh = channel << 1;

	if( channel < 0 || channel > REAL_CHANNEL_NUM || val <  0 || val > 5 )
    {
    	SVPrint( "failed: %s( channel(%d) val(%d) )!\r\n",	__FUNCTION__, channel, val );
    	return -1;
    }

	g_mympiMutex.Lock();

	stAttr.enType = PT_H264;
	stAttr.pValue = &stH264Attr;
	memset( &stH264Attr, 0, sizeof(VENC_ATTR_H264_S) );
	ret = HI_MPI_VENC_GetChnAttr( vencCh, &stAttr );
	if (HI_SUCCESS == ret)
    {
    	stH264Attr.u32PicLevel = val;
    	ret = HI_MPI_VENC_SetChnAttr( vencCh, &stAttr );            
    }



	g_mympiMutex.Unlock();
    
	SVPrint( "ret(0x%X) = %s( channel(%d) val(%d) )!\r\n", ret, __FUNCTION__, channel, val );
    return ret;
#endif	

	return 0;
}

/*
* fn: ���ñ���������
*/
int MympiSetBitrateType( int channel, int val )
{
#if defined MCU_HI3515

	int ret = 0;
	VENC_CHN_ATTR_S stAttr;
	VENC_ATTR_H264_S stH264Attr;
	int vencCh = channel << 1;

	if( channel < 0 || channel > REAL_CHANNEL_NUM || val <  RC_MODE_VBR || val > RC_MODE_FIXQP )
    {
    	SVPrint( "failed: %s( channel(%d) val(%d) )!\r\n",	__FUNCTION__, channel, val );
    	return -1;
    }

	g_mympiMutex.Lock();

	stAttr.enType = PT_H264;
	stAttr.pValue = &stH264Attr;
	memset( &stH264Attr, 0, sizeof(VENC_ATTR_H264_S) );
    
	ret = HI_MPI_VENC_GetChnAttr( vencCh, &stAttr );
	if( HI_SUCCESS == ret )
    {
    	stH264Attr.enRcMode = (RC_MODE_E)val;
    	ret = HI_MPI_VENC_SetChnAttr( vencCh, &stAttr );
    }
    
	g_mympiMutex.Unlock();
    
	SVPrint( "ret(0x%X) = %s( channel(%d) val(%d) )!\r\n", ret, __FUNCTION__, channel, val );
    
	return ret;
#endif
    return 0;
}

/*
* fn: ���ñ�����
*/
int MympiSetBitrate( int channel, int val )
{
#if defined MCU_HI3515

	int ret = 0;
	VENC_CHN_ATTR_S stAttr;
	VENC_ATTR_H264_S stH264Attr;
	int vencCh = channel << 1;

	if( channel < 0 || channel > REAL_CHANNEL_NUM || val <  1 || val > 20000 )
    {
    	SVPrint( "failed: %s( channel(%d) val(%d) )!\r\n",	__FUNCTION__, channel, val );
    	return -1;
    }

	g_mympiMutex.Lock();

	stAttr.enType = PT_H264;
	stAttr.pValue = &stH264Attr;
	memset( &stH264Attr, 0, sizeof(VENC_ATTR_H264_S) );
    
	ret = HI_MPI_VENC_GetChnAttr( vencCh, &stAttr );
	if( HI_SUCCESS == ret )
    {
    	stH264Attr.u32Bitrate = val;
    	ret = HI_MPI_VENC_SetChnAttr( vencCh, &stAttr );
    }
    
	g_mympiMutex.Unlock();
    
	SVPrint( "ret(0x%X) = %s( channel(%d) val(%d) )!\r\n", ret, __FUNCTION__, channel, val );
    
	return ret;
#endif
    return 0;
}


/*
* fn: ����֡����
*/
int MympiSetFramerate( int channel, int val )
{
#if defined MCU_HI3515

	int ret = 0;
	VENC_CHN_ATTR_S stAttr;
	VENC_ATTR_H264_S stH264Attr;
	int vencCh = channel << 1;

	if( channel < 0 || channel > REAL_CHANNEL_NUM || val <	1 || val > 30 )
    {
    	SVPrint( "failed: %s( channel(%d) val(%d) )!\r\n",	__FUNCTION__, channel, val );
    	return -1;
    }
	if( VIDEO_ENCODING_MODE_PAL == VencParamEasyGetVideoStandard() )
    {
    	if( val > 25 )
        {
        	val = 25;
        }
    }

	g_mympiMutex.Lock();

	stAttr.enType = PT_H264;
	stAttr.pValue = &stH264Attr;
	memset( &stH264Attr, 0, sizeof(VENC_ATTR_H264_S) );
    
	ret = HI_MPI_VENC_GetChnAttr( vencCh, &stAttr );
	if( HI_SUCCESS == ret )
    {
    	stH264Attr.u32TargetFramerate     = val;
    	ret = HI_MPI_VENC_SetChnAttr( vencCh, &stAttr );
    }
    
	g_mympiMutex.Unlock();
    
	SVPrint( "ret(0x%X) = %s( channel(%d) val(%d) )!\r\n", ret, __FUNCTION__, channel, val );
    
	return ret;
#endif
    return 0;
}

/*
* fn: ����I ֡���
*/
int MympiSetIframeInterval( int channel, int val )
{
#if defined MCU_HI3515    
	int ret = 0;
	VENC_CHN_ATTR_S stAttr;
	VENC_ATTR_H264_S stH264Attr;
	int vencCh = channel << 1;

	if( channel < 0 || channel > REAL_CHANNEL_NUM || val <	1 || val > 1000 )
    {
    	SVPrint( "failed: %s( channel(%d) val(%d) )!\r\n",	__FUNCTION__, channel, val );
    	return -1;
    }
    
	g_mympiMutex.Lock();

	stAttr.enType = PT_H264;
	stAttr.pValue = &stH264Attr;
	memset( &stH264Attr, 0, sizeof(VENC_ATTR_H264_S) );
    
	ret = HI_MPI_VENC_GetChnAttr( vencCh, &stAttr );
	if( HI_SUCCESS == ret )
    {
    	stH264Attr.u32Gop	= val;
    	ret = HI_MPI_VENC_SetChnAttr( vencCh, &stAttr );
    }
    
	g_mympiMutex.Unlock();
    
	SVPrint( "ret(0x%X) = %s( channel(%d) val(%d) )!\r\n", ret, __FUNCTION__, channel, val );
    
	return ret;
#endif
    return 0;
}

/*
* fn: ���÷ֱ���
	1. ��������Ƶ�����漰����Ƶ�ֱ���ʱ����
	2. ������Ϣ���߶�ʱ��,ִ��������Ƶ�����̵߳Ķ���
	3. ���÷ֱ����漰����Դ�����·���,���Է���Ϣ���������߳�
*/
int MympiSetResolution()
{
	FiEncSendRestartMessage();
	return 0;
}

/*
* fn: ������Ƶ��׼
     1. ��������Ƶ�����漰����Ƶ��ʽʱ����
     2. ������Ϣ���߶�ʱ��,ִ��������Ƶ�����̵߳Ķ���
     3. ������Ƶ��ʽ�漰����Դ�����·���,���Է���Ϣ���������߳�
*/
int MympiSetVideoStandard()
{
	FiEncSendRestartMessage();
	return 0;
}

/*
* fn: ������Ƶ��������
     1. ��������Ƶ�����漰����������ʱ����
     2. ������Ϣ���߶�ʱ��,ִ��������Ƶ�����̵߳Ķ���
     3. �������������Ƶ���벿��,���ܻ�Ӱ�쵽����Ƶͬ��ͨ��,�����������������
*/
int MympiSetAudioEncType()
{
	FiEncSendRestartMessage();
	return 0;
}


