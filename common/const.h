#ifndef __CONST_H__
#define __CONST_H__

typedef unsigned int 	uint;
typedef unsigned char 	uchar;
typedef unsigned short  ushort;  
typedef  char         	sharechar; // �û�ShareMalloc
typedef unsigned long long uint64_t;

#define	FI_SUCCESS	        	0	// �ɹ�
#define	FI_FAIL	                (-1)    // ʧ��
#define FI_SUCCESSFUL         	FI_SUCCESS
#define FI_FAILED	        	FI_FAIL
#define	FI_TRUE	            	1	// ��
#define	FI_FALSE	        	0	// ��

#define NET_ADDRSIZE         	20	    // "192.168.188.168" ��20��bytes;"00:AB:BB:CC:BA:00" ��18���ֽ�
#define MAX_PATH_LEVEL	    	20	    // ���Ŀ¼����
#define COM_BUF_SIZE         	256	    // ����buf ��С
#define MAX_CHANNEL_NUM	    	16	    // ���ͨ����
#define DATETIME_LEN	    	20	    // "2013-11-18 10:20:28" �ĳ���
#define DATE_LEN	        	12	    // "2013-11-18" �ĳ���
#define TIME_LEN	        	12	    // "10:20:28" �ĳ���
#define NORMAL_USER_NAME_LEN	32      // һ���û����ĳ���
#define NORMAL_PASSWD_LEN		32      // һ������ĳ���
#define NORMAL_URL_LEN	    	128     // һ�������ĳ���
#define MAX_WEEK_DAY	    	7       //һ����7��
#define MAX_DAY_TIME_SEG		4	    //һ���ṩ�ĸ�ʱ���ѡ��
#define MAX_RECORD	            4
#define NORMAL_FILENAME_LEN		80	//

#define REAL_CHANNEL_NUM		4
#define CHANNEL_ENC_STREAM_NUM  2//ÿ��ͨ���ı�����������

#define MAX_VENC_CHN_NUM (REAL_CHANNEL_NUM*2)
#define MAX_AENC_CHN_NUM  REAL_CHANNEL_NUM
#define MAX_ENC_CHN_NUM  (MAX_VENC_CHN_NUM+MAX_AENC_CHN_NUM)
#endif  

