#include<io.h>
#include<stdio.h>
int main()
{
long Handle;
struct _finddata_t FileInfo;
if((Handle=_findfirst("D:\\����\\*.txt",&FileInfo))==-1L)
printf("û���ҵ�ƥ�����Ŀ\n");
else
{
printf("%s\n",FileInfo.name);
while(_findnext(Handle,&FileInfo)==0)
printf("%s\n",FileInfo.name);
_findclose(Handle);
}
return 0;
}
