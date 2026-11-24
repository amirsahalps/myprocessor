#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"filutils.h"
#include"comment_removal.h"
char *include_file(const char *filename)
{
FILE *fp,*fq;
fp=fopen(filename,"r");//reading .i file
if(fp==0)
return 0;
fq=fopen("temp.i","w");//temp file to include header files
if(fq==0)
{
printf(".i file cant be created");
fclose(fp);
return 0;
}
int i;
char s[1024];
while((fgets(s,sizeof(s),fp))!=0)
{
if((strncmp(s,"#include",8))==0)//getting line which contains #include
{
char *p=s+8;// jump after #include < or "
while(*p==' '||*p=='\t')
p++;// if space or tab incriment

char closing;
//checking its < or "
if(*p=='<')
closing='>';
else if(*p=='"')
closing='"';
else
{
printf("bad include line:%s",s);
continue;
}
char *end=strchr(p+1,closing);// finding closing > or " address
if(end==0)
{
printf("bad include line:%s",s);
continue;
}
int len=(int)(end-p-1);// finding charcters btween them
//printf("file name is= %.*s\n",len,p+1);
/////////////////////////////////////////////
char name[256];
if(len<=0||len>=(int)sizeof(name))
{
printf("bad include line:\n");
continue;
}
for(i=0;i<len;i++)// copiying header file name to name array
name[i]=p[1+i];
name[i]='\0';	
///////////////////////////////////////////////////
char *t;
if (closing == '>')
{
    t = read_std(name);          // <name>: standard folder first
    if (t == NULL)
        t = readfile(name);         // fallback: current folder
}
else
{
    t = readfile(name);             // "name": current folder first
    if (t == NULL)
        t = read_std(name);      // fallback: standard folder
}
if(t==0)
{
printf("error:cant open this file:%s\n",name);
fclose(fp);
fclose(fq);
remove("temp.i");
return 0;
}
char *c=remove_comments(t);// removing comments in including file
free(t);
if(c==0)
{
printf("out of memory:\n");
fclose(fp);
fclose(fq);
remove("temp.i");
return 0;
}
fputs(c,fq);// includiing file
free(c);
////////////////////////////////////////////
}
else
{
fputs(s,fq);//other part of main
}
}
fclose(fp);
fclose(fq);
rename("temp.i",filename);
return 0;
} 
