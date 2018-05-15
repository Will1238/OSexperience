#include<iostream>
#include<string>

using namespace std;

typedef struct Quick
{
    int qs;//快表段号
    int qp;//快表页号
    int qb;//快表段号
} Quick;
typedef struct Data
{
    int num;//内存的块数
    string str;//对应数据块的作业内容，简化起见说明内容为一串字符。
} Data;
//页表
typedef struct Page
{
    int num;//页号
    int flag;//页状态，即是否在内存。
    int block;//该页对应的块号
} Page;
typedef struct Stack
{
    int num;//段号
    int flag;//段状态
    int plen;//页表长度
    int psta;//页表始址
} Stack;
//段表寄存器
typedef struct Stare
{
    int ssta;//段表始址
    int slen;//段表长度
} Stare;
Stack ss[10];////全局变量
Stare st;///////全局变量
Data work[20];//全局变量
Quick qu;//////全局变量
Page page[5][5];
bool menuflag=0;
int bbs;//内存块大小
int bs;//内存大小
void menu();
void start();
void change();
int main()
{
    menu();
    return 0;
}
void menu()
{
    cout<<"请选择:"<<endl;
    cout<<endl;
    cout<<" 1、初始化表 "<<endl;
    cout<<" 2、物理地址转换 "<<endl;
    cout<<" 3、退出 "<<endl;
    int menu1;
    cin>>menu1;
    if(menu1!=1&&menu1!=2&&menu1!=3)
    {
        cout<<"请输入正确的选项"<<endl;
        menu();
    }
    switch(menu1)
    {
    case 1:
    {
        menuflag=1;
        start();
        break;
    }
    case 2:
    {
        if(menuflag==0)
        {
            cout<<"请初始化表"<<endl;
            menu();
        }
        change();
        break;
    }
    case 3:
        return;
    }//switch
}
void start()
{
    cout<<"请输入内存大小(K)"<<endl;
    cin>>bs;
    cout<<"请输入内存块的大小(k)"<<endl;
    cin>>bbs;
    int blocknum;
    blocknum=bs/bbs;
    cout<<"内存一共被分为"<<blocknum<<"块，每块"<<bbs<<"k"<<"一共"<<bs<<"k"<<endl;
    cout<<"请输入进程个数"<<endl;
    int pn;
    cin>>pn;
//下面求所有进程的总段数和段表,并为每段创建页表
    int sums=0;
    for (int pn1=0; pn1<pn; pn1++)
    {
        cout<<"请输入第"<<pn1<<"个进程的段数"<<endl;
        int ppn;
        cin>>ppn;
        sums+=ppn;
    }
    for(int ss1=0; ss1<sums; ss1++)
    {
        cout<<"请输入第"<<ss1<<"个段表数据：段号，状态，页表长度，页表始址"<<endl;
        cin>>ss[ss1].num>>ss[ss1].flag>>ss[ss1].plen>>ss[ss1].psta;
        cout<<"请初始化第"<<ss1<<"段的页表，输入两个数据页表状态和对应块号"<<endl;
        for(int sss1=0; sss1<ss[ss1].plen; sss1++)
        {
            page[ss1][sss1].num=sss1;
            cout<<"请输入该段第"<<sss1<<"个页表的页表状态和对应块号"<<endl;
            cin>>page[ss1][sss1].flag>>page[ss1][sss1].block;
        }
    }
//初始化段表寄存器
    cout<<"初始化段表寄存器的段表始址"<<endl;
    cin>>st.ssta;
    st.slen=sums;
//初始化内存中物理地址每一块的数据区
    cout<<"简单起见，我们对物理地址的每一块用字符串进行简单的初始化，没有具体到每一物理地址"<<endl;
    for (int bn=0; bn<blocknum; bn++)
    {
        work[bn].num=bn;
        cout<<"请输入第"<<bn<<"个内存块里的作业内容"<<endl;
        cin>>work[bn].str;
    }
//初始化快表
    cout<<"简单起见，我们初始化快表只有一个"<<endl;
    cout<<"请输入要作为快表的段号和页号"<<endl;
    cin>>qu.qb>>qu.qp;
    while(ss[qu.qb].flag!=1||page[qu.qb][qu.qp].flag!=1)
    {
        cout<<"该页不在内存请输入一页在内存中的作为快表,请输入要作为快表的段号和页号"<<endl;
        cin>>qu.qb>>qu.qp;
    }
    qu.qs=page[qu.qb][qu.qp].block;
    menu();
}
void change()
{
    cout<<"请输入要转化的逻辑地址，段号s，段内页号p，页内偏移地址d(B)"<<endl;
    int snum,pnum,dnum;
    cin>>snum>>pnum>>dnum;
//首先查快表
    if(snum==qu.qb&&pnum==qu.qp)
    {
        cout<<"快表命中"<<"对应块号是"<<qu.qs<<endl;
        cout<<"该块中作业数据是"<<work[page[qu.qb][qu.qp].block].str<<endl;

        cout<<"物理地址是"<<qu.qs*bbs*1024+dnum<<endl;;
        menu();
    }
//访问段表寄存器
    else
    {
        cout<<"快表没有命中,访问段表寄存器，段号等于段表始址加上偏移地址"<<endl;
        int ssnum;
        ssnum=st.ssta+snum;
        if(ssnum>st.slen-1)
        {
            cout<<"越界中断"<<endl;
            menu();
        }
//访问段表
        else
        {
            if(ssnum>=0&&ssnum<=st.slen-1)
            {
//是否缺段
                cout<<"段表有效"<<endl;
                if(ss[ssnum].flag==0)
                {
                    cout<<"缺段中断"<<endl;
                    menu();
                }
                else
                {
//查询页表，根据段号查出页表始址，加上段内偏移页数，即得到页表项。
//缺页中断测试
                    if(pnum>ss[ssnum].plen-1)
                    {
                        cout<<"缺页中断"<<endl;
                        menu();
                    }
                    else
                    {
                        if(pnum>=0&&pnum<=ss[ssnum].plen-1)
                        {
                            if(page[ssnum][pnum].flag==0)
                            {
                                cout<<"缺页中断"<<endl;
                                menu();
                            }
                            else
                            {

                                cout<<"找到该页"<<"查询页表后对应块号"<<page[ssnum][pnum].block<<endl;
                                cout<<"该块内存的数据是"<<work[page[ssnum][pnum].block].str<<endl;
                                cout<<"转化得到的物理地址是："<<page[ssnum][pnum].block*bbs*1024+dnum<<endl;
                                menu();
                            }
                        }
                    }
                }
            }
        }
    }
}

