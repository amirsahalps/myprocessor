#define PI 3.14
#define MAX 100
#define DEBUG
#define SQUARE(x) ((x)*(x))
#include"filutils.h"
#include"comment_removal.h"
#include"macro_handler.h"
int main()//sd
{
int a=7;//firstline comment
/*j,ncjdjcjknkJNKJCBKCBCBKJBCK
DNBBDBHKBCkdbcKBCKCBKCBDCK
*/
int b=6;
//whole line comment
int c=8;
a/**/b;

int a = PI;
int b = PIPE;
int c = MAX + PI;
int a = SQUARE(a+1);
int c = SQUARE (3);
int d = SQUARE;
int s = SQUARE(f(2));

char *a = "PI is a name";
char *u = "http://x.com";
char *v = "/* not a comment */";
char *w = "say \"hi\" // still string";
char c = '"'; // real comment
char d = '/'; /* real block comment */
return 0;
}
/* dadcajchjkhckjdckhdbkcgdjcgsj
acnkjchahcbhjabcha

