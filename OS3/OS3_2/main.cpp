#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct MemPart{
    int start;
    int length;
    string state;
};

struct Job{
    string name;
    int length;
    int state;      //0未分配，1已分配
}job;

vector<MemPart> FreePart,OccupyPart;    //空闲分区表与已分配分区表
int FreeNum=0;                          //空闲分区数量
int Next=0;                             //上次找到的空闲分区的位置下一个,用于循环首次适应算法

int menuInput(void);        //菜单面板
void memInput(void);        //输入空闲分区
void jobInput(void);        //输入作业信息
void display(void);         //显示空闲分区表与已分配分区表
void memSort(void);         //将空闲分区按从大到小排序
void firstFit(void);        //首次适应算法
void nextFit(void);         //循环首次适应算法
void bestFit(void);         //最佳适应算法

int menuInput(void)
{
    fflush(stdin);
    system("cls");
    int i=-1;
    cout<<"请选择操作:"<<endl;
    cout<<"0.显示分区表"<<endl;
    cout<<"1.首次适应算法"<<endl;
    cout<<"2.循环首次适应算法"<<endl;
    cout<<"3.最佳适应算法"<<endl;
    cout<<"4.退出"<<endl;
    cin>>i;
    return i;
}

void memInput(void)
{
    MemPart input;
    input.state="free";
    cout<<"请输入所需要分配的空闲分区数："<<endl;
    cin>>FreeNum;
    for(int i=0;i<FreeNum;i++)
    {
        cout<<"请输入第"<<i<<"个空闲分区的首地址与大小："<<endl;
        cin>>input.start>>input.length;
        FreePart.push_back(input);
    }

}

void jobInput(void)
{
    cout<<"请输入作业名称"<<endl;
    cin>>job.name;
    cout<<"请输入作业大小"<<endl;
    cin>>job.length;
    job.state=0;
}

void display(void)
{
    printf("\n空闲分区表：\n");
    printf("%15s%15s%15s","起始地址","分区大小","分区状态\n");
    for(unsigned int i=0;i<FreePart.size();i++)
        printf("%15d%15d%15s\n",FreePart[i].start,FreePart[i].length,FreePart[i].state.c_str());

    printf("已分配分区表：\n");
    printf("%15s%15s%15s","起始地址","分区大小","分区状态\n");
    for(unsigned int i=0;i<OccupyPart.size();i++)
        printf("%15d%15d%15s\n",OccupyPart[i].start,OccupyPart[i].length,OccupyPart[i].state.c_str());
}

void firstFit(void)
{
    jobInput();
    MemPart occupy;
    for(unsigned int i=0;i<FreePart.size();i++)          //寻找合适的空闲分区
    {
        if(FreePart[i].length>=job.length)      //分配内存
        {
            occupy.length=job.length;
            occupy.start=FreePart[i].start;
            occupy.state=job.name;
            OccupyPart.push_back(occupy);

            FreePart[i].start+=job.length;
            job.state=1;
            break;
        }
    }

    if(job.state==0)
        printf("无合适的空闲分区分配给该作业，请稍后再提交！\n");
    else
        printf("作业分配成功！\n");
}

void nextFit(void)
{
    jobInput();
    MemPart occupy;
    for(unsigned int i=Next;i<FreePart.size();i++)          //寻找合适的空闲分区
    {
        if(FreePart[i].length>=job.length)                                  //分配内存
        {
            occupy.length=job.length;
            occupy.start=FreePart[i].start;
            occupy.state=job.name;
            OccupyPart.push_back(occupy);

            FreePart[i].start+=job.length;
            job.state=1;
            Next=i+1;
            break;
        }
    }
    if(job.state==0)
    {
        for(unsigned int i=0;i<(unsigned)Next;i++)
        {
                if(FreePart[i].length>=job.length)                                  //分配内存
                {
                    occupy.length=job.length;
                    occupy.start=FreePart[i].start;
                    occupy.state=job.name;
                    OccupyPart.push_back(occupy);

                    FreePart[i].start+=job.length;
                    job.state=1;
                    Next=i+1;
                    break;
                }
        }
    }

    if(job.state==0)
        printf("无合适的空闲分区分配给该作业，请稍后再提交！\n");
    else
        printf("作业分配成功！\n");
}

void bestFit(void)
{

}

int main()
{
    memInput();
    while(1)
    {
        switch (menuInput())
        {
            case 0:
                system("cls");
                display();
                system("pause");
                break;

            case 1:
                system("cls");
                firstFit();
                system("pause");
                break;

            case 2:
                system("cls");
                nextFit();
                system("pause");
                break;

            case 3:
                system("cls");
                bestFit();
                system("pause");
                break;

            case 4:
                exit(EXIT_SUCCESS);
                break;

            default:
                cout<<"输入错误，请重新输入！\n"<<endl;
                system("pause");
                break;
        }

    }

    return 0;
}
