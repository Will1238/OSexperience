#include <cstdio>
#include <cstdlib>

struct JCB
{
    char username[10];
    char jobname[10];
    int atime;              //作业到达时间
    int ntime;              //作业估计运行时间
    int nsource;            //作业所需总系统资源
    int asource;            //已分配的资源
    int nsource2;           //作业现在所需的资源(=nsource-asource)
    struct JCB* Next;

    JCB(void)
    {
        Next=NULL;
    }
}*Ready=NULL, *p;           //Ready指向就绪队列的队头，p指向正被调度的作业

int N=0;                    //作业个数
int source=10;              //初始系统资源

void input(void);           //输入作业
void fcfs_sort(void);       //新作业插入队列
void display(JCB* work);    //显示作业信息
void running(void);         //运行后备队列队首的作业
void running2(void);   //将不满足的队首作业放至队尾
int length(void);           //返回后备队列的长度
int deadlock_test(void);    //死锁检测,返回值0表示正常，返回值1表示死锁

void input(void)
{
    printf("（本程序初始系统资源数为10）\n");
    printf("请输入作业个数：");
    scanf("%d",&N);

    for(int i=0;i<N;i++)
    {
        p=new JCB();
        printf("\n作业%d：\n",i);
        printf("输入作业用户名：");
        scanf("%s",p->username);
        printf("输入作业名：");
        scanf("%s",p->jobname);
        printf("输入作业到达时间：");
        scanf("%d",&(p->atime));
        printf("输入作业运行时间：");
        scanf("%d",&(p->ntime));
        printf("输入作业所需总资源：");
        scanf("%d",&(p->nsource));
        printf("输入已分配给作业的资源：");
        scanf("%d",&(p->asource));
        p->nsource2=p->nsource - p->asource;

        fcfs_sort();
    }
}

void fcfs_sort(void)
{
    if(Ready==NULL)
    {
        Ready=p;
    }
    else
    {
        JCB *flag=Ready;
        if(Ready->atime <= p->atime)
        {
            while((flag->Next!=NULL)&&((flag->Next)->atime <= p->atime))
                flag=flag->Next;

            p->Next=flag->Next;
            flag->Next=p;
        }
        else
        {
            p->Next=Ready;
            Ready=p;
        }

    }
}

void display(JCB* work)
{
    printf("\n%15s%15s%15s%15s%15s%15s%15s\n", "用户名", "作业名", "到达时间", "估计运行时间", "所需总资源", "已分配资源", "所需资源");
    printf("%15s%15s%15d%15d%15d%15d%15d\n", work->username, work->jobname, work->atime, work->ntime, work->nsource, work->asource, work->nsource2);
}

void running(void)
{
    p=Ready;
    Ready=Ready->Next;

    p->asource=p->nsource;
    source-=p->nsource2;
    p->nsource2=0;
    printf("\n当前运行的作业：\n");
    display(p);
    printf("\n系统所剩资源:%d\n",source);

    printf("\n当前作业后备队列状态为：\n")
    for(JCB* flag=Ready;flag!=NULL;flag=flag->Next)
    {
        printf("\n作业%d：\n");
        display(flag);
    }

    p->Next=NULL;
    source+=p->nsource;

    printf("\n用户[%s]的作业[%s]完成!\n",p->source,p->nsource);
    printf("\n系统所剩资源:%d\n",source);

    delete p;
}

void running2(void)
{

}

int deadlock_test(void)
{
    int i=0;
    for(JCB *flag;(flag!=NULL)&&(flag->nsource2 > source);flag=flag->Next)
        i++;

    if(i==length())
        return 1;
    else
        return 0;
}

int length(void)
{
    int i=0;
    for(JCB *flag;flag!=NULL;flag=flag->Next)
        i++;
    return i;
}

int main()
{
    input();
    for(p=Ready;p!=NULL;p=p->Next)
        display(p);

    while(length())
    {
        if(deadlock_test()!=0)
            break;

//
        p=Ready;
        while(p->nsource2 > source)
        {
            p=p->Next;
            running2();

        }
//
        running();
        Sleep(1000);
    }

    return 0;
}
