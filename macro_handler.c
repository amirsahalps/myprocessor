#include<string.h>
#include<stdio.h>
///////////////////////////////////////////
struct macro
{
    char name[64];
    char value[256];
};


int process_macros(const char *filename)
{
struct macro table[100];
int count = 0;
FILE *fp,*fq;
fp=fopen(filename,"r");
if(fp==0)
{
printf("cant opent this file:%s",filename);
return 0;
}
fq=fopen("temp.i","w");
if(fq==0)
{
printf("cant open temp file");
return 0;
}
int i;
char s[1024];
while((fgets(s,sizeof(s),fp))!=0)
{
if(strncmp(s,"#define",7)==0)
{
char *p=s+7;//jump to after #define
while(*p==' '||*p=='\t')
p++;

int n=0;
while(p[n]=='_'||(p[n]>='a'&& p[n]<='z')||(p[n]>='A' && p[n]<='Z')||(p[n]>='0'&& p[n]<='9'))
n++;

if((n>0&&n<64)&&count<100)
{
count++;
for( i=0;i<n;i++)
table[count].name[i]=p[i];

table[count].name[i]='\0';
}
else
{
printf("bad #define line:%s",s);
continue;
}
p = p + n;
    while (*p == ' ' || *p == '\t')
        p++;
int v = 0;
while (p[v] != '\0' && p[v] != '\n' && v < 255)
{
    table[count].value[v] = p[v];
    v++;
}
table[count].value[v] = '\0';

printf("macro: name=[%s] value=[%s]\n", table[count].name, table[count].value);

}

}
}






