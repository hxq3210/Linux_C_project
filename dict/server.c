/*************************************************************************
  > 文件名称 : server.c
  > 创 建 者 : hxq
  > E--mail  : 1038403210@qq.com
  > 创建时间 : 2018年08月13日18时28分56秒
  > 描   述  : 
 *************************************************************************/
#include<stdio.h>
#include"head.h"

void do_register(int connfd,MSG *msg,sqlite3 *db)   //注册用户
{
	char sql[128];
	char *errmsg;
	sprintf(sql,"insert into user(name,pass) values('%s','%s');",msg->name,msg->data);//注册，将信息插入数据库
	printf("%s\n",sql);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		sqlite3_free(errmsg);
		sprintf(msg->data,"用户%s已存在!",msg->name);
	}
	else
	{
		strncpy(msg->data,"OK",256);  //操作成功
	}
	send(connfd,msg,sizeof(MSG),0);
	return;
}
void do_login(int connfd,MSG *msg,sqlite3 *db)     //登录用户
{
	char sql[128];
	char *errmsg,**result;
	int row,col;
	sprintf(sql,"select * from user where name ='%s' and pass ='%s';",msg->name,msg->data);
	if(sqlite3_get_table(db,sql,&result,&row,&col,&errmsg) != SQLITE_OK)
	{
		printf("error:%s\n",errmsg);
		sqlite3_free(errmsg);
	}
	if(row == 0)  //没有找到登录的用户
	{	
		strncpy(msg->data,"name or pass wrong!!",256);
	}
	else
	{
		strncpy(msg->data,"OK",256);
	}
	send(connfd,msg,sizeof(MSG),0);
	sqlite3_free_table(result);
	return;
}
int do_search(int connfd,MSG *msg,sqlite3 *db)		//查单词
{
	char sql[128];
	char *errmsg;
	char **result;
	int row,col;
	sprintf(sql,"select * from dict where word ='%s';",msg->name);
	if(sqlite3_get_table(db,sql,&result,&row,&col,&errmsg) != SQLITE_OK)
	{
		printf("error:%s\n",errmsg);
		sqlite3_free(errmsg);
	}
	if(row > 0)		//找到单词
	{
		strncpy(msg->data,result[row*col+2],1024);
	}
	else
	{
		strncpy(msg->data,"no mean for this word!!",256);
		send(connfd,msg,sizeof(MSG),0);
		//			strcpy(msg->data,"no mean for this word!!");
		return 0;
	}
	send(connfd,msg,sizeof(MSG),0);
	sqlite3_free_table(result);
	return 1;
}

void get_date(char date[])//获取时间
{
	time_t t;
	struct tm *tp;
	time(&t);
	tp = localtime(&t);
	strftime(date,64,"%Y-%m-%d %H:%M:%S",tp);
//	return;
}
void do_query(int connfd, MSG *msg, sqlite3 *db)  //将历史记录插入到record表中
{
	char sql[128], *errmsg;
	int found = 0;
	char date[1024], word[1024];
	strcpy(word, msg->data);
	found = do_search(connfd,msg,db);
	if (found>=0)          //判断找到单词是否成功
	{
		get_date(date);   //如果成功，记录时间，插入历史表
		sprintf(sql,"insert into record values ('%s','%s','%s');",msg->name,date,word);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("error : %s\n", errmsg);
			sqlite3_free(errmsg);
		}
	}
	else                 //如果失败，报错
	{
		strcpy(msg->data, "not found\n");
		send(connfd, msg, sizeof(MSG), 0);
	}
	return ;
}

int history_callback(void *arg, int f_num, char **f_value, char **f_name)//回调表中msg->name的记录
{
	int connfd;
	MSG msg;
	connfd = *(int *)arg;
	sprintf(msg.data, "%s : %s : %s", f_value[0],f_value[1], f_value[2]);
	send(connfd, &msg, sizeof(MSG), 0);
	return 0;
}

void do_history(int connfd, MSG *msg, sqlite3 *db)  //查找当前用户的历史记录
{
	char sql[128], *errmsg;
	sprintf(sql, "select * from record ;");
	if(sqlite3_exec(db, sql, history_callback, (void *)&connfd, &errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	else
	{
		send(connfd, msg, sizeof(MSG), 0);
		msg->data[0] = '\0';               //表示回调结束
		send(connfd, msg, sizeof(MSG), 0);
	}
	return;
}

void do_client(int connfd,sqlite3 *db)   //处理客户机信息
{
	MSG msg;
	while(recv(connfd,&msg,sizeof(msg),0) > 0)
	{
		switch(msg.type)
		{
			case 1:
				do_register(connfd,&msg,db);	//注册
				break;
			case 2:
				do_login(connfd,&msg,db);		//登录
				break;
			case 3:
				//				do_search(connfd,&msg,db);		//查单词
				do_query(connfd,&msg,db);
				break;
			case 4:
				do_history(connfd,&msg,db);		//历史记录
				break;
		}
	}
	printf("client quit\n");
	exit(0);
	return;
}
int main(int argc, char *argv[])
{
	int listenfd,connfd;
	struct sockaddr_in server_addr;
	pid_t pid;
	sqlite3 *db;
	char sql[128],*errmsg;
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("error : %s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	if(argc != 3)
	{
		printf("Usage:%s <ip> <port>\n",argv[0]);
		return -1;
	}
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family		=	AF_INET;
	server_addr.sin_addr.s_addr	=	inet_addr(argv[1]);
	server_addr.sin_port		=	htons(atoi(argv[2]));
	if(bind(listenfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
	if(listen(listenfd,5) < 0)
	{
		perror("fail to listen");
		exit(-1);
	}
	signal(SIGCHLD,SIG_IGN);
	sprintf(sql,"delete from record;");
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("error : %s\n", errmsg);
		sqlite3_free(errmsg);
	}
	while(1)
	{
		if((connfd = accept(listenfd,NULL,NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		if((pid = fork()) < 0)
		{
			perror("fail to fork");
			exit(-1);
		}
		if(pid == 0)
		{
			do_client(connfd,db);
		}
		if(pid > 0)
		{
			wait(NULL);
		}
		close(connfd);
	}
	return 0;
}


