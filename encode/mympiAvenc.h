#ifndef __MYMPIAVENC_H__
#define __MYMPIAVENC_H__
#if defined MCU_HI3515



#if defined MCU_HI3515
#include "hi_comm_avenc.h"
#endif
#include "thread.h"

typedef struct _AudioFlag_
{
	int  operateFlag;    // ������־, 1 ��ʾ�б��޸Ĺ�
	uint val;             // 0,�ر���Ƶ(������Ƶ��); 1,������Ƶ(����Ƶ��)
} AUDIO_FLAG_T;

typedef struct _AvencSt_
{
	pthread_t threadId;
	int  runFlag;
	AUDIO_FLAG_T	 avChange;    // ����Ƶ������ı���
	AVENC_CHN          AVChnId;    // ͨ��
	AVENC_OPERATE_OBJECT_E enObject;
} AVENC_ST;

#ifdef __cplusplus
extern "C"{
#endif

int MympiAvencStart();
int MympiAvencStop();

#ifdef __cplusplus
}
#endif


#endif //#if defined MCU_HI3515A do not use now
#endif // __MYMPIAVENC_H__

