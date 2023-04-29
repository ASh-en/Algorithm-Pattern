#include <iostream>
#include <time.h>
#include<windows.h>

char buf[102] = {0};

#ifdef WINDOWS
void HideCursor()
{
     CONSOLE_CURSOR_INFO cursor;
     cursor.bVisible = FALSE;// 是否可见
     cursor.dwSize = sizeof(cursor);// 光标百分比大小
     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorInfo(handle, &cursor);
}

void ShowCursor()
{
     CONSOLE_CURSOR_INFO cursor;
     cursor.bVisible = TRUE;// 是否可见
     cursor.dwSize = sizeof(cursor);// 光标百分比大小
     HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorInfo(handle, &cursor);
}
#endif

void proc(float p)//p为进度百分比
{

    static float hisp = 0;
    static clock_t use_time = clock();


    const char *lable = "|/-\\";
    //float p = (float) i*100.0/sum;
    uint8_t i = (uint8_t) p;
    uint8_t l = (clock()/500)%4;

    if(buf[i] == '\0' )
    {
        buf[i] = '*';/**< '▌' = 0xa884,buf[2*i]= 0xa8, buf[2*i + 1]= 0x84,判断条件也需要成2*i，同时需要将数组空间加大*/
    }

    if((p>(hisp+0.01))||((clock()-use_time) > 500))//进度差大于0.01或者时间差大于500ms进行一次更新。
    {
        hisp = p;
        use_time = clock();//这两条语句保证if的判断条件只有一个会为真
        
		/**
		*更新速度过快时会有光标跳跃闪烁问题
		*linux环境下可通过\e[?25lm 进行光标控制，类似其他参数还可控制前背景颜色等
		*Windows环境下更复杂一些，需要通过 HideCursor(),ShowCursor(),进行控制
		*同时该环境下也存在其他函数进行颜色控制，该文件的这两个函数是我自己重新写的，
		*也可以直接用头文件中提供的标准函数，函数名一致，但是另外有参数和返回值。
		*/
#ifdef WINDOWS
        printf("[%-101s][%.02f%%][%c]\r", buf,p,lable[l]);
#else
        printf("\e[?25lm\e[34m[%-101s][%.02f%%][%c]\r", buf,p,lable[l]);//linux
#endif

        fflush(stdout);

    }
    if( i == 100)
    {
        hisp = 0;
        use_time = 0;
        memset(buf, '\0', sizeof(buf));
        printf("\n");
    }


}