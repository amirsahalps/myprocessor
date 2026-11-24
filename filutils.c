#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//////////////////////////////////////////////////
char *readfile(const char *fina)
{
FILE *fp=fopen(fina,"r");
if(fp==0)
return 0;
fseek(fp,0,SEEK_END);
long size=ftell(fp);
rewind(fp);
char *text=malloc(sizeof(char)*size+1);
if(text==0)
{
free(text);
return 0;
}
int ch,i=0;
while((ch=fgetc(fp))!=EOF)
{
text[i++]=ch;
}
text[i]='\0';
fclose(fp);
return text;
}
 char *read_std(const char *name)
{
    char path[512];
    snprintf(path, sizeof(path), "/usr/include/%s", name);
    return readfile(path);
}
