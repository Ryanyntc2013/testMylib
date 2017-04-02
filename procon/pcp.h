#ifndef __PCP_H__
#define __PCP_H__

#include <pthread.h>
#include "const.h"
#include "mutex.h"
#include "ttypes.h"

#define	MAX_PCP_DATA_NODE		16	// һ��ͨ����໺��16 ���ڵ�
#define ASSUME_CONSUMER_SIZE	1	// �ٶ���2 �������������ٶȱȽ���,��֤��8 �����õĽڵ�

typedef struct _PcpHead_
{
	int users;        // ��ǰ�ж��ٸ��û�����ʹ�øýڵ�
	int channel;    // ���ڵ�������������ĸ�ͨ����
	int type;        // ��������,DATA_TYPE_EN �е�����һ��
	int len;        // �ڵ����ݵĴ�С	
} PCP_HEAD_T;

typedef struct _PcpNode_
{
	PCP_HEAD_T         	pcpHead;
	struct _PcpNode_     *next;
	char             	data[1];
} PCP_NODE_T;

typedef struct _PcpSt_
{
	int	            	writePos;
	pthread_mutex_t		dataMutex;
	PCP_NODE_T	        *dataPool[MAX_PCP_DATA_NODE];
} PCP_T;

typedef struct PcpReadSt
{
	int flag;
	int channel;
	int readBegin;
	int readEnd;
} PCP_READ_T;

typedef struct PcpWriteSt
{
	int flag;
	int channel;
} PCP_WRITE_T;

typedef struct _PcpPool_
{
	PCP_NODE_T *head;
	PCP_NODE_T *tail;
} PCP_POOL_T;

class CPcp
{
public:    
	CPcp( int blockFlag = BLOCK_NO, int dataType = DATA_TYPE_NOMAL );
    ~CPcp();    
	void Init( int chNum, int dataNode, uint maxSize );
	uint Open( int channel, int flag );
	void Close( uint fd );
	PCP_NODE_T *Read( uint fd );
	int Write( uint fd, DATA_PIECE_T proDataInfo );    
	int Write( uint fd, PCP_NODE_T *pExNode );
	void Tfree( PCP_NODE_T *pcpNode );    
	PCP_NODE_T *Talloc( int channel );    
private:    
	PCP_NODE_T *Tcopy( PCP_NODE_T *pcpNode );
	int GetWritePos( int channel );    
private:
	PCP_T *m_pcp;
	int	m_chNum;
	int	m_dataType;
	int m_blockFlag;
	int m_dataNode;
	uint m_maxPcpDataNodeSize;
	PCP_POOL_T *m_pool;     // producer list, ��������
	ClMutexLock m_lock;
};

#endif

