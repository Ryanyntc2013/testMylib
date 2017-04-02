/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.01.17
**  description  : ��װepoll��غ���,ʹ�ñ�����ǰ��鿴��ǰ�ں˰汾�Ƿ�֧��epoll
********************************************************************************/

#ifndef __EPOLLW_H__
#define __EPOLLW_H__

#include <sys/epoll.h>

int EpollCreat( int size );
int EpollClose( int epfd );
int EpollCtl( int epfd, int op, int fd, struct epoll_event *event );
int EpollWait( int epfd, struct epoll_event *events, int maxevents, int timeout );

/* ===== ���������Լ��ķ�װ ===== */
int EpollCtlAdd( int epfd, int sockfd, uint events );
int EpollCtlDel( int epfd, int sockfd, uint events );
int EpollCtlMod( int epfd, int sockfd, uint events );


// ������Щ�ꡢ���Ͷ���<sys/epoll.h>�ж���,�����������Ϊ��ʶ�𷽱�
#ifdef _sven_EPOLLW_ 
typedef union epoll_data 
{
    void *ptr;
    int fd;                // ��Ҫepoll��fd
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;
struct epoll_event 
{
    __uint32_t events;      /* Epoll events,������ EPOLL*** �Ļ���� */
    epoll_data_t data;      /* User data variable */
};

// epoll �¼�
#define EPOLLIN         //��ʾ��Ӧ���ļ����������Զ��������Զ�SOCKET�����رգ���
#define EPOLLOUT	    //��ʾ��Ӧ���ļ�����������д��
#define EPOLLPRI	    //��ʾ��Ӧ���ļ��������н��������ݿɶ�������Ӧ�ñ�ʾ�д������ݵ�������
#define EPOLLERR	    //��ʾ��Ӧ���ļ���������������
#define EPOLLHUP	    //��ʾ��Ӧ���ļ����������Ҷϣ�
#define EPOLLET	        //��#define EPOLL��Ϊ��Ե����(Edge Triggered)ģʽ�����������ˮƽ����(Level Triggered)��˵�ġ�
#define EPOLLONESHOT	//ֻ����һ���¼���������������¼�֮���������Ҫ�����������

/* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
#define EPOLL_CTL_ADD 1	/* Add a file decriptor to the interface.  */
#define EPOLL_CTL_DEL 2	/* Remove a file decriptor from the interface.  */
#define EPOLL_CTL_MOD 3	/* Change file decriptor epoll_event structure.  */

int epoll_create( int size );
int epoll_ctl( int epfd, int op, int fd, struct epoll_event *event );
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
#endif 

#endif 

