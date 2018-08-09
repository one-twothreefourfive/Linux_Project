
#include <stdio.h>
#include <curses.h>			/* 使用curses函数库和前面定义的kbhit()函数 */
#include <errno.h>
//#include <sys/filio.h>
#include <sys/ioctl.h>

//#define C_PLUS_PLUS_CHAR_READ_MODE1 1
//#define C_PLUS_PLUS_CHAR_READ_MODE2 1
#define C_PLUS_PLUS_CHAR_READ_CURSES_MODE 1


#if C_PLUS_PLUS_CHAR_READ_CURSES_MODE
int kbhit()
{
	int i;

	errno=0;
	if(ioctl(0,FIONREAD,&i) < 0) {
		if(errno == EBADF) printf("errno:bad file number");
		if(errno == EINVAL) printf("errno: invalid argument");
	}
	return i;
}
void main()
{
	char c=' ';
	int i = 0;
	
	initscr();				/* 初始化curses函数 */
	cbreak();
	noecho();				/* 按键时不在屏幕回显字符 */
	mvprintw(0,0,"Press 'q' quit \n");
	refresh();

	while(c != 'q') {
		if(kbhit()) {
			c = getchar();	/* 不会阻塞，因为我们知道有个字符正在等待 */
			mvprintw(1,0,"got %c,on iteration %d \n",c,++i);
			refresh();
		}
	}
	nocbreak();
	echo();
	endwin();				/* 结束curses进程 */
}
#endif

#if C_PLUS_PLUS_CHAR_READ_MODE1
void main()
{	
	int c;
	system("stty raw");			/* 终端驱动处于一次一个字符模式 */
	c = getchar();
	system("stty cooked");		/* 终端驱动处又回到一次一行模式 */
	
}
#endif

#if C_PLUS_PLUS_CHAR_READ_MODE2
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
