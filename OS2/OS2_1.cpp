#include <iostream>
#include <cstdio>
#include <windows.h>

using namespace std;

struct JCB{
    int No;
    int startRunTime;		//开始运行时刻 
    int finishTime;			//完成运行时刻
    int zzTime;				//带权周转时间
    int nTime;				//完成所需的时间（资源）
	int priority;			//优先级
    JCB *Next;

    JCB(void){
        No=-1;
        startRunTime=-1;
        finishTime=-1;
        zzTime=-1;
        nTime=-1;
    	priority=-1;
        Next=NULL;
    }
}*Head,*Tail;

void input(void)
{
    int N;
    JCB *work;

    cout<<"请输入作业个数:"<<endl;
    cin>>N;
    for(int i=0;i<N;i++)
    {
        work=new JCB();
        work->No=i;
        cout<<"请输入作业"<<i<<"运行所需时间:"<<endl;
        cin>>work->nTime;
        cout<<"请输入作业"<<i<<"的优先级数:"<<endl;
		cin>>work->priority;

        if(Head==NULL)
        {
            Head=work;
            Tail=Head;
        }
        else
        {
			Tail->Next=work;
			Tail=Tail->Next;
		}
    }
}

void destroy(void)
{
	while(Head!=NULL)
	{
		Tail=Head;
		Head=Head->Next;
		delete Tail;
	}
}

void FCFS(void)
{
	JCB *work,*tag,*FCFS_Head=NULL,*FCFS_Tail=NULL;
	int t=0;
	float zztime_right=0,zztime=0;		//带权周转和周转 
	
	for(tag=Head;tag!=NULL;tag=tag->Next)	//拷贝作业队列 
	{
		work=new JCB();
		work->No=tag->No;
		work->nTime=tag->nTime;
		work->priority=tag->priority;
		if(FCFS_Head==NULL)
		{
			FCFS_Head=work;			
			FCFS_Tail=work;
		}
		else
		{	
			FCFS_Tail->Next=work;
			FCFS_Tail=FCFS_Tail->Next;
		}
			
	}
	
	printf("\n先来先服务算法（FCFS）：\n");
	printf("%10s%15s%10s%10s%15s\n","作业编号","开始运行时刻","完成时刻","周转时间","带权周转时间"); 
	
	for(tag=FCFS_Head;tag!=NULL;tag=tag->Next)
	{
		tag->startRunTime=t;
		tag->finishTime=t+tag->nTime;
		tag->zzTime=tag->finishTime;	//作业均在0时刻被提交给系统 
		printf("%10d%15d%10d%10d%15.1f\n",tag->No,tag->startRunTime,tag->finishTime,tag->zzTime,(float)tag->zzTime/tag->nTime);
		 
		zztime+=tag->zzTime;
		zztime_right+=(float)tag->zzTime/tag->nTime;
		t+=tag->nTime;
		Sleep(1000);
	}
	
	zztime/=FCFS_Tail->No+1;
	zztime_right/=FCFS_Tail->No+1;
	printf("平均周转时间：%6.1f\n",zztime);
	printf("平均带权周转时间：%6.1f\n",zztime_right);
	
	tag=FCFS_Head;	
	while(tag!=NULL)
	{
		work=tag;
		tag=tag->Next;
		delete work;
	}	
}

void SJF(void)
{
	JCB *work,*tag,*SJF_Head=NULL,*SJF_Tail=NULL,*head=NULL,*tail=NULL;
	int t=0,n=0;
	float zztime_right=0,zztime=0;		//带权周转和周转 
	
	for(tag=Head;tag!=NULL;tag=tag->Next)	//拷贝作业队列 
	{
		work=new JCB();
		work->No=tag->No;
		work->nTime=tag->nTime;
		work->priority=tag->priority;
		if(SJF_Head==NULL)
		{
			SJF_Head=work;			
			SJF_Tail=work;
		}
		else
		{	
			SJF_Tail->Next=work;
			SJF_Tail=SJF_Tail->Next;
		}		
	}
	
	for(n=Tail->No;n>0;n--)													//建立新队列 
	{	
		
		for(tag=SJF_Head->Next,work=SJF_Head;tag!=NULL;tag=tag->Next)		//寻找到最短作业 
			if(tag->nTime < work->nTime)
				work=tag;	
		
		if(work==SJF_Head)													//将找到的作业从队列中删除 
		{
			SJF_Head=SJF_Head->Next;
		}
		else
		{
			for(tag=SJF_Head;tag->Next!=work;tag=tag->Next)
				continue;
			tag->Next=work->Next;
		}
		
		work->Next=NULL;				
		
		if(head==NULL)														//将找到的作业插入新队列 
		{
			head=work;
			tail=work;
		}
		else
		{
			tail->Next=work;
			tail=tail->Next;
		}
	}
	
	printf("\n短作业优先算法（SJF）：\n");
	printf("%10s%15s%10s%10s%15s\n","作业编号","开始运行时刻","完成时刻","周转时间","带权周转时间"); 
	
	for(tag=head;tag!=NULL;tag=tag->Next)
	{
		tag->startRunTime=t;
		tag->finishTime=t+tag->nTime;
		tag->zzTime=tag->finishTime;	//作业均在0时刻被提交给系统 
		printf("%10d%15d%10d%10d%15.1f\n",tag->No,tag->startRunTime,tag->finishTime,tag->zzTime,(float)tag->zzTime/tag->nTime);
		 
		zztime+=tag->zzTime;
		zztime_right+=(float)tag->zzTime/tag->nTime;
		t+=tag->nTime;
		Sleep(1000);
	}
	
	zztime/=Tail->No+1;
	zztime_right/=Tail->No+1;
	printf("平均周转时间：%6.1f\n",zztime);
	printf("平均带权周转时间：%6.1f\n",zztime_right);
	
	tag=head;	
	while(tag!=NULL)
	{
		work=tag;
		tag=tag->Next;
		delete work;
	}
	
}

int main(void)
{
	input();
	FCFS();
	SJF();
	destroy;
    return 0;
}
