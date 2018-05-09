#include <cstdio>
#include <cstdlib>
#include <windows.h>

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
    int RunState;   //运行状态，0表示就绪，1表示正在运行，2表示运行结束
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

void input(void);             //输入存储分区方式
void display(MemPart*);      //显示进程表和分区说明表
void memSort(MemPart*);      //将存储分区从小到大排序
void proSort();               //将就绪进程从小到大排序

void input(void)
{
    printf("(内存大小1024，即0~1023）\n");
    printf("请输入分区个数：");
    scanf("%d",&Mem_Num);
    MemTable=(MemPart*)malloc(sizeof(MemPart)*Mem_Num);
    for(int i=0;i<Mem_Num;i++)
    {
        printf("请输入第%d块固定分区的长度：");
        if(i!=0){
            MemTable[i].addr=MemTable[i-1].addr+MemTable[i-1].size;
        }
    }

}

int main()
{

    return 0;
}
