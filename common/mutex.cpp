/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ��װ socketͨ�� ��غ���
********************************************************************************/

#include "mutex.h"

/* ===== ����ͨ���ķ�װ ===== */
ClMutexLock::ClMutexLock()
{
	pthread_mutex_init( &m_mutex, NULL );
}

ClMutexLock::~ClMutexLock()
{
	pthread_mutex_destroy( &m_mutex );
}

void ClMutexLock::Lock()
{
	pthread_mutex_lock( &m_mutex );
}

int ClMutexLock::Trylock()
{
	return pthread_mutex_trylock( &m_mutex );
}

void ClMutexLock::Unlock()
{
	pthread_mutex_unlock( &m_mutex );
}

pthread_mutex_t *ClMutexLock::GetMutex()
{
	return &m_mutex;
}

/* ===== end ����ͨ���ķ�װ ===== */

/* ===== �Զ�д���ķ�װ ===== */
CRwLock::CRwLock()
{  
    pthread_rwlock_init( &m_rwl, NULL );         
}  
  
CRwLock::~CRwLock()
{  
    pthread_rwlock_destroy( &m_rwl );  
}  
  
void CRwLock::ReadLock()
{  
    pthread_rwlock_rdlock( &m_rwl );   
}   
  
void CRwLock::WriteLock()
{  
    pthread_rwlock_wrlock( &m_rwl );  
}    
 
void CRwLock::Unlock()
{  
    pthread_rwlock_unlock( &m_rwl );
}

/* ===== end �Զ�д���ķ�װ ===== */

CMutexLockRecursive::CMutexLockRecursive()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init( &attr );
	pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE_NP );
	pthread_mutex_init( &m_mutex, &attr );
	pthread_mutexattr_destroy( &attr );
}

CMutexLockRecursive::~CMutexLockRecursive()
{
	pthread_mutex_destroy( &m_mutex );
}

void CMutexLockRecursive::Lock()
{
	pthread_mutex_lock( &m_mutex );
}

void CMutexLockRecursive::Unlock()
{
	pthread_mutex_unlock( &m_mutex );
}

pthread_mutex_t *CMutexLockRecursive::GetMutex()
{
	return &m_mutex;
}

