#include<string.h>
#include<stdlib.h>
//////////////////////////////////////////////////////comment removal///////////////////////////////////////
char *remove_comments(const char *src)
{
char *out=malloc(strlen(src)+1);
if(out==0)
return 0;
int i=0,k=0,in_string=0;
while(src[i]!='\0')//goes till end of string
{
////////////////string copy(if commentting char found inside "" then what) /////////////////////////////
if(src[i]=='"')//first "
{
out[k]=src[i];
k++;
i++;
while(src[i]!='\0'&&src[i]!='"')
{
if(src[i]=='\\'&&src[i+1]!='\0')//if \ found and next char is \0 no need to copy 2 char just \ is enogh :"say \"hi\" // still string"
{
out[k]=src[i];
k++,i++;
out[k]=src[i];
k++,i++;
}
else
{
out[k]=src[i];// if \0 found next \ only \ need to copy or whatever inside string literal.
k++,i++;
}
}
if(src[i]=='"')// last " 
{
out[k]=src[i];
k++,i++;
}
}
////////////////////////// char = '\'' and = '"'; check for this//////////////////////
else if(src[i]=='\'')//first '
{
out[k]=src[i];// copy first single quates
k++,i++;
while(src[i]!='\0'&&src[i]!='\'')//checks for \0 and next single quate to come out of while loop
{
if(src[i]=='\\'&&src[i+1]!='\0')// checking, after' \  ' real character is present with \ ans next char is copied
{
out[k]=src[i];
k++,i++;
out[k]=src[i];
k++,i++;
}
else
{
out[k]=src[i];
k++,i++;
}
}
if(src[i]=='\'')// last '
{
out[k]=src[i];
k++,i++;
}
}

///////////////////////////  checks' // ' //////////////////////////

else if(src[i]=='/'&&src[i+1]=='/')//checks for //
{
while(src[i]!='\n'&&src[i]!='\0')//chcks the end new line or \0.
i++;//skip to next line after //
}



/////////////////////// checks for /* */ ////////////////////////////////////

else if(src[i]=='/'&&src[i+1]=='*')// checks for /*
{
i=i+2;// jumps 2 to reach next char after *.
while(src[i]!='\0'&&(src[i]!='*'||src[i+1]!='/'))//checks  end of comment */ and end of file 
i++;//skip /* */ characters
if(src[i]!='\0')//if end of sting dont jump unauthorised memory 
i=i+2;//if not end  of string jump
out[k]=' ';//adding space were /* */ removed
k++;
}
//////////////////////////////////copy//////////////////////////////////
else
{
out[k]=src[i];// copying file to out sting apart from comments
k++;
i++;
}
}
out[k]='\0';//for making out a string
return out;
}


