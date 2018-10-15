/*************************************************************************
    > 文件名称 : seqstack.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日16时15分26秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define N 10
typedef int datatype;
typedef struct _stack_
{
	datatype data[N];
	int top;
}seqstack;
seqstack *seqstack_create();
//入栈
datatype seqstack_push(seqstack *s,datatype va);

datatype seqstack_pop(seqstack *s);
datatype seqstack_isempty(seqstack *s);
datatype seqstack_get_top_value(seqstack *s);
