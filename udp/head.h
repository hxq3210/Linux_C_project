/*************************************************************************
    > 文件名称 : head.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月02日21时26分28秒
    > 描   述  : 
*************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<arpa/inet.h>
#include<pthread.h>
/*
struct msg
{
	int id;				//１、消息　２、文件
	int len;			//文件长度
	char name[32];		//文件名称
	char text[256];		//文件内容
};
*/
