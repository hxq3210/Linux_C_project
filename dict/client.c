/*************************************************************************
    > 文件名称 : client.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月13日00时10分41秒
    > 描   述  : 
*************************************************************************/
#include<stdio.h>
#include"head.h"

void do_register(int sockfd,MSG *msg)		//注册用户
{
	msg->type = 1;
	printf("input name: ");
	scanf("%s",msg->name);
	printf("input passwd:");
	scanf("%s",msg->data);
	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	printf("Register:%s\n",msg->data);
	return;
}

int do_login(int sockfd,MSG *msg)   //登录用户
{
	msg->type = 2;
	printf("Please input name: ");
	scanf("%s",msg->name);
	printf("Please input passwd: ");
	scanf("%s",msg->data);
	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	if(strncmp(msg->data,"OK",3) == 0)
	{
		printf("Login : OK\n");
		return 1;
	}
	printf("Login:%s\n",msg->data);
	return 0;
}

void do_query(int sockfd,MSG *msg)		//查单词
{
	msg->type = 3;
	while(1)
	{
		printf("Input a word,'3'退:\n");
		scanf("%s",msg->name);
		if(strncmp(msg->name,"3",1) == 0) 
		{
			break;
		}
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("mean>>>%s\n",msg->data);	
	}
	return;
}
void do_history(int sockfd,MSG *msg)	//保存历史记录
{
	msg->type = 4;
	send(sockfd,msg,sizeof(MSG),0);
	while(1)
	{
		recv(sockfd,msg,sizeof(MSG),0);
		if(msg->data[0] == '\0')
			break;
		printf("%s\n",msg->data);
	}
	return;
}
int main(int argc, char *argv[])
{
	MSG msg;
	if(argc!=3)
	{
		printf("Usage:%s <ip> <port>\n",argv[0]);
		return -1;
	}
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd  < 0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in  server_addr;
	server_addr.sin_family		= AF_INET;
	server_addr.sin_port		= htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t len  = sizeof(server_addr);

	int ret = connect(sockfd,(struct sockaddr *)&server_addr,len);
	if(ret < 0)
	{
		perror("connect");
		return -2;
	}
	int n;
	system("clear");
	while(1)
	{
		printf("***********************************\n");
		printf("*  1:register  2:login  3:  quit  *\n");
		printf("***********************************\n");
		printf("please choice:");
		int ret =scanf("%d",&n);
		if(ret <= 0 || (n>3||n<1))
		{
			perror("fail to choice");
			exit(-1);
		}
		switch(n)
		{
			case 1:
				do_register(sockfd,&msg);
				break;
			case 2:
				if(do_login(sockfd,&msg) == 1)
				{
					printf("\n");
					goto next;	//跳转查单词
				}
				break;
			case 3:
				close(sockfd);
				exit(0);
		}
	}
next:
	while(1)
	{
		printf("*************************************\n");
		printf("*  1:query_word  2:history  3:quit  *\n");
		printf("*************************************\n");
		printf("please choice:");
		int ret = scanf("%d",&n);
		if(ret <= 0||(n>3||n<1))
		{
			perror("fail to choice");
			exit(-1);
		}
		switch(n)
		{
			case 1:
				do_query(sockfd,&msg);
				break;
			case 2:
				do_history(sockfd,&msg);
				break;
			case 3:
				close(sockfd);
				exit(0);
		}
	}
	return 0;
}
