#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <time.h>

#define PCB_NUM 5         //模拟进程数量
#define MEM_SIZE 1024      //内存大小

using namespace std;

struct MemPart{
    int addr;   //分区起始地址
    int size;   //分区大小
    int state;  //0表示空闲，非0表示已分配，存储的是进程ID

    MemPart(){
        addr=0;
        size=0;
        state=0;
    }
}*MemTable;

struct PCB{
    int pcbID;
    int size;
    int RunState;   //进程状态，0表示就绪，1表示正在运行，2表示运行结束
    int TolTime;
    int RunTime;

    PCB(){
        pcbID=0;
        size=0;
        RunState=0;
        TolTime=0;
        RunTime=0;
    }
}pcbList[PCB_NUM];

int Mem_Num=0;

void input(void);            //输入存储分区方式
void pcbInit(void);          //初始化进程表
int pcbTestEnd(void);        //检测是否所有进程均运行完毕
void display(void);          //显示进程表和分区说明表
void memSort(void);          //将存储分区从小到大排序
void distroy(void);          //释放分配的内存

void input(void)
{
    printf("(内存大小1024，即0~1023）\n");
    printf("请输入分区个数：");
    scanf("%d",&Mem_Num);
    MemTable=(MemPart*)malloc(sizeof(MemPart)*Mem_Num);
    for(int i=0;i<Mem_Num;i++)
    {
        printf("请输入第%d块固定分区的长度：",i);
        scanf("%d",&MemTable[i].size);
        if(i!=0){            //计算首地址
            MemTable[i].addr=MemTable[i-1].addr+MemTable[i-1].size;
        }
        else{
            MemTable[i].addr=0;
        }
        if(MemTable[i].addr+MemTable[i].size >= MEM_SIZE){
            printf("超出规定内存范围，请重新输入！\n");
            i--;
            continue;
        }
        MemTable[i].state=0;
    }
    memSort();
}

void pcbInit(void)
{
    srand((unsigned)time(NULL));
    for(int i=0;i<PCB_NUM;i++)
    {
        pcbList[i].pcbID=i+1;
        pcbList[i].size=10+15*i;
        pcbList[i].RunState=0;
        pcbList[i].TolTime=1+rand()%9;
        pcbList[i].RunTime=0;
    }
}

int pcbTest(void)
{
    int flag=1;
    for(int i=0;i<PCB_NUM;i++)
    {
        if(pcbList[i].RunState!=2)
        {
            flag=0;
            break;
        }
    }
    return flag;
}

void display(void)
{
    printf("\n就绪进程：\n");
    printf("%15s%15s%15s%15s%15s\n","进程ID","进程大小","进程状态","需要时间","运行时间");
    for(int i=0;i<PCB_NUM;i++)
       printf("%15d%15d%15d%15d%15d\n",pcbList[i].pcbID,pcbList[i].size,pcbList[i].RunState,pcbList[i].TolTime,pcbList[i].RunTime);

    printf("内存分区：\n");
    printf("%15s%15s%15s\n","起始地址","分区大小","分区状态");
    for(int i=0;i<Mem_Num;i++)
        printf("%15d%15d%15d\n",MemTable[i].addr,MemTable[i].size,MemTable[i].state);
}

void memSort(void)
{
    int tempSize=0;
    for(int i=0;i<Mem_Num-1;i++)
    {
        for(int j=i;j<Mem_Num;j++)
        {
            if(MemTable[i].size>MemTable[j].size)
            {
                tempSize=MemTable[i].size;
                MemTable[i].size=MemTable[j].size;
                MemTable[j].size=tempSize;
            }
        }
    }
}

void destroy(void)
{
    delete []MemTable;
}

int main()
{
    input();
    pcbInit();
    display();
    system("pause");

    while(pcbTest()!=1)
    {
        for(int i=0;i<PCB_NUM && pcbTest()!=1;i++)
        {
            if(pcbList[i].RunState==0)  //分配内存给线程
            {
                for(int j=0;j<Mem_Num;j++)
                {
                    if(MemTable[j].state==0 && MemTable[j].size>=pcbList[i].size)
                    {
                        MemTable[j].state=pcbList[i].pcbID;
                        pcbList[i].RunState=1;
                        break;
                    }
                }
            }

            for(int k=0;k<PCB_NUM;k++)  //时间加1
            {
                if(pcbList[k].RunState==1)
                    pcbList[k].RunTime++;
            }
            for(int k=0;k<PCB_NUM;k++)  //处理完成的进程，释放内存
            {
                if(pcbList[k].RunTime==pcbList[k].TolTime)
                {
                    for(int x=0;x<Mem_Num;x++)
                    {
                        if(MemTable[x].state==pcbList[k].pcbID)
                            MemTable[x].state=0;
                    }
                    pcbList[k].RunState=2;
                }
            }
            display();
            system("pause");
        }
    }
    printf("所有进程运行完毕，程序结束。\n");
    destroy();

    return 0;
}
