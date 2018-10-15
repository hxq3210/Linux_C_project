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
#include<sqlite3.h>
#include<signal.h>
#include<time.h>
#include<sys/wait.h>
#define DATABASE "./test.db"


typedef struct
{
    int type;
    char name[128];
    char data[256];   // password or word
}MSG;
