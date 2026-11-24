#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"filutils.h"
#include"comment_removal.h"
#include"include_file.h"
#include"macro_handler.h"
int main(int argc,char **argv)
{
if(argc!=2)
{
printf("worng usage:./a.out filename\n");
return 0;
}
FILE *fp,*fq;
fp=fopen(argv[1],"r");
if(fp==0)
{
printf("file not present\n");
return 1;
}
int j;
j=strlen(argv[1]);
char *p=malloc(sizeof(char)*j+1);
if(p==0)
{
printf("not allocated\n");
return 1;
}
strcpy(p,argv[1]);
if(j>=2&&p[j-1]=='c'&&p[j-2]=='.')//checks if its lenght min 2 and it has . c at last.
{
p[j-1]='i';
}
else
{
printf("not a .c file error\n");
free(p);
return 1;
}
fq=fopen(p,"w");
///////////////////////////////////////////// removing comments///////////////////////////////////
char *text=readfile(argv[1]);// copying whole file as a string to text
if(text==0)
{
printf("cannot read file");
return 0;
}
char *clean=remove_comments(text);//after clearing comments in text clear file is addres to clean
fprintf(fq,"%s",clean);//clean file without comments copied to .i file
fclose(fq);
fclose(fp);
printf("%s is created\n",p);

include_file(p);
process_macros(p);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
free(p);


return 0;
}
