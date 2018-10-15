/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日15时58分28秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include"bitree.h"
int main(int argc, char *argv[])
{
	int c;
	printf("请输入二叉树节点个数\n");
	scanf("%d",&c);
	bitree *root = bitree_create(c,1);
	printf("层序遍历二叉树\n");
	cx_order(root);
	bt_free(root);
    return 0;
}
