#include "stdio.h"
#include <stdlib.h>
#include <conio.h>
#define getpch(type) (type*)malloc(sizeof(type))
#define source 15

struct jcb
{
    char username[10];
    char jobname[10];
    char state;
    int atime;//作业到达时间
    int ntime;//作业估计运行时间
    int rtime; //作业的运行时间
    int nsource;//作业所需系统资源
    int asource;//已分配的资源
    int need1;
    struct jcb* link;
}*ready=NULL, *p;//ready指向就绪队列的队头，p指向正被调度的作业

typedef struct jcb JCB;
int rsource=15;//剩下资源
int num,i=0;//num为作业个数，i为记录不能满足作业要求调度的次数

void destroy(JCB *pr)
{
    free(pr);
}

void sort() /* 建立对作业进行到达时间排列函数*/
{
    JCB *first, *second;
    int insert=0;
    if((p->nsource<=source)&&(rsource>=0)&&(p->nsource>p->asource))
    {
        //需要资源要在系统资源范围内，分配资源要在需要资源范围内，剩下资源不能小于0
        if((ready==NULL)||((p->atime)<(ready->atime))) /*作业到达时间最短的,插入队首*/
        {
            p->link=ready;
            ready=p;
        }
        else /* 作业比较到达时间,插入适当的位置中*/
        {
            first=ready;
            second=first->link;
            while(second!=NULL)
            {
                if((p->atime)<(second->atime)) /*若插入作业比当前队尾作业到达时间短,*/
                {
                    /*插入到当前队尾作业前面*/
                    p->link=second;
                    first->link=p;
                    second=NULL;
                    insert=1;
                }
                else /* 插入作业到达时间最长,则插入到队尾*/
                {
                    first=first->link;
                    second=second->link;
                }
            }
            if (insert==0) first->link=p;
        }
    }
    else
        destroy(p);
}

void sort1() /*对作业进行排列函数 */
{
    JCB *first;
    if(ready==NULL) /*如果就绪队列为空*/
    {
        ready=p; /*将新建作业放入队列中，将ready指向队首作业 */
    }
    else /*队列中有作业在等待，将新建作业插入到队尾 */
    {
        first=ready; /*first指针指向队首作业 */
        while(first->link!=NULL) first=first->link; /*当first指针没有指向队尾时，指针后移 */
        first->link=p;/*将p指向的作业插入队尾*/
    }
}

void input() /*建立作业控制块函数*/
{
    int i;
    printf("\n 请输入作业个数:");
    scanf("%d",&num);
    for(i=0; i<num; i++)
    {
        printf("\n 请输入作业号NO.%d：\n",i);
        p = getpch(JCB);
        printf("输入作业用户名:");
        scanf("%s",p->username);
        printf("\n输入作业名:");
        scanf("%s",p->jobname);
        printf("\n输入作业到达时间:");
        scanf("%d",&p->atime);
        printf("\n 输入作业运行时间:");
        scanf("%d",&p->ntime);
        printf("\n 输入作业所需资源:");
        scanf("%d",&p->nsource);
        printf("\n 输入作业已分配资源:");
        scanf("%d",&p->asource);
        printf("\n");
        p->need1=p->nsource-p->asource;//还需要资源=需要资源-已分配资源
        p->state='W';
        p->link=NULL;
        sort();
    }
}

int space() /*查看作业个数*/
{
    int l=0;
    JCB *pr=ready;
    while(pr!=NULL)
    {
        l++;
        pr=pr->link;
    }
    return(l);
}

void disp(JCB *pr) /*建立作业显示函数，用于显示当前作业*/
{
    printf("\n 用户N \t 作业N \t 状态S \t 到达T \t 服务T \t 所需S \t 已分S \t 还需S \n");
    printf(" |%s \t",pr->username);
    printf(" |%s \t",pr->jobname);
    printf(" |%c \t",pr->state);
    printf(" |%d \t",pr->atime);
    printf(" |%d \t",pr->ntime);
    printf(" |%d \t",pr->nsource);
    printf(" |%d \t",pr->asource);
    printf(" |%d \t",pr->need1);
    printf("\n");
}

void check()
{
    JCB *pr;
    printf("\n****当前正在运行的作业是：%s",p->jobname);
    disp(p);
    pr=ready;
    printf("\n****当前输入井队列状态为：\n"); /*显示就绪队列状态*/
    while(pr != NULL)
    {
        disp(pr);
        pr = pr->link;
    }
}

void running(JCB *p)//对输入井队列中满足资源要求的作业进行服务
{
    while(p->rtime<p->ntime)
    {
        (p->rtime)++;
    }
    p->state='F';
    printf("\n****作业运行完成后状态:\n");
    disp(p);
    printf("\n 用户名[%s]的作业[%s] 已完成。\n",p->username,p->jobname);
}

void running1()// 计算剩下资源
{
    JCB *pr;
    for(pr=ready; pr!=NULL; pr=pr->link)
    {
        rsource=rsource-pr->asource;
    }
}

void running2(JCB *pr)
{
    if(pr->need1<=rsource)
    {
        check();
        rsource-=pr->need1;
        pr->asource+=pr->need1;
        pr->need1 =0;
        printf("\t********************************************\n");
        printf("\n分配给作业后所剩的资源是：%d \n",rsource);
        running(pr);
        rsource = rsource + pr->nsource;
        printf("\n释放后的资源是：%d\n",rsource);
        destroy(pr);
    }
    else
    {
        printf("该作业不能满足要求，调度下一个作业");
        sort1();
        i++;
    }
}

int main()
{
    int len, h=0;//h表示执行的次数
    printf("*********************************************************\n");
    printf("                             \n");
    printf("                  多道作业调度算法                       \n");
    printf("*********************************************************\n");
    input();
    len = space();
    running1();
    if(rsource>=0)
    {
        while((i<=2*num)&&(len!=0)&&(ready!=NULL))
        {
            getchar();
            h++;
            printf("The execue number:%d\n",h);
            printf("\n系统可分配资源是：%d",rsource);
            getchar();
            p=ready;
            ready=ready->link;
            p->link=NULL;
            p->state ='R';
            running2(p);
            printf("\n 按任一键继续...");
            getchar();
        }
        if(i>2)
        {
            printf("\n******剩下系统资源不能满足作业需要要求了\n");
            printf("\n******退出程序");
        }
        else  printf("\n作业已完成\n");
        getchar();
    }
    else
        printf("\n\n****因为输入已分配的资源与系统资源不符合错误，所以退出程序****");

    return 0;
}
