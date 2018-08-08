#include <stdio.h>
//#include <sys/filio.h>
#include <sys/ioctl.h>
#include <errno.h>

//#define C_PLUS_PLUS_CHAR_READ_MODE 1

#ifdef C_PLUS_PLUS_CHAR_READ_MODE
void main()
{	
	int c;
	system("stty raw");			/* 终端驱动处于一次一个字符模式 */
	c = getchar();
	system("stty cooked");		/* 终端驱动处又回到一次一行模式 */
	
}
#else
int kbhit()
{
	int i;

	errno=0;
	if(ioctl(0,FIONREAD,&i) < 0)
	{
		if(errno == EBADF) printf("errno:bad file number");
		if(errno == EINVAL) printf("errno: invalid argument");
	}
	return i;
}
main()
{	
	int i = 0;
	char c=' ';
	
	system("stty raw -echo");
	printf("input 'q' squit\n");

	for(;c!='q';i++)
	{
		if(kbhit())
		{
			c = getchar();
			printf("\n got %c,on iteration = %d",c,i);
		}
	}
	system("stty cooked echo");   
}
#endif
