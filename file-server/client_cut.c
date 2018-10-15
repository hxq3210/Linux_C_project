/*************************************************************************
    > 文件名称 : client_cut.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月16日18时38分20秒
    > 描   述  : 
*************************************************************************/
#include<stdio.h>
#include"head.h"

int do_filecut(char * fname,int N)
{
	FILE * fd  = fopen(fname,"rb");				//源文件
	FILE * div = fopen("./div.txt","w");		//记录文件
	if(fd == NULL || div == NULL)
	{
		perror("文件打开错误：");
		return -1;
	}
	fseek(fd,0,SEEK_END);
	int fLen = ftell(fd);
	int blocklen = fLen / N;
	FILE *ftmp;
	for(int i = 0;i < N;i++)
	{
		char tName[20];
		char tdir[60]= "./";
		sprintf(tName,"部分%d.tmp",i+1);
		strcat(tdir,tName);
		ftmp = fopen(tdir,"wb");
		if(ftmp == NULL)
		{
			perror("生成文件出错");
			break;
		}
		fputs(tdir,div);
		fputc('\n',div);


		int offset = i*blocklen;
		fseek(fd,offset,SEEK_SET);
		int count = 0;
		if(i == N -1) 
			blocklen = fLen - blocklen*(N - 1);
		while(count < blocklen && !feof(fd))
		{
			fputc(fgetc(fd),ftmp);
			count++;
		}
		printf("count:%d\n",count);
		fclose(ftmp);
	}
	fclose(fd);
	fclose(div);
//	system("pause");
//	sleep(2);
	return N;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage:%s <ip> <port> \n",argv[0]);
		return -1;
	}
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in server_addr;
	server_addr.sin_family			=		AF_INET;
	server_addr.sin_port			=		htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr		=		inet_addr(argv[1]);
	socklen_t len					=		sizeof(server_addr);

	int ret = connect(sockfd,(struct sockaddr*)&server_addr,len);
	if(ret < 0)
	{
		perror("connect");
		return -1;
	}
	char * filename;
	char  tName[30];
	FILE * stream;
	char buffer[1024];
	bzero(buffer,1024);
	int n,i;
	printf("请输入要分割的文件名,分割的个数\n");
	scanf("%s %d",filename,&n);
	ret = do_filecut(filename,n);
	if(ret < 0)
	{
		printf("分割文件失败\n");
		return -1;
	}
//	pid_t pid = fork();
//	if(pid == 0)
//	{
		for(i=0;i<n;i++)
		{
			sprintf(tName,"部分%d.tmp",i+1);
			//		strcat(tdir,tName);
			if((stream = fopen(tName,"r")) == NULL)
			{
				printf("文件打开失败\n");
				exit(-1);
			}
			else
			{
				bzero(buffer,1024);
				while((ret = fread(buffer,1,1024,stream)) > 0)
				{
//					printf("%s",buffer);
					if(send(sockfd,buffer,ret,0) < 0)
					{
						printf("发送失败\n");
						exit(-1);
					}
		//			printf("%s",buffer);
					bzero(buffer,1024);
				}
//				if(fclose(stream))
//				{
					printf("文件关闭\n");
//					break;
//					exit(1);
//				}
			}
		}
//	}
	close(sockfd);
    return 0;
}
