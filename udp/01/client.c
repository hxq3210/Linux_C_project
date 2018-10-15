/*************************************************************************
  > 文件名称 : client.c
  > 创 建 者 : hxq
  > E--mail  : 1038403210@qq.com
  > 创建时间 : 2018年08月03日11时46分51秒
  > 描   述  : 
 *************************************************************************/
#include<stdio.h>
#include"head.h"
typedef struct msg
{
	char type;
	char name[32];
	char text[128];
}MSG;
typedef struct node
{
	struct sockaddr_in addr;
	struct node *next;
}listnode,*linklist;

int main(int argc, char *argv[])
{
	MSG msg;
	pid_t pid;
	if(argc != 3)
	{
		printf("Usage:%s <ip> <port>\n",argv[0]);
		return -1;
	}
	char buff[128] ={0};
	int n,ret  = 0;
	int sockfd  = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in  myaddr;
	myaddr.sin_family		= AF_INET;
	myaddr.sin_port			= htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr	= inet_addr(argv[1]);
	socklen_t len = sizeof(struct sockaddr);
	printf("输入用户名:");
	fgets(msg.name,sizeof(msg.name),stdin);
	msg.name[strlen(msg.name)-1] = '\0';
	msg.text[0] = '\0';
	msg.type = 'L';

	ret = sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&myaddr,len);
	if(ret < 0)
	{
		perror("sento");
		return -1;
	}
	pid = fork();
	if(pid < 0)
	{
		perror("fail fork()");
		return -1;
	}
	if(pid == 0)//子进程获取输入，并发送消息
	{
		while(1)
		{
			fgets(msg.text,128,stdin);
			if(strncmp(buff,"quit",4)==0)
			{
				msg.type = 'Q';
				ret = sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&myaddr,len);
				//			printf("client input:%s\n",buff);
				if(ret < 0)
				{
					perror("sento");
					return -1;
				}
				printf("quit !!!");
				kill(getppid(),SIGKILL);
				exit(1);
			}
			else 
			{
				msg.type = 'B';
				ret = sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&myaddr,len);
				if(ret < 0)
				{
					perror("fail sento");
				}
			}
		}
	}
	else
	{
		while(1)
		{
			ret = recvfrom(sockfd,buff,strlen(buff),0,(struct sockaddr*)&myaddr,&len);
			if(ret < 0)
			{
				perror("recv from server");
				return -1;
			}
			puts(msg.text);
		}
	}
	close(sockfd);
	return 0;
}

