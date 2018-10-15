/*************************************************************************
    > 文件名称 : bitree.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日15时58分13秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include"bitree.h"
#include<stdlib.h>
#include<string.h>
/*创建队列*/
sequeue * sq_create()
{	
	sequeue *s=(sequeue *)malloc(sizeof(sequeue));

	s->head=s->tail=0;

	bzero(s,sizeof(sequeue));
	
	return s;
}

/*初始化队列*/
void sq_init(sequeue *s)
{
	s->head=s->tail=0;
}
/*队列判空*/
int sq_isempty(sequeue *s)
{
	if(s->head==s->tail)
		return -1;
	else
		return 0;
}
/*队列判满*/
int sq_isfull(sequeue *s)
{
	if(s->tail>=N)
		return -1;
	else 
		return 0;
}
/*进队列*/
int sq_in(sequeue *s,datatype va)
{
	if(sq_isfull(s))  return -1;

	s->data[s->tail]=va;
	
	s->tail++;
	
//	free(s);

	return 0;
}
/*出队列*/
datatype sq_out(sequeue *s)
{
	datatype ret=0;

	if(sq_isempty(s))  return -1;
	ret=s->data[s->head];

	s->head++;

	return ret;
}
/*释放队列*/
int sq_free(sequeue *s)
{
	if(sq_isempty(s))
	{
		free(s);
		return 0;
	}
	else
	{
		sq_out(s);
		free(s);
	}
	return 0;
}






/*创建二叉树节点 ===》》递归*/
bitree * create_node(datatype va)
{
	bitree *n = malloc(sizeof(bitree));
	n->data = va;
	n->lchild = n->rchild =NULL;
	printf(" bitree = %d\n", va);
	return n;
}
/*建立满二叉树*/
bitree * bitree_create(int size,datatype value)
{
	bitree *t = create_node(value);
	if(2*value <= size)
	{
		t->lchild = bitree_create(size,2*value);
	}
	if(2*value+1 <= size)
	{
		t->rchild = bitree_create(size,2*value+1);
	}
	return t;
}

/*层序遍历*/
void cx_order(bitree *root)
{
	bitree *b;						
	sequeue *q;						//声明一个队列
	if(root == NULL)						
		return;						//如果树为空，直接返回
	q = sq_create();				//创建并初始化队列
	sq_in(q,root);				//将根节点入队
	while(!sq_isempty(q))				
	{
		b = sq_out(q);				//节点出队
		printf(" %d ", b->data);	//输出出队的节点
		if(b->lchild != NULL)    sq_in(q,b->lchild);  //若左孩子不为空，将其入队
		if(b->rchild != NULL)    sq_in(q,b->rchild);  //若右孩子不为空，将其入队
	}
	sq_free(q);
	printf("\n");
}
/*二叉树的释放*/
void bt_free(bitree *root)
{
     if(root != NULL)
	 {
	     bt_free(root->lchild);
         bt_free(root->rchild);
	     free(root);
		 root = NULL;
	 }
}

