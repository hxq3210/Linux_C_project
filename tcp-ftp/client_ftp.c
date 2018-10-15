/*************************************************************************
  > 文件名称 : client_ftp.c
  > 创 建 者 : hxq
  > E--mail  : 1038403210@qq.com
  > 创建时间 : 2018年08月07日17时51分34秒
  > 描   述  : 
 *************************************************************************/
#include<stdio.h>
#include"head.h"

int do_socket(char add[128],int port)
{
	int ret=0;

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return -2;
	}

	struct sockaddr_in addr;
	addr.sin_family= AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(add);

	socklen_t len=sizeof(addr);

	ret=connect(sockfd,(struct sockaddr*)&addr,len);
	if(ret<0)
	{
		perror("connect");
		return -1;
	}
	return sockfd;
}
int do_send(char *pb,int sockfd)
{
	struct file f;
	char msg[128]={0};
	int ret1=0,ret2=0;
	int fp=open(pb,O_RDONLY);
	if(fp<0)
	{
		perror("open");
		return -1;
	}
	while(1)
	{
		bzero(&f,sizeof(f));
		f.len=read(fp,f.text,sizeof(f.text));
		ret1=send(sockfd,&f,sizeof(f),0);
		if(ret1<0)
		{
			perror("read");
			break;
		}
		recv(sockfd,msg,sizeof(msg),0);
		if(f.len==0)
		{
			close(fp);
			printf("send success!\n");
			break;
		}
	}
	return 0;
}
int do_recv(char *pa,int connfd)
{
	struct file f;
	int fd=open(pa,O_CREAT|O_RDWR,0644);
	if(fd<0)
	{
		perror("open");
		return -1;
	}
	int ret1=0,ret2=0;
	while(1)
	{
		bzero(&f,sizeof(f));
		ret1=recv(connfd,&f,sizeof(f),0);
		if(ret1<0)
		{
			perror("recv");
			break;
		}
		send(connfd,"hello",5,0);
		if(f.len==0)
		{
			close(fd);
			printf("recv ok!\n");
			break;
		}
		else
		{
			ret2=write(fd,f.text,f.len);
			if(ret2<0)
			{
				perror("write");
				break;
			}
		}
	}
	return 0;
}

int do_ls(int sockfd)
{
	do_recv("ls",sockfd);
	system("cat ls");
	system("rm ls");
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s <ip> <port>\n",argv[0]);
		return -1;
	}

	int sockfd=do_socket(argv[1],(atoi(argv[2])));
	char te1[32]={0};
	char te2[32]={0};
	int ret=0;
	char buff[128]={0};
	struct file f;
	system("clear");
	printf("******************************\n");
	printf("FTP:put/get+filename ‘by’退出 \n");
	printf("******************************\n");

	while(1)
	{
		printf("ftp>> ");
		fgets(f.te,sizeof(f.te),stdin);
		ret=send(sockfd,&f,sizeof(f),0);
		if(ret<0)
		{
			perror("send2");
			break;
		}
		sscanf(f.te,"%s %s",te1,te2);

		if(strncmp(f.te,"ls",2)==0) 
		{
			do_ls(sockfd);
		}

		else if(strcmp(te1,"get")==0)
		{
			ret=do_recv(te2,sockfd);
			if(ret==-1)  printf("没有%s文件\n",te2);
			else printf("文件%s下载完毕!\n",te2);
		}

		else if(strcmp(te1,"put")==0)
		{
			ret=do_send(te2,sockfd);
			if(ret==-1) 
				printf("没有%s文件\n",te2);
			else
				printf("文件%s上传完毕!\n",te2);
		}
		else if(strncmp(f.te,"by",2)==0) 
			break;

	}	
	close(sockfd);
	return 0;
}
