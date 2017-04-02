/********************************************************************************
**	Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**	author        :  sven
**	version       :  v1.0
**	date           :  2013.10.10
**	description  : �����̳߳ؽӿ�
********************************************************************************/

#include <string.h>

#include "debug.h"
#include "thread.h"
#include "malloc.h"
#include "threadPool.h"

/***********************************************************************
* fn: �����̳߳�
* priority,���ȼ�, Ϊ�̳߳���ÿ���̵߳����ȼ�
* threadNum, �̳߳�, Ϊ�̳߳����̸߳���
************************************************************************/
int ClThreadPool::Create( int threadNum ) 
{
	m_MaxThreadNum = threadNum;
	m_ThreadID = ( pthread_t * )Malloc( sizeof(pthread_t)*m_MaxThreadNum );
	if ( m_ThreadID == NULL ) return -1;
    
	pthread_mutex_init( &m_MutexThread, NULL );
	pthread_cond_init( &m_CondThread, NULL );
	for ( int i = 0; i < m_MaxThreadNum; ++i )
    {
    	ThreadCreate( &m_ThreadID[i], ThreadProcess, this );
    }
	return 0;
}

/*******************************************************************************
* fn: ��Ҫ����ĺ�����ӵ��̳߳�
* fun: Ҫ����ĺ���
* args: fun Ҫ�õ��Ĳ���,����ָ������ݽ��ᱻ����,���������ָ���, add ���ǵ��ͷ�
* argsSize: args ��ָ��ؼ�����˶�����������
* ����: Add ���������malloc �ռ�,Ȼ���args �������copy ���ÿռ�, ���ÿռ���ͷ�ʱ��
        ���ں�����ִ�����,��void ClThreadPool::ThreadRoutine(), �����ͷ�,��˶���
        THREAD_FUN fun ʵ�庯����ʱ��,���ܹ�������free args��
*********************************************************************************/
int ClThreadPool::Add( THREAD_FUN fun, void *args, int argsSize ) 
{ 
	WORK_NODE_T *worker;
#if 0 // �û�û�����ü����������ȴ�,���Բ�����
	if( m_WorkQueueSize == m_MaxThreadNum )
    {
    	SVPrint( "ThreadPool add error: m_WorkQueueSize(%d) == m_MaxThreadNum(%d)!\r\n", 
                                                    	m_WorkQueueSize, m_MaxThreadNum );
    	return -1;        
    }
#endif
	worker = NewWork( fun, args, argsSize );
	if ( worker == NULL ) return -1;

	pthread_mutex_lock( &m_MutexThread );    
	if ( m_WorkQueueRear == NULL )
    {
    	m_WorkQueueFront = worker;
    	m_WorkQueueRear = worker;
    }
	else
    {
    	m_WorkQueueRear->next = worker;
    	m_WorkQueueRear = worker;
    }
    ++m_WorkQueueSize;
	pthread_mutex_unlock( &m_MutexThread );
	pthread_cond_signal( &m_CondThread );

    return 0;
}

int ClThreadPool::Destroy()
{
	if ( m_Shutdown || m_ThreadID == NULL ) return -1;

	m_Shutdown = true;
	pthread_cond_broadcast( &m_CondThread );
	for ( int i = 0; i < m_MaxThreadNum; ++i )
    {
    	ThreadJoin( m_ThreadID[i], NULL );
    	Print( "Thread %d is quit to work !\r\n", m_ThreadID[i] );
    }

	m_MaxThreadNum = 0;
	Free( m_ThreadID );
    
	WORK_NODE_T *worker = NULL;
	while ( m_WorkQueueFront != NULL )
    {
    	worker = m_WorkQueueFront;
    	m_WorkQueueFront = worker->next;
    	Free ( worker );
    }
	m_WorkQueueRear = NULL;
	m_WorkQueueSize = 0;
	pthread_mutex_destroy( &m_MutexThread );
	pthread_cond_destroy( &m_CondThread );
	return 0;
}

void *ClThreadPool::ThreadProcess( void *args )
{
	if ( args != NULL )
    {
    	ClThreadPool *pThis = ( ClThreadPool * )args;
    	pThis->ThreadRoutine();
    }
	return NULL;
}

void ClThreadPool::ThreadRoutine()
{
    while ( 1 )
    {
    	pthread_mutex_lock( &m_MutexThread );    
    	while ( m_WorkQueueSize == 0 && !m_Shutdown )
        {
            //Print( "Thread %u is waiting !\r\n", ThreadSelf() );
        	pthread_cond_wait( &m_CondThread, &m_MutexThread );
        }
    	if ( m_Shutdown )
        {
        	pthread_mutex_unlock( &m_MutexThread );
            //Print( "Thread %d will quit !\r\n", ThreadSelf() );
        	break; //  while ( 1 )
        }
    	Print( "Thread %d is starting to work !\r\n", ThreadSelf() );        
        
    	WORK_NODE_T *worker     = m_WorkQueueFront;
    	m_WorkQueueFront     = worker->next;
        --m_WorkQueueSize;
    	if ( m_WorkQueueSize == 0 )	m_WorkQueueRear = NULL;
    	pthread_mutex_unlock( &m_MutexThread );

        (*(worker->fun))( worker->args );
        
    	Free( worker->args );
    	Free( worker );
    }
}

WORK_NODE_T *ClThreadPool::NewWork( THREAD_FUN fun, void *args, int argsSize )
{
	WORK_NODE_T *pResult = NULL;
	WORK_NODE_T *worker = ( WORK_NODE_T* )Malloc( sizeof(WORK_NODE_T) );
	if ( worker != NULL )
    {
    	worker->next     = NULL;
    	worker->fun     = fun;
    	worker->args     = (void *)Malloc( argsSize );
    	if( NULL != worker->args )
        {
        	memcpy(worker->args, args, argsSize);
        	pResult = worker;
        }    
    	else
        {
        	Free(worker);
        }
    }
    
	return pResult;
}

