#ifndef __PROCONAPP_H__
#define __PROCONAPP_H__

#define MAX_JPG_DATA_NODE	    10
#define MAX_H264_DATA_NODE	    (16 << 1)//(32<<1)//    // ��������Ƶͬ��
#define MAX_MD_DATA_NODE	    8
#define MAX_IPC_SNAP_DATA_NODE	5
#define MAX_IPC_SNAP_DATA_SIZE	(512 * 1024) // 512 KBytes ��1080p ͼƬ
#define MAX_RECORD_DATA_NODE	8
#define MAX_RECORD_DATA_SIZE	(512 * 1024) // 512 KBytes дһ�δ���
#define MAX_YUV_DATA_NODE		8
#define MAX_YUV_DATA_SIZE	    (720 * 576 * 2) // һ֡YUV����


void ProconInit();

#endif

