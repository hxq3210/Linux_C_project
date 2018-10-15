/*************************************************************************
    > 文件名称 : bitree.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日15时58分19秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 20
/*创建二叉树结构体*/
typedef int datatype;
typedef struct bnode
{
	struct bnode *lchild;
	datatype  data;
	struct bnode *rchild;
}bitree;
/*创建队列结构体*/
typedef struct _sequeue_
{
	datatype data[N];	//存放数据
	int head;   //队头下标
	int tail;	//队尾下标
	int count;	//记录有效长度
}sequeue;
/*创建二叉树节点 ===》》递归*/
bitree * create_node(datatype va);

/*建立满二叉树*/
bitree * bitree_create(int size,datatype value);

/*二叉树调用函数*/
//bitree *root;

/*先序遍历*/
int pro_order(bitree *root);
/*中序遍历*/
int z_order(bitree *root);
/*后序遍历*/
int h_order(bitree *root);
/*层序遍历*/
void cx_order(bitree *root);
/*释放二叉树*/
void bt_free(bitree *root);



/*创建队列*/
sequeue * sq_create();
/*初始化队列*/
void sq_init(sequeue *s);
/*入队*/
int sq_enter(sequeue *s,datatype value);
/*出队*/
int sq_exit(sequeue *s);
/*释放队列*/
int sq_free(sequeue *s);
/*判空*/
int sq_isempty(sequeue *s);
/*判满*/
int sq_isfull(sequeue *s);





