/********************************************************************************
**  Copyright (c) 2013, �����ж��������Զ������޹�˾, All rights reserved.
**  author        :  sven
**  version       :  v1.0
**  date           :  2013.10.10
**  description  : ���������
********************************************************************************/

#include <stdlib.h>
#include <sys/time.h>

/***********************************************
* fn: ����һ�������
************************************************/
int RandInt()
{
	struct timeval tv;
	gettimeofday( &tv, NULL );
	unsigned int seed = tv.tv_sec ^ tv.tv_usec;
	return rand_r( &seed );
}

/****************************************************
* fn: ����һ�������n, a <= n <= b;
*****************************************************/
int RandAb( int a, int b )
{
	struct  timeval tv;

	gettimeofday(&tv, NULL);
	srand(tv.tv_usec);
    
	return( a + (int)((double)(b-a+1)*rand()/(RAND_MAX*1.0)));
}

