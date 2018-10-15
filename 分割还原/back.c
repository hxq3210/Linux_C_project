/*************************************************************************
    > 文件名称 : demo4.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年08月01日09时02分23秒
    > 描   述  : 
*************************************************************************/
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main()
{
    FILE *fdest = fopen("cba.txt", "wb"); //合并生成的文件
    FILE *div = fopen("div.txt", "r");  // 读取已分割部分的目录
    if ( fdest == NULL || div == NULL)
    {
        perror("打开文件出错");
        return;
    }

    char tempName[60]; 
    FILE *tempFile;
    // 循环读出temp文件路径，并进行文件的合并
    while (fgets(tempName, 60, div)) // fgets读取到字符串时返回非0，否则返回0
    {

         tempName[strlen(tempName)-1] = '\0'; // 去掉最后一个\n
         tempFile = fopen(tempName, "rb");
         if (tempFile == NULL)
         {
             printf("打开文件%s失败,", tempName);
             perror("出错原因");
             return;
         }

         printf("正在合并%s到新文件\n",tempName);
         int ch = fgetc(tempFile);//在用feof前先读取一个字符

         while (!feof(tempFile))
         {
             fputc(ch, fdest); //写入字符
             ch = fgetc(tempFile);//读取下一个字符 如果是EOF,那么进入下一次循环前就会停止
         }

         fclose(tempFile);
    }
    fclose(fdest);
    fclose(div);

    system("pause");
}
