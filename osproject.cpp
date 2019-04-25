/*
Ques. 7.  Design a scheduling program to implements a Queue with two levels:
Level 1 : Fixed priority preemptive Scheduling
Level 2 : Round Robin Scheduling
For a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority.If one process P1 is scheduled and running , another process P2 with higher priority comes.
The New process (high priority) process P2 preempts currently running process P1 and process P1 will go to second level queue.
Time for which process will strictly execute must be considered in the multiples of 2.
All the processes in second level queue will complete their execution according to round robin scheduling.
Consider: 1. Queue 2 will be processed after Queue 1 becomes empty.
		  2. Priority of Queue 2 has lower priority than in Queue 1.
*/
#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
struct process
{
	int aT,bT,copy_bT,pN,cT,wT,tAT;         //aT=ArrivalTime,bT=BurstTime,pN=PriorityNumber,cT=CompletionTime,wT=WaitingTime
	string processId;                      //processId=ProcessName
};
int findMin(process [],int);
int findIndex(int,string,process []);
int m=0,cTsetter=0,checker=0,checker1=0;
class Scheduling
{
	int noprocess,var,indef,var1,timer,minPriority,pPI,pIvar,x,previousminpriority;
	process pro[50];
	string previouspro;
	vector<string> q1,q2;                                   // two Queues            q1= Priority Preemptive Scheduling, q2=Round Robin Scheduling
	vector<int> prioritySelector;
	public:

		void getData()
		{
			cout<<"\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
			cout<<"\t\t\t|\t\t\tCPU Scheduling  (Multi-Level)           |"<<endl;
			cout<<"\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<<endl;
			cout<<"  Enter the number of processes :- ";
			cin>>noprocess;
			if(noprocess==0)
				exit(0);
			int p=65;
			for(int i=0;i<noprocess;i++)
			{
				pro[i].processId=char(p);
				cout<<"  Enter  Arrival time  ||   Burst Time   ||   Priority for process ["<<pro[i].processId<<"] respectively"<<endl;
				cout<<"  --> ";
				cin>>pro[i].aT;
				cin>>pro[i].bT;
				pro[i].copy_bT=pro[i].bT;
				cin>>pro[i].pN;
				pro[i].cT=0;
				p++;
			}
		}

		void findMinInArrivalTime()
		{
			int minval;
			minval=findMin(pro,noprocess);
			for(int i=0;i<noprocess;i++)
			{
				if(pro[i].aT==minval)
				{
					q1.push_back(pro[i].processId);
					prioritySelector.push_back(pro[i].pN);
				}
			}
		}

		void processSelector()
		{
			minPriority=*(std::min_element(prioritySelector.begin(),prioritySelector.end()));
			for(int i=0;i<prioritySelector.size();i++)
			{
				if(minPriority==prioritySelector.at(i))
				{
					var=i;
					break;
				}
			}
			for(int i=0;i<noprocess;i++)
			{
				if(pro[i].processId==q1[var])
				{
					var1=i;
				}
			}
			if(m>=1)
			{
				if(q1[var]!=previouspro)
				{
					q1.erase(std::remove(q1.begin(),q1.end(),previouspro),q1.end());
					if(checker==0)
					{
						prioritySelector.erase(prioritySelector.begin()+pIvar,prioritySelector.begin()+(pIvar+1));
					}
					else
					{
						checker=0;
					}
					if(pro[pPI].bT!=0)
					{
						q2.push_back(previouspro);
					}
				}
			}
			m+=1;
			pIvar=var;
			previouspro=q1[var];
			previousminpriority=minPriority;
			pPI=var1;
			if(checker1==1)
			{
				startQ1Process();
			}
		}

		void startQ1Process()
		{
			while(q1.size()!=0)
			{
				checker1+=1;
				int con=0;
				if(pro[var1].bT==0)
				{
					for(int i=0;i<q1.size();i++)
					{
						if(q1.at(i)==pro[var1].processId)
						{
							indef=i;
						}
					}
					q1.erase(std::remove(q1.begin(),q1.end(),q1.at(indef)),q1.end());
					prioritySelector.erase(prioritySelector.begin()+indef,prioritySelector.begin()+(indef+1));
					checker=1;
					if(q1.size()==0)
					{
						checker1=0;
						checker=0;
						break;
					}
					processSelector();
				}
				if(cTsetter==0)
				{
					pro[var1].cT=pro[var1].aT;
					cTsetter=1;
				}
				else
				{
					pro[var1].cT=timer;
				}
				pro[var1].bT-=1;
				pro[var1].cT+=1;
				timer=pro[var1].cT;
				for(int i=0;i<noprocess;i++)
				{
					if(timer==pro[i].aT)
					{
						q1.push_back(pro[i].processId);
						prioritySelector.push_back(pro[i].pN);
						con=1;
					}
				}
				if(con==1)
				{
					processSelector();
				}
			}
			if(q2.size()!=0)
			{
				startQ2process();
			}
		}

		void startQ2process()
		{
			int TQ=2,index2;
			string pI,preprocess;
			pI=q2.at(0);
			index2=findIndex(noprocess,pI,pro);
			while(q2.size()!=0)
			{
				pro[index2].cT=timer;
				if(pro[index2].bT==1)
				{
					pro[index2].bT-=1;
					pro[index2].cT+=1;
				}
				else
				{
					pro[index2].bT-=TQ;
					pro[index2].cT+=TQ;
				}
				timer=pro[index2].cT;
				if(pro[index2].bT==0)
				{
					q2.erase(std::remove(q2.begin(),q2.end(),pro[index2].processId),q2.end());
				}
				else
				{
					preprocess=pro[index2].processId;
					q2.erase(std::remove(q2.begin(),q2.end(),pro[index2].processId),q2.end());
					q2.push_back(preprocess);
				}
				for(int i=0;i<noprocess;i++)
				{
					if(timer==pro[i].aT)
					{
						q1.push_back(pro[i].processId);
						prioritySelector.push_back(pro[i].pN);
					}
				}
				if(q1.size()!=0)
				{
					checker1=1;
					m=0;
					processSelector();
				}
				if(q2.size()==0)
				{
					break;
				}
				pI=q2.at(0);
				index2=findIndex(noprocess,pI,pro);
			}
		}

		void check()
		{
			x=pro[0].aT;
			for(int i=0;i<noprocess;i++)
			{
				if(pro[i].aT>x)
				{
					x=pro[i].aT;              // finding te maximum aT
				}
			}
			while(timer<=x)
			{
				int cod=0;
				timer++;
				for(int i=0;i<noprocess;i++)
				{
					if(timer==pro[i].aT)
					{
						q1.push_back(pro[i].processId);
						prioritySelector.push_back(pro[i].pN);
						cod=1;
					}
				}
				if(cod==1)
				{
					m=0;
					checker1=1;
					processSelector();
				}
			}
		}

		void display()
		{
			cout<<"  Data set given by User"<<endl;
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
			cout<<"  |  ProcessID \t\t\tArrival Time\t\t\tBurst Time\t\t\tPriority        |"<<endl;
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
			for(int i=0;i<noprocess;i++)
			{
				cout<<"  |  "<<pro[i].processId<<"\t\t\t\t"<<pro[i].aT<<"\t\t\t\t"<<pro[i].bT<<"\t\t\t\t"<<pro[i].pN<<"\t        |"<<endl;
			}
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl<<endl;
		}

		void finalResult()
		{
			float avgwT=0;
			cout<<"  +*************************************************************************************************************+"<<endl;
			cout<<"  |\t\t\t\t\tFinal result  timing table of processes\t\t\t\t\t        |"<<endl;
			cout<<"  +*************************************************************************************************************+"<<endl;
			cout<<"  |  PId"<<"\t||\t"<<"AT"<<"\t||\t"<<"BT"<<"\t||\t"<<"CT"<<"\t||\t"<<"TAT"<<"\t||\t  "<<"WT"<<"\t\t        |"<<endl;
			cout<<"  +*************************************************************************************************************+"<<endl;
			for(int i=0;i<noprocess;i++)
			{
				pro[i].tAT=pro[i].cT-pro[i].aT;
				pro[i].wT=pro[i].tAT-pro[i].copy_bT;
				avgwT+=pro[i].wT;
				cout<<"  |  "<<pro[i].processId<<"\t\t||\t"<<pro[i].aT<<"\t||\t"<<pro[i].copy_bT<<"\t||\t"<<pro[i].cT<<"\t||\t"<<pro[i].tAT<<"\t||\t  "<<pro[i].wT<<"\t\t        |"<<endl;
				cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
			}
			cout<<"  |\t\t\t\t\tAverage waiting time : "<<avgwT/noprocess<<"\t\t\t\t\t\t|"<<endl;
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
		}
};
int main()
{
	Scheduling sc;
	sc.getData();
	sc.display();
	sc.findMinInArrivalTime();
	sc.processSelector();
	sc.startQ1Process();
	sc.check();
	sc.finalResult();
}
int findMin(process pro[], int noprocess)
{
    int mn=pro[0].aT;
    for(int i=0;i<noprocess;i++)
	{
        int temp=pro[i].aT;
        mn=std::min(mn,temp);
    }
    return mn;
}
int findIndex(int noprocess,string pI,process pro[])
{
	int in;
	for(int i=0;i<noprocess;i++)
	{
		if(pI==pro[i].processId)
		{
			in=i;
		}
	}
	return in;
}
