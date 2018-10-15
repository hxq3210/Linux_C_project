/*************************************************************************
    > 文件名称 : seqstack.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日16时15分21秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include"seqstack.h"
#include<stdlib.h>
#include<string.h>
seqstack *seqstack_create()
{
	seqstack * s = (seqstack*)malloc(sizeof(seqstack));
	if(NULL == s) return NULL;
	bzero(s,sizeof(seqstack));
	return s;
}
int	seqstack_isfull(seqstack *s)
{
	if(s->top >= N)	return 1;
	else			return 0;
}
int	seqstack_isempty(seqstack *s)
{
	if(s->top <= 0)  return 1;
	else			 return 0;
}
int seqstack_push(seqstack *s,datatype va)
{
	if(seqstack_isfull(s))	return -1; 
	s->data[s->top] = va;
	s->top++;
	return 0;
}
datatype seqstack_pop(seqstack *s)
{
	if(seqstack_isempty(s)) return -1;
	s->top--;
	return s->data[s->top];
}
datatype seqstack_get_top_value(seqstack *s)
{
//	if(s->top==0) return -1;
	return s->data[s->top];
}
