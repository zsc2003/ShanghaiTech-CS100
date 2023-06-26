#include <stdio.h>
#include <string.h>
 
int main()
{
   char c[] = "This is recitation session";
   char buffer[20];
 
   /* 打开文件用于读写 */
   FILE *fp = fopen("file.txt", "w+");
 
   /* 写入数据到文件 */
   fwrite(c, strlen(c) + 1, 1, fp);
 
   /* 查找文件的开头 */
   fseek(fp, 0, SEEK_SET);
 
   /* 读取并显示数据 */
   fread(buffer, strlen(c)+1, 1, fp);
   printf("%s\n", buffer);
   fclose(fp);
   
   return(0);
}