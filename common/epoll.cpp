/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.01.17
**  description  : ��װ(wrap)epoll��غ���,
              ʹ�ñ�����ǰ��鿴��ǰ�ں˰汾�Ƿ�֧��epoll.
********************************************************************************/
#include <unistd.h>
#include <string.h>
#include "epoll.h" 

/*******************************************************************************
* fn: ����һ��epoll
* size: ���ֵ
* ����: 0 or -1
********************************************************************************/
int EpollCreat( int size )
{
	int ret;

	ret = epoll_create( size );
    
	return ret;
}

/*******************************************************************************
* fn: �ر�һ��epoll
* epfd: EpollCreat ���ص�ֵ
*******************************************************************************/
int EpollClose( int epfd )
{
	int ret;

	ret = close( epfd );
    
	return ret;
}

/********************************************************************************
* fn: ����epfd ��fd �Ĳ���
* epfd: EpollCreat ���ص�ֵ
* op: EPOLL_CTL_*** �е�����һ��
* fd: ����ӵ�fd
* event: ��Ҫ��fd�����Щ�¼�
* ����: 0 or -1
********************************************************************************/
int EpollCtl( int epfd, int op, int fd, struct epoll_event *event )
{
	int ret;

	ret = epoll_ctl( epfd, op, fd, event );
    
	return ret;
}

/********************************************************************************
* fn: epoll �ȴ�
* epfd: EpollCreat ���ص�ֵ
* events: out, ͨ��Ϊһ������,��С���Ϊ20
* maxevents: ����¼���
* timeout: �ȴ���ʱ��(����);-1,��ʾ�����ڵȴ�;0,��ʾ���ȴ�
* ����:0,û��socket׼����; > 0, �����Ѿ�׼�����˵�socket����Ŀ; -1,����
*********************************************************************************/
int EpollWait( int epfd, struct epoll_event *events, int maxevents, int timeout )
{
	int ret;

	ret = epoll_wait( epfd, events, maxevents, timeout );
    
	return ret;
}

/* ===== ���������Լ��ķ�װ ===== */
/*******************************************************************************
* fn: ����epfd ��fd ��add ����
* epfd: EpollCreat ���ص�ֵ
* fd: �����Ƶ�fd
* events: ��Ҫ��fd ������Щ�¼�
* ����: 0 or -1
********************************************************************************/
int EpollCtlAdd( int epfd, int sockfd, uint events )
{
	int ret;
	struct epoll_event ev = { 0 };
    
	ev.data.fd     = sockfd;
	ev.events     = events;
	ret = EpollCtl( epfd, EPOLL_CTL_ADD, sockfd, &ev );
    
	return ret;
}

/*******************************************************************************
* fn: ����epfd ��fd ��del ����
* epfd: EpollCreat ���ص�ֵ
* fd: �����Ƶ�fd
* events: ��Ҫ��fd ������Щ�¼�
* ����: 0 or -1
*******************************************************************************/
int EpollCtlDel( int epfd, int sockfd, uint events )
{
	int ret;    
	struct epoll_event ev = { 0 };    
    
	ev.data.fd     = sockfd;
	ev.events     = events;
	ret = EpollCtl( epfd, EPOLL_CTL_DEL, sockfd, &ev );
    
	return ret;
}

/******************************************************************************
* fn: ����epfd ��fd ��modify ����
* epfd: EpollCreat ���ص�ֵ
* fd: �����Ƶ�fd
* events: ��Ҫ��fd ������Щ�¼�
* ����: 0 or -1
******************************************************************************/
int EpollCtlMod( int epfd, int sockfd, uint events )
{
	int ret;
	static struct epoll_event ev;    
    
	ev.data.fd     = sockfd;
	ev.events     = events;
	ret = EpollCtl( epfd, EPOLL_CTL_MOD, sockfd, &ev );

	return ret;
}

