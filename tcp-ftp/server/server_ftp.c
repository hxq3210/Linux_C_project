/*************************************************************************
  > 文件名称 : server_ftp.c
  > 创 建 者 : hxq
  > E--mail  : 1038403210@qq.com
  > 创建时间 : 2018年08月07日17时51分26秒
  > 描   述  : 
 *************************************************************************/
#include<stdio.h>
#include"head.h"

int do_socket(char add[128],int port)
{
	int ret=0,connfd;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in  addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(add);

	socklen_t len=sizeof(addr);

	ret=bind(sockfd,(struct sockaddr*)&addr,len);

	ret=listen(sockfd,100);  //监听
	if(ret<0)
	{	
		perror("listen");
		return -3;
	}

	struct sockaddr_in cliaddr;
	socklen_t mylen=sizeof(cliaddr);

	connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&mylen);
	if(connfd<0)
	{
		perror("accept");
		return -2;
	}

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
		send(connfd,"world",5,0);
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
int do_send(char *pb,int sockfd)
{
	struct file f;
	int ret1=0,ret2=0;
	char msg[128]={0};
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
			//send(sockfd,&f.len,4,0);
			close(fp);
			printf("send success!\n");
			break;
		}
	}
	return 0;
}
int do_ls(int connfd)
{
	system("ls -l > ls");
	do_send("ls",connfd);
	system("rm ls");
	return 0;
}

int main(int argc, char *argv[])
{
	int ret1=0,ret=0;
	char te[64]={0};
	char te1[32]={0};
	char te2[32]={0};	
	if(argc != 3)
	{
		printf("Usage: %s <ip> <port>\n",argv[0]);
		return -1;
	}
	int connfd=do_socket(argv[1],(atoi(argv[2])));
	struct file f;
	while(1)
	{
		ret1=recv(connfd,&f,sizeof(f),0);
		if(ret1<0)
		{
			perror("recv");
			break;
		}
		sscanf(f.te,"%s %s",te1,te2);
		if(strncmp(te1,"ls",2)==0)
		{
			do_ls(connfd);
		}

		if(strncmp(te1,"by ",3)==0) 
			break;

		if(strcmp(te1,"get")==0)
		{
			do_send(te2,connfd);
			printf("文件%s上传完毕!\n",te2);
		}

		if(strcmp(te1,"put")==0)
		{
			do_recv(te2,connfd);
			printf("文件%s下载完毕!\n",te2);
		}
	}

	close(connfd);
	return 0;
}
