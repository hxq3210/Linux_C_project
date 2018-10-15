/*************************************************************************
    > 文件名称 : server.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月03日19时24分50秒
    > 描   述  : 
*************************************************************************/
#include <stdio.h>   //printf
#include <arpa/inet.h>  //inet_addr htons
#include <sys/types.h>
#include <sys/socket.h>  //socket bind listen accept connect
#include <netinet/in.h> //sockaddr_in
#include <stdlib.h> //exit
#include <unistd.h> //close
#include <string.h> //strcat
#include <unistd.h>	//fork
#define N 512

#define errlog(errmsg) 	do{perror(errmsg);\
		printf("%s-->%s-->%d\n", __FILE__, __func__, __LINE__);\
 		exit(1);\
	       }while(0)
 						 
/**
  L：表示消息类型为登录
  B：表示消息类型为广播
  Q：表示消息类型为退出
  */
						 
typedef struct msg	//定义消息结构体
{
	char type;		/**< 消息类型 */
	char name[32];  /**< 消息来源标识*/
	char text[N];   /**< 消息内容*/
}MSG;
 
typedef struct node		//存储网络信息结构体的链表
{
	struct sockaddr_in addr;
	struct node *next;	
}listnode,*linklist;
 
void process_login(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr);	//登录
void process_chat(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr);		//客户端发送消息
void process_quit(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr);		//退出
 
/**
 创建一个链表
 */
linklist linklist_creat()
{
	linklist H;
	H=(linklist)malloc(sizeof(listnode));
	H->next=NULL;
	return H;
}
 
 
 
int main(int argc, const char *argv[])
{
	MSG msg;
	int sockfd;
	pid_t pid;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t addrlen = sizeof(struct sockaddr);
	char buf[N] = {0};
 
	if(argc < 3)
	{
		printf("argument is too few\n");			
		exit(1);
	}
 
	//第一步：创建一个套接字
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		errlog("fail to socket");
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));
 
	//第三步：将套接字与网络信息结构体绑定
	if(bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
	{
		errlog("fail to bind");
	}
	pid=fork();
	if(pid<0)
	{
		errlog("fork error");
	}
	
	/**子进程输入**/
	if(0==pid)
	{
		memset(&msg,0,sizeof(msg));
		strcpy(msg.name,"server");
		msg.type='B';
		while(1)
		{
			fgets(msg.text, N, stdin);
			msg.text[strlen(msg.text)-1]='\0';
			sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&(serveraddr),addrlen);
		}
	}
	
	/**父进程接收发送**/
	else
	{
		linklist H=linklist_creat();
		while(1)
		{
			if(recvfrom(sockfd, &msg, sizeof(msg), 0, (struct sockaddr*)&(clientaddr),&addrlen) <= 0)
			{
				errlog("recvfrom error");
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
		}
	}
	close(sockfd);
	return 0;
}
 
void process_login(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr)
{
	linklist p=H->next;
	//sprintf(msg.text,"%s上线了",msg.name);
	strcpy(msg.text,msg.name);
	msg.text[strlen(msg.text)]='\0';
	strcat(msg.text," 上线了");
	//printf(msg.text);
	puts(msg.text);
	while(p!=NULL)
	{
	 sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr *)&(p->addr),sizeof(p->addr));  
	// printf("send %s to port %d\n",msg.text,ntohs((p->addr).sin_port));
	 p=p->next;
	}
	p=(linklist)malloc(sizeof(listnode));			//使用头插法插入网络信息结构体数据
	p->addr=clientaddr;
	p->next=H->next;
	H->next=p;
	printf("get client port = %d.\n",ntohs((p->addr).sin_port));
}
 

 
 void process_chat(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr)
 {
	linklist p = H->next;	
	char s[N]={0};
	sprintf(s,"%s说: %s",msg.name,msg.text);
	strcpy(msg.text,s);
	puts(msg.text);
	while(p)																	//遍历链表
	{
		if(memcmp(&clientaddr,&p->addr,sizeof(clientaddr))!=0)
		{
			if(sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&(p->addr),sizeof(p->addr))<0)
			errlog("fail to sendto");
		}
		p=p->next;
	}
	
 }
 
 /*
  比较网络信息，删除存储即将退出的客户端的网络信息的节点
 */
 void process_quit(int sockfd,linklist H,MSG msg,struct sockaddr_in clientaddr)
 {
	linklist p = H;
	linklist q=NULL;
	sprintf(msg.text,"%s 下线了",msg.name);
	puts(msg.text);
	while(p->next)
	{
		if(memcmp(&clientaddr,&p->next->addr,sizeof(clientaddr))==0)
		{
			q=p->next;
			p->next=q->next;
			free(q);
			q=NULL;
		}
		else 
		{
			sendto(sockfd,&msg,sizeof(msg),0,(struct sockaddr*)&(p->next->addr),sizeof(p->next->addr));			//退出信息发送给其余未推出的所有客户端成员
			p=p->next;
		}
	}
	
 }
 
