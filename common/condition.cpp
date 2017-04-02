/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ��װ������������, ClCondition �� CCondition ��������
	ClCondition: ����
	CCondition: ������
********************************************************************************/

#include "condition.h" 

static void Pthread_mutex_unlock( void *arg )
{
	pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
	pthread_mutex_unlock( mutex );
}

ClCondition::ClCondition()
{
	pthread_mutex_init( &m_mutex, NULL );
	pthread_cond_init( &m_cond, NULL );        
}

ClCondition::~ClCondition()
{        
	pthread_cond_destroy( &m_cond );
	pthread_mutex_destroy( &m_mutex );
}

/********************************************************************************
sven explain:
  1. pthread_cond_wait ��������ǰ unlock m_mutex, ���غ��lock m_mutex,
  2. ���û�� pthread_cleanup_pop( 1 )(�ص�)Pthread_mutex_unlock(m_mutex),��ô���߳�ʱ�п����������
  3. pthread_cleanup_push Ŀ����Ϊ�˷�ֹ�߳���pthread_cond_wait ��ʱ�������̸߳ɵ����������
  4. pthread_mutex_lock �� pthread_cleanup_pop( 1 )(�ص�)Pthread_mutex_unlock(m_mutex)���ʹ��
*******************************************************************************/
void ClCondition::Wait()
{
	pthread_mutex_lock( &m_mutex );    
	pthread_cleanup_push( Pthread_mutex_unlock, (void *)&m_mutex );
	pthread_cond_wait( &m_cond, &m_mutex );            
	pthread_cleanup_pop( 1 );
}

void ClCondition::Signal()
{
	pthread_mutex_lock( &m_mutex );
	pthread_cond_signal( &m_cond );
	pthread_mutex_unlock( &m_mutex );
}

void ClCondition::Broadcast()
{
	pthread_mutex_lock( &m_mutex );
	pthread_cond_broadcast( &m_cond );
	pthread_mutex_unlock( &m_mutex );
}


