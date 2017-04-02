#ifndef __TIMER_H__
#define __TIMER_H__

#include <pthread.h>

// ��ʱ��ʱ�侫��: ����/��
#define	TIMER_PRECISION_MS		1
#define	TIMER_PRECISION_SEC		1000  

typedef void * (*TIMER_CMD)( void * );

typedef struct timerNode
{
	unsigned 	id;            // ��ʱ���ڵ�id,��ɾ��ĳ����ʱ���ڵ��ʱ���õ�
	unsigned 	interval;    // ÿ���೤ʱ��ִ��һ�κ���,��λ(����)
	unsigned	elapse;        // ϵͳ���ϴ�ִ���꺯�����߹��˶��ٴ�
	TIMER_CMD	fun;        // �ص�����
	void *    	arg;        // �ص������Ĳ���
	struct timerNode *next;    
} TIMER_NODE_T;

class ClTimer
{
public:
	ClTimer(): m_TimerList( NULL ), m_TimerThread( -1 ), m_TimerQuit( 0 ),
        	m_Precision( TIMER_PRECISION_SEC ),	m_SleepTime( 100 ) { }
    ~ClTimer() { }
    
	int Create( int precision = TIMER_PRECISION_SEC );    
	int Destroy();    
	int Add( TIMER_CMD fun, void *arg,  unsigned interval, unsigned *timerId );    
	int Delete( unsigned timerId );

private:
	void FreeTimerList();
	void InsertTimerList( TIMER_NODE_T *pTimer );
	void WaitTimerThreadQuit();
	unsigned GetInterval( unsigned interval );
	unsigned UpdateElapse( unsigned elapse );
	unsigned UpdateTimes( unsigned times, unsigned interval );
	void ExeTimer();
	static void *TimerThread( void *arg );
	void *TimerProcess();
	unsigned GetTimerID();

private:
	TIMER_NODE_T *m_TimerList;
	int	m_TimerThread;
	int	m_TimerQuit;
	int	m_Precision;
	int	m_SleepTime;
	unsigned int m_TimerID;
	pthread_t m_TimerThreadID;
	pthread_mutex_t m_TimerMutex;
};

#define CTimer ClTimer

int CreateRTimer( int precision );
int AddRTimer( TIMER_CMD fun, void *arg, unsigned interval );
int AddRTimer( TIMER_CMD fun, void * arg, unsigned interval, unsigned int *timerId );
int DestroyRTimer();
int DeleteRTimer( unsigned timerId );

#endif	


