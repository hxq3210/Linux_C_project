/*************************************************************************
    > 文件名称 : server_bak.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月16日18时38分10秒
    > 描   述  : 
*************************************************************************/
#include<stdio.h>
#include"head.h"

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage: %s <ip> <port> <file_back_name>\n",argv[0]);
		return -1;
	}
	FILE * fd = fopen(argv[3],"wb");			//合并生成的文件
	if(NULL == fd)
	{
		perror("打开文件失败");
		return -1;
	}
	int listenfd,connfd;
	struct sockaddr_in server_addr;
	pid_t pid;

	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	server_addr.sin_family			=	AF_INET;
	server_addr.sin_addr.s_addr		=	inet_addr(argv[1]);
	server_addr.sin_port			=	htons(atoi(argv[2]));
	socklen_t len	=	sizeof(server_addr);
	if(bind(listenfd,(struct sockaddr*)&server_addr,len) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
	if(listen(listenfd,10) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}
	else
	{
		printf("connect......\n");
	}
	signal(SIGCHLD,SIG_IGN);
	while(1)
	{
		if((connfd = accept(listenfd,NULL,NULL)) < 0)
		{
//			perror("fail to accept");
			exit(-1);
		}
		int ret = 0; 
		if((pid = fork()) < 0)
		{
			perror("fail to fork");
			exit(-1);
		}
		else if(pid == 0)
		{
			char buff[1024];
			while(ret = recv(connfd,buff,sizeof(buff),0))
			{
				if(ret < 0)
				{
					perror("fail to recv");
					exit(-1);
				}
				int write_len = fwrite(buff,1,ret,fd);				
				if(write_len < ret)
				{
					printf("file write fail\n");
					break;
				}
				//			printf("%s",buff);
				bzero(buff,sizeof(buff));
			}
			printf("File back Ok!\n");
			exit(0);			
		}
		else if(pid > 0)
		{
			wait(NULL);
		}
		fclose(fd);
		close(connfd);
		close(listenfd);
	}
	return 0;
}
