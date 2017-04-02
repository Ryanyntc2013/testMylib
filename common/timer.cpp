/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ʵ��һ����ʱ����,����Ϊ ��, ͳ��ʱ��Ϊ���ʱ��
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include "debug.h"
#include "thread.h"
#include "malloc.h"
#include "timer.h"

void ClTimer::FreeTimerList()
{
	pthread_mutex_lock( &m_TimerMutex );
	TIMER_NODE_T *pTimer = NULL;
	while ( m_TimerList != NULL )
    {
    	pTimer = m_TimerList;
    	m_TimerList = m_TimerList->next;
    	Free( pTimer );
    }
	pthread_mutex_unlock( &m_TimerMutex );    
}

void ClTimer::InsertTimerList( TIMER_NODE_T *pTimer )
{
	pthread_mutex_lock( &m_TimerMutex );
	pTimer->next = m_TimerList;
	m_TimerList = pTimer;
	pthread_mutex_unlock( &m_TimerMutex );    
}

void ClTimer::WaitTimerThreadQuit()
{
	m_TimerQuit	= 1;
	ThreadJoin( m_TimerThreadID, NULL );
}

inline unsigned ClTimer::GetInterval( unsigned interval )
{
	return interval * m_Precision / m_SleepTime;
}

inline unsigned ClTimer::UpdateElapse( unsigned elapse )
{
	return elapse + 1;
}

inline unsigned ClTimer::UpdateTimes( unsigned times, unsigned interval )
{
	return interval;
}

void ClTimer::ExeTimer()
{
	TIMER_NODE_T *pCurTimer;
	if ( m_TimerList != NULL )  // ˫����
    {
    	pthread_mutex_lock( &m_TimerMutex );
    	if ( m_TimerList != NULL )
        {
        	pCurTimer = m_TimerList;

        	while ( NULL != pCurTimer )
            {
            	pCurTimer->elapse = UpdateElapse( pCurTimer->elapse );
            	if ( pCurTimer->elapse >= pCurTimer->interval )  // ��ʱ������
                {
                    ( *(pCurTimer->fun) )( pCurTimer->arg );  // ִ�лص�����	                
                	pCurTimer->elapse = 0;
                }
                
            	pCurTimer = pCurTimer->next;
            }
        }    
    	pthread_mutex_unlock( &m_TimerMutex );
    }
}

void *ClTimer::TimerThread( void *args )
{
	if ( args != NULL )
    {
    	ClTimer *pThis = ( ClTimer* )args;
    	pThis->TimerProcess();
    }
	return NULL;
}

void *ClTimer::TimerProcess()
{
	int uSleepTime = (m_SleepTime - 1) * 1000;
	while ( !m_TimerQuit )
    {
    	ExeTimer();
    	usleep( uSleepTime );
    }
	return NULL;
}

/*
* fn: ������ʱ���߳�
* precision: ����, TIMER_PRECISION_MS or TIMER_PRECISION_SEC
*/
int ClTimer::Create( int precision )
{    
	if ( m_TimerThread != 0 ) // ����̴߳����ɹ���ֻ�����ʼ��һ��
    {
    	pthread_mutex_init( &m_TimerMutex, NULL );
    	if ( precision == TIMER_PRECISION_MS )
        {
        	m_Precision	= precision;
        	m_SleepTime	= 10;
        }
    	m_TimerThread = ThreadCreateCommonPriority( &m_TimerThreadID, TimerThread, this ); 
                                            
    	if ( m_TimerThread != 0 ) Print( "sys_init_timer create thread failed !\r\n" );
    }
	return m_TimerThread;
}

int ClTimer::Destroy()
{
	int nRet = -1;
	if ( m_TimerThread == 0 )
    {
    	m_TimerThread = -1;
    	WaitTimerThreadQuit();        
    	FreeTimerList();
    	pthread_mutex_destroy( &m_TimerMutex );
    	nRet = 0;
    }
	return nRet;
}

/*
* fn: ���ָ��ID�ŵĶ�ʱ��
* fun: ��ʱ���ص�����
* arg: ��ʱ���ص���������
* second: ����ÿ��������ִ��һ��
* timerId: out,��ʱ���ڵ�ID,�����������ҵ��Ѿ�add �Ķ�ʱ���ڵ�
* !!!ע��: 1. �ص�����fun�в����ٴε��ö�ʱ���еĽӿں���, ������������ !!!
            ( Init(), Destroy(), Add(...), Delete(id) )
           2. ����ص�����������,��Ҫ����	
*/
int ClTimer::Add( TIMER_CMD fun, void *arg, unsigned second, unsigned int *timerId )
{
	int nRet = -1;
    
	if ( m_TimerThread == 0 )
    {
    	TIMER_NODE_T *pTimer = ( TIMER_NODE_T * )Malloc( sizeof(TIMER_NODE_T) );
    	if ( pTimer != NULL )
        {                
        	pTimer->id	        = GetTimerID();
        	pTimer->interval	= GetInterval( second );
        	pTimer->elapse	    = 0;
        	pTimer->fun	        = fun;
        	pTimer->arg	        = arg;
        	pTimer->next	    = NULL;

        	if( NULL != timerId )
            {
                *timerId = pTimer->id;
            }
            
        	InsertTimerList( pTimer );
        	nRet = 0;
        }
    }
	return nRet;
}

unsigned ClTimer::GetTimerID()
{
	unsigned     	timerID	    = 0;
	TIMER_NODE_T *	pTimer	    = NULL;
	int	        	existFlag	= 0;
    
	pthread_mutex_lock( &m_TimerMutex );
	while ( 1 )
    {
        ++m_TimerID;
    	for ( pTimer = m_TimerList;
              pTimer != NULL;
              pTimer = pTimer->next )
        {
        	if ( m_TimerID == pTimer->id )
            {
            	existFlag = 1;
            	break;
            }
        }
    	if( 1 == existFlag )
        {
        	existFlag = 0;
        	continue;
        }
        
    	break;
    }
	timerID = m_TimerID;
	pthread_mutex_unlock( &m_TimerMutex );
	return timerID;
}

int ClTimer::Delete( unsigned timerId )
{
	int nRet = -1;
	pthread_mutex_lock( &m_TimerMutex );
	if ( m_TimerList != NULL )
    {    
    	TIMER_NODE_T *pTimer = m_TimerList;
    	if ( pTimer->id == timerId )
        {
        	m_TimerList = pTimer->next;
        	Free( pTimer );
        	nRet = 0;
        }
    	else
        {
        	TIMER_NODE_T *pPreTimer = m_TimerList;
        	TIMER_NODE_T *pCurTimer = pPreTimer->next;
        	while( pCurTimer != NULL )
            {
            	if ( pCurTimer->id == timerId )
                {
                	pPreTimer->next = pCurTimer->next;
                	Free( pCurTimer ); 
                	nRet = 0;
                	break;
                }

            	pPreTimer = pCurTimer;
            	pCurTimer = pPreTimer->next;
            }
        }
    }
	pthread_mutex_unlock( &m_TimerMutex );
	return nRet;
}


/* ===== ��װ�ⲿ�ӿ� ===== */
static ClTimer	s_SysRelativeTimer;
int CreateRTimer( int precision )
{
	return s_SysRelativeTimer.Create( precision );
}

int AddRTimer( TIMER_CMD fun, void * arg, unsigned interval )
{
	return s_SysRelativeTimer.Add( fun, arg, interval, NULL );
}

int AddRTimer( TIMER_CMD fun, void * arg, unsigned interval, unsigned int *timerId )
{
	return s_SysRelativeTimer.Add( fun, arg, interval, timerId );
}

int DestroyRTimer()
{
	return s_SysRelativeTimer.Destroy();
}

int DeleteRTimer( unsigned timerId )
{
	return s_SysRelativeTimer.Delete( timerId );
}

