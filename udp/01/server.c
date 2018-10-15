/*************************************************************************
    > 文件名称 : server.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月03日11时42分29秒
    > 描   述  : 
*************************************************************************/
#include<stdio.h>
#include"head.h"
typedef struct msg  //定义消息结构体
{
	char type;
	char name[32];
	char text[128];
}MSG;

typedef struct node    //存储网络信息结构体链表
{
	struct sockaddr_in addr;
	struct node *next;
}listnode,*linklist;


linklist linklist_create()
{
	linklist H;
	H = (linklist)malloc(sizeof(listnode));
	H->next = NULL;
	return H;
}
void process_login(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr) //登录
{
	linklist p = H->next;
	strcpy(msg.text,msg.name);
	msg.text[strlen(msg.text)] = '\0';
	strcat(msg.text,"上线了");
	puts(msg.text);
	while(p != NULL)
	{
		sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&(p->addr),sizeof(p->addr));
		p = p->next;
	}
	p = (linklist)malloc(sizeof(listnode));
	p->addr = clientaddr;
	p->next = H->next;
	H->next = p;
	printf("get client port = %d\n",ntohs((p->addr).sin_port));
}
void process_chat(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr)  //聊天
{
	linklist p = H->next;
	char s[128] = {0};
	sprintf(s,"%s说:%s",msg.name,msg.text);
	strcpy(msg.text,s);
	puts(msg.text);
	while(p)
	{
		if(memcmp(&clientaddr,&p->addr,sizeof(clientaddr)) != 0)
		{
			if(sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&(p->addr),sizeof(p->addr))<0)
				perror("fail to sendto");
		}
		p = p->next;
	}
}
void process_quit(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr) //退出
{
	linklist p = H;
	linklist q = NULL;
	sprintf(msg.text,"%s",msg.name);
	puts(msg.text);
	while(p->next)
	{
		if(memcmp(&clientaddr,&p->next->addr,sizeof(clientaddr))==0)
		{
			q = p->next;
			p->next = q->next;
			free(q);
			q = NULL;
		}
		else
		{
			sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&(p->next->addr),sizeof(p->next->addr));
			p = p->next;
		}
	}
}

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
	//创建socket
	int sockfd  = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in  serveraddr,clientaddr;
	serveraddr.sin_family		= AF_INET;
	serveraddr.sin_port			= htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr	= inet_addr(argv[1]);
	socklen_t addrlen = sizeof(struct sockaddr);
	ret = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(ret < 0)
	{
		perror("fail bind");
		return -1;
	}
	pid = fork();
	if(pid < 0)
	{
		perror("fail fork");
		return -1;
	}
	//子进程输入
	if(pid == 0)
	{
		memset(&msg,0,sizeof(msg));
		strcpy(msg.name,"server");
		msg.type = 'B';
		while(1)
		{
			fgets(msg.text,128,stdin);
			msg.text[strlen(msg.text)-1] = '\0';
			sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&serveraddr,addrlen);
		}
	}
	//父进程接收发送
	if(pid > 0)
	{
		linklist H = linklist_create();
		while(1)
		{
			ret = recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,&addrlen);
			if(ret < 0)
			{
				perror("recv from client");
				return -1;
			}
			switch(msg.type)
			{
				case 'L':
					process_login(sockfd,H,msg,clientaddr);
					break;
				case 'B':
					process_chat(sockfd,H,msg,clientaddr);
					break;
				case 'Q':
					process_quit(sockfd,H,msg,clientaddr);
					break;
			}
/*		else
			{
				printf("ip = %s,port = %d:%s\n",inet_ntoa(myaddr.sin_addr),
				myaddr.sin_port,buff);
				sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&myaddr,len);
			}
*/
		}
	}
	close(sockfd);
	return 0;
}
