#ifndef _HASH_MESSAGE_H
#define _HASH_MESSAGE_H

#include "mutex.h"

#define MAX_NODE 20000
#define MAX_MUTEX 40

typedef enum _Message_
{
	MSG_ID_WRITE_FLASH = 1001,
	MSG_ID_CALCULATE_HDD_SIZE,
	MSG_ID_TIMER_WRITE_SYS_CONFIG,
	MSG_ID_ALARM_WAIT_LINKAGE_THREAD,
	MSG_ID_IO_ALARM_PARAM_CHANGE,    
    
	MSG_ID_DEAL_RTP_SEND_THREAD,
	MSG_ID_DEAL_AV_SEND_THREAD,
	MSG_ID_DEAL_MESSAGE_DATA_THREAD,
	MSG_ID_ALARM_MORE_THAN_LIMIT,
	MSG_ID_DEAL_TALKBACK_THREAD,
    
	MSG_ID_DEAL_TALKBACK_RECV_THREAD,
	MSG_ID_DEAL_TALKBACK_SEND_THREAD,
	MSG_ID_RESTART_NTP,
	MSG_ID_RESTART_ENC_MODEL,    
	MSG_ID_FTP_JPG_THREAD,
    
	MSG_ID_SNAP,
	MSG_ID_ICMP_APP,
	MSG_ID_DTU_APP,
	MSG_ID_MD_PARAM_CHANGE,
	Msg_ID_MD_ALARM_PARAM_CHANGE,

	MSG_ID_DTU_HYALINE,
    MSG_ID_TIMER_WRITE_SYS_LOG,  //myf 130409 1020
    MSG_ID_SYS_UPDATE,  //myf 130508 1448
    MSG_ID_SYS_UPDATE_PRO,  //myf 130508 1448
	MSG_ID_DCP_SIGNAL,

	MSG_ID_VLOSS_ALARM_PARAM_CHANGE,  //add by jerry  20130531
	MSG_ID_SHELTER_ALARM_PARAM_CHANGE,  //add by jerry  20130531
    MSG_ID_NETWORK_CHANGE,      // ���ڸı������ַ��, ���������紫����ص��߳�
    MSG_ID_REBOOT,              // ��������linux ϵͳ.
} MSG_ID_EN;

typedef struct msgNode
{
	int		msgId;
	int		msgLen;
	char *	msgBuf;
    
	struct msgNode * next;
    
} MSG_NODE;


// ר����������ָ���͵�����
typedef struct _MsgCmd_
{
	unsigned int 	cmd;            // ָ��
	unsigned int 	dataLen;        // ���ݳ���, �����̻߳��õ�,���������ת��ָ��,��ô��ָ��ת�����ݵĳ���
	unsigned short	index;            // ���������̷߳���ָ���ʱ��,ָ���������ĸ��û�
	char	    	unused[2];        // ����
	char             *pData;            // ��ָ���Ӧ������
} MSG_CMD_T;

class CMessage
{
public:
	CMessage();
    ~CMessage();    
	int Send( int msgId, char* msgBuf, int msgLen );    
	int Recv( int msgId, char* msgBuf, int msgLen );
	bool Find( int msgId );

private:
	MSG_NODE *m_Node[MAX_NODE];
	ClMutexLock m_Mutex[MAX_MUTEX];
	void FreeNode( MSG_NODE* pNode );
	int GetNodeIndex( int msgId );
	int GetMutexIndex( int msgId );
};

int MessageSend( int nMsgId, char* pMsgBuf = NULL, int nMsgLen = 0 );
int MessageRecv( int nMsgId, char* pMsgBuf = NULL, int nMsgLen = 0 );
bool MessageFind( int nMsgId );

#endif 

