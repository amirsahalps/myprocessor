#include<stdio.h>
#include"header.h"
#include"mystring.c"
int main(int argc,char **argv)
{
if(argc!=3)
{
printf("wrong usage:");
return 0;
}
FILE *fp,*fq;
fp=fopen(argv[1],"r");
if(fp==0)
{
printf("file not present");
return 1;
}
fq=fopen(argv[2],"w");
int i,ch,k=0,c=0;
char s[1000];
while((ch=fgetc(fp))!=-1)
{
if(ch==' '||ch=='\n'||ch=='\t')
{
if(k>0)
{
s[k]='\0';
for(i=0;s[i];i++)
{
if(s[i]=='a')
mystrrev(s,k);
}
fputs(s,fq);
c++;
k=0;
}
fputc(ch,fq);
}
else if(k<999)
s[k++]=ch;
}
printf("%d",c);
fclose(fp);
fclose(fq);
}






