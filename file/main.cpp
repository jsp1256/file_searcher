#include<io.h>
#include<stdio.h>
int main()
{
long Handle;
struct _finddata_t FileInfo;
if((Handle=_findfirst("D:\\资料\\*.txt",&FileInfo))==-1L)
printf("没有找到匹配的项目\n");
else
{
printf("%s\n",FileInfo.name);
while(_findnext(Handle,&FileInfo)==0)
printf("%s\n",FileInfo.name);
_findclose(Handle);
}
return 0;
}
