#ifndef __MPIVIFRAME_H__
#define __MPIVIFRAME_H__

#include <pthread.h>



typedef struct _ShelterDetect_
{
	uchar shelterStat;  // 0:���ڵ�    1:���ڵ�
	uchar shelterCnt;  //��⵽����֡��Ч������Ϊ���ڵ�
	uchar noShelterCnt;  //��⵽����֡��Ч������Ϊȡ���ڵ�
	uchar reserved[1];
}SHELTER_DETECT_T;


typedef struct _ViFrameSt_
{
	pthread_t threadId;
	int  runFlag;
} ShelterThreadStatus_t;


typedef struct _ShelterSensitivity_
{
	uint rowDotNum;      // ÿ�в�������
	int  frameNum;         //������֡��������Ϊ���ڵ�
	int  variance;      //����
} SHELTER_SENSITIVITY_T;

void StartViFrameThread();//do not use in HI3515A
void StopViFrameThread();//do not use in HI3515A

void StartOdThread();
void StopOdThread();
int VideoGetShelterDetect( int channel );

#endif // __MPIVIFRAME_H__

