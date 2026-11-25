#include<string.h>
#include<stdio.h>
///////////////////////////////////////////
struct macro
{
	char name[64];
	char value[256];
	int  is_func;        // 1 = has an argument, 0 = simple macro
	char param[32];      // the parameter name, e.g. "x"
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
		fclose(fp);
		return 0;
	}
	int i,g;
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
				//count++;
				memset(&table[count], 0, sizeof(table[count]));
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
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(*p=='(')
			{
				table[count].is_func = 1;
				p++;                               // jump over the '('

				int k = 0;
				while (p[k]=='_'||(p[k]>='a'&& p[k]<='z')||(p[k]>='A' && p[k]<='Z')||(p[k]>='0'&& p[k]<='9'))                   // blank 1: letter, digit or '_' (use p[k])
					k++;
				// k is the length of the parameter name
				for (int g2 = 0; g2 < k; g2++)
					table[count].param[g2] = p[g2];
				table[count].param[k] = '\0';

				p = p + k;                         // now p stands on ')'
				if (*p == ')')
					p++;                           // jump over the ')'
				else
				{
					printf("bad macro line: %s", s);
					continue;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////
			while (*p == ' ' || *p == '\t')
				p++;
			int v = 0;
			while (p[v] != '\0' && p[v] != '\n' && v < 255)
			{
				table[count].value[v] = p[v];
				v++;
			}
			table[count].value[v] = '\0';
			fputc('\n',fq);
			//printf("macro:name=[%s] param=[%s] body=[%s]\n",table[count].name, table[count].param, table[count].value);
			count++;
		}
		//////////////////////////////////////////macro replacing /////////////////////////////////////////////////////
		else
		{
			int i=0;


			while (s[i] != '\0')
			{
				///////////////////////////////////////macro name comes inside ""string dont replace that //////////////////////////////
				if(s[i]=='"')//first"
				{
					fputc(s[i],fq);
					i++;
					while(s[i]!='\0'&&s[i]!='"')
					{
						if(s[i]=='\\'&&s[i+1]!='\0')//if \ found and next char is \0 no need to copy 2
						{
							fputc(s[i],fq);
							i++;
							fputc(s[i],fq);
							i++;
						}
						else
						{
							fputc(s[i],fq);
							i++;
						}
					}
					if(s[i]=='"')
					{
						fputc(s[i],fq);
						i++;
					}

				}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				else if ( s[i]=='_'||(s[i]>='a'&& s[i]<='z')||(s[i]>='A' && s[i]<='Z'))//letter or '_' starting of a word
				{
					int start = i;
					while (s[i]=='_'||(s[i]>='a'&& s[i]<='z')||(s[i]>='A' && s[i]<='Z')||(s[i]>='0'&& s[i]<='9'))//letter, digit or '_'
						i++;
					int len = i - start;

					char word[64];
					if (len >= (int)sizeof(word))
						len = sizeof(word) - 1;
					for ( g = 0; g < len; g++)
						word[g] = s[start + g];// copy each word in that line to word and check
								       // memcpy(word, s + start, len);
					word[len] = '\0';

					int found = -1;
					for ( int k = 0; k < count; k++)
					{
						if (strcmp(table[k].name, word) == 0)
						{
							found = k;
							break;
						}
					}
					///////////////////////////////// macro with argument//////////////////////////////////
					if (found >= 0 && table[found].is_func)
					{
						int j = i;// j is the first character of argument
						while (s[j] == ' ' || s[j] == '\t')
							j++;
						if (s[j] == '(')
						{
							j++;
							int astart = j;//argument start 
							int depth = 0;

							while (s[j] != '\0' && !(s[j] == ')' && depth == 0))
							{
								if (s[j] == '(')
									depth++;
								else if (s[j] == ')')
									depth--;
								j++;
							}

							if (s[j] == ')')
							{
								char *body = table[found].value;
								int x = 0;
								while (body[x] != '\0')
								{
									if (body[x]=='_'||(body[x]>='a'&&body[x]<='z')||(body[x]>='A'&&body[x]<='Z'))
									{
										int ws = x;                          // a word starts here
										while (body[x]=='_'||(body[x]>='a'&&body[x]<='z')||(body[x]>='A'&&body[x]<='Z')||(body[x]>='0'&&body[x]<='9'))
											x++;
										int wl = x - ws;

										if (wl == (int)strlen(table[found].param) &&
												strncmp(body + ws, table[found].param, wl) == 0)
											fwrite(s + astart, 1, j - astart, fq);   // the parameter: write the argument
										else
											fwrite(body + ws, 1, wl, fq);            // another word: write it as it is
									}
									else
									{
										fputc(body[x], fq);                          // brackets, *, spaces...
										x++;
									}
								}
								i = j + 1;                                   // continue the line after the ')'
								continue;
							}
						}
					}
					/////////////////////////////////////////////simple macros puting///////////////////////////////

					if (found >= 0&& !table[found].is_func)
						fputs(table[found].value, fq);
					else
						fputs(word, fq);
				}
				else
				{
					fputc(s[i], fq);
					i++;
				}
			}
		}
	}
	fclose(fp);
	fclose(fq);
	if (rename("temp.i", filename) != 0)
		perror("rename");
	return 0;
}






