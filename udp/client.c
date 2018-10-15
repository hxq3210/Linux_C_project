/*************************************************************************
    > 文件名称 : client.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月03日19时24分56秒
    > 描   述  : 
*************************************************************************/
#include <stdio.h>   
#include <arpa/inet.h>  //inet_addr htons
#include <sys/types.h>
#include <sys/socket.h>  //socket bind listen accept connect
#include <netinet/in.h> //sockaddr_in
#include <stdlib.h> //exit
#include <unistd.h> //close
#include <string.h>  //strcat
#include <signal.h>
#define N 128

#define errlog(errmsg) do{perror(errmsg);\
		printf("%s-->%s-->%d\n", __FILE__, __func__, __LINE__);\
		exit(1);\
		}while(0)

typedef struct msg					
{
	char type;
	char name[32];
	char text[N];
}MSG;
 
typedef struct node					
{
	struct sockaddr_in addr;
	struct node *next;	
}listnode,*linklist;
 
 
 
int main(int argc, const char *argv[])
{
	MSG msg;
	int sockfd;
	struct sockaddr_in serveraddr;
	socklen_t addrlen = sizeof(struct sockaddr);
	pid_t pid;
	if(argc < 3)
	{
		printf("argument is too few\n");
		exit(1);
	}
 
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		errlog("fail to socket");
	}
 
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));
	
	printf("输入用户名:");
	fgets(msg.name,sizeof(msg.name),stdin);
	msg.name[strlen(msg.name)-1]='\0';
	msg.text[0]='\0';
	msg.type= 'L';
	if(sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&serveraddr,addrlen)<0)
	{
		errlog("fail to sendto");
	}
 
	pid=fork();
	if(pid==0)						/**子进程从终端获取输入，并发送消息**/
	{
		while(1)
		{
			fgets(msg.text,N,stdin);
			msg.text[strlen(msg.text)-1]='\0';
			if(strncmp(msg.text,"quit",4)==0)
			{
				msg.type='Q';
				if(sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&serveraddr,addrlen)<0)
				{
					errlog("fail to sendto");
				}
				printf("quit !");
				kill(getppid(),SIGKILL);
				exit(1);
			}
			else
			{
				msg.type='B';
				if(sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&serveraddr,addrlen)<0)
				{
					errlog("fail to sendto");
				}
			}
		}
	}
	else					/**父进程接收服务器端的消息并打印**/
	{
		while(1)
		{
			recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&serveraddr, &addrlen); 
			puts(msg.text);
		}
	}
	close(sockfd);
 
	return 0;
}
