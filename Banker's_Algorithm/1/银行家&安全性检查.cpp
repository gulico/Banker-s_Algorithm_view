#include <iostream.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////////////////////////
//全局变量定义
int Available[100]; //可利用资源数组
int Max[50][100];   //最大需求矩阵
int Allocation[50][100];  //已分配矩阵
int Need[50][100];        //需求矩阵
int Request[50][100];     //M个进程还需要N类资源的资源量
int Finish[50];
int p[50];
int m,n;   //M个进程,N类资源

struct BestRequest{
	int id;
	int request[100];
	int sum;
	bool nav;

}bestRequest[50];
int MaxRequest[100];
/////////////////////////////////////////////////////////////////////////
//安全性算法
bool camp(BestRequest a ,BestRequest b)
{
	return a.sum > b.sum ;			
}
int Safe()                      
{
    int i,j,l=0;
    int Work[100]; //可利用资源数组
    for (i=0;i<n;i++)
        Work[i]=Available[i];
    for (i=0;i<m;i++)
        Finish[i]=0;
    for (i=0;i<m;i++)
    {
        if (Finish[i]==1)
        continue;
        else
        {
            for (j=0;j<n;j++)
            {
                if (Need[i][j]>Work[j])
                    break;
            }
            if (j==n)//本进程全部需要资源都可得
            {
                Finish[i]=1;//标记本进程已经加入队列
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];//当前被本进程占用的所有已分配资源被释放，可利用资源增加。
                p[l++]=i;//本进程序号加入队列p
                i=-1;//从头寻找可执行进程
            }
            else continue;
        }
        if (l==m)//全部进程加入队列
        {
            cout<<"系统是安全的"<<'\n';
            cout<<"系统安全序列是:\n";
            for (i=0;i<l;i++)
            {
                cout<<p[i];
                if (i!=l-1)
                    cout<<"-->";
            }
            cout<<'\n';
            return 1;
        }
    }

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//银行家算法
int main()
{
	FILE *fp = NULL;
	fp = fopen("in.txt", "r");
    int i,j,mi;
	printf("输入进程的数目:\n");
    //cout<<"输入进程的数目:\n";
    //cin>>m;
	fscanf(fp,"%d",&m);
	printf("%d\n",m);
	printf("输入资源的种类:\n");
    //cout<<"输入资源的种类:\n";
    //cin>>n;
	fscanf(fp,"%d",&n);
	printf("%d\n",n);
	printf("输入每个进程最多所需的各类资源数:\n");
    //cout<<"输入每个进程最多所需的各类资源数,按照"<<m<<"x"<<n<<"矩阵输入\n";
    for (i=0;i<m;i++){
        for(j=0;j<n;j++){
			fscanf(fp,"%d",&Max[i][j]);
			printf("%d ",Max[i][j]);
            //cin>>Max[i][j];
		}
		printf("\n");
	}
	printf("输入每个进程已经分配的各类资源数\n");
    //cout<<"输入每个进程已经分配的各类资源数,按照"<<m<<"x"<<n<<"矩阵输入\n";
    for (i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            //cin>>Allocation[i][j];
			fscanf(fp,"%d",&Allocation[i][j]);
			printf("%d ",Allocation[i][j]);
            Need[i][j]=Max[i][j]-Allocation[i][j];
            if (Need[i][j]<0)
            {
                cout<<"你输入的第"<<i+1<<"个进程所拥有的第"<<j+1<<"个资源错误，请重新输入:\n";
                j--;
                continue;
            }
        }
		printf("\n");
    }
    //cout<<"请输入各个资源现有的数目:\n";
	printf("请输入各个资源现有的数目\n");
    for (i=0;i<n;i++){
    //cin>>Available[i];
		fscanf(fp,"%d",&Available[i]);
		printf("%d ",Available[i]);
	}
	printf("\n");
    Safe();
    while (1)
    {
        cout<<"输入要申请的资源的进程号：（第一个进程号为0，第二个进程号为1，依此类推）\n";
        cin>>mi;
        cout<<"输入进程所请求的各个资源的数量\n";
        for (i=0;i<n;i++)
        cin>>Request[mi][i];
		int flag = 1;
        for (i=0;i<n;i++)
        {

            if (Request[mi][i]>Need[mi][i])
            {
				flag=0;
                cout<<"所请求资源数超过进程的需求量！\n";
                break;
            }
            if (Request[mi][i]>Available[i])
            {
				flag=0;
                cout<<"所请求资源数超过系统所有的资源数！\n";
                break;
            }
        }
		
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];//系统可分配减少
            Allocation[mi][i]+=Request[mi][i];//已分配增加
            Need[mi][i]-=Request[mi][i];//本进程需求量减少
        }
        if (Safe()&& flag){
            cout<<"同意分配请求\n";
			for(i=0;i<m;i++){
				bestRequest[i].id = i;
				bestRequest[i].sum = 0;
				bestRequest[i].nav = false;
				for(j=0;j<n;j++){
					bestRequest[i].request[j]=Available[j]-Need[i][j];
					bestRequest[i].sum+=bestRequest[i].request[j];
					if(bestRequest[i].request[j]<0){
						bestRequest[i].nav = true;
					}
				}
			}
			sort(bestRequest,bestRequest+m,camp);//降序
			int sum=0;
			for(i=0;i<m;i++){
				int mm[100];
				int temp = 0;
				if(bestRequest[i].nav)
					continue;
				for(j=0;j<n;j++){
					if(bestRequest[i].request[j] >= Need[mi][j]){
						mm[j] = Need[mi][j];
					}
					else{
						mm[j] = bestRequest[i].request[j];
					}
					temp += mm[j];
				}
				if(temp>sum){
					sum = temp;
					for(j=0;j<n;j++){
						MaxRequest[j] = mm[j];
					}
				}
			}

			if(sum != 0){
				printf("建议请求数组为：\n");
				for(j=0;j<n;j++){
					
					printf("%d ",MaxRequest[j]);
				}
				printf("\n");
			}
			else{
				printf("本进程无法请求\n");
			}
		}
        else
        {
            cout<<"你的请求被拒绝…\n";
            for (i=0;i<n;i++)
            {
                Available[i]+=Request[mi][i];
                Allocation[mi][i]-=Request[mi][i];
                Need[mi][i]+=Request[mi][i];
            }
			for(i=0;i<m;i++){
				bestRequest[i].id = i;
				bestRequest[i].sum = 0;
				bestRequest[i].nav = false;
				for(j=0;j<n;j++){
					bestRequest[i].request[j]=Available[j]-Need[i][j];
					bestRequest[i].sum+=bestRequest[i].request[j];
					if(bestRequest[i].request[j]<0){
						bestRequest[i].nav = true;
					}
				}
			}
			sort(bestRequest,bestRequest+m,camp);//降序
			int sum=0;
			for(i=0;i<m;i++){
				int mm[100];
				int temp = 0;
				if(bestRequest[i].nav)
					continue;
				for(j=0;j<n;j++){
					if(bestRequest[i].request[j] >= Need[mi][j]){
						mm[j] = Need[mi][j];
					}
					else{
						mm[j] = bestRequest[i].request[j];
					}
					temp += mm[j];
				}
				if(temp>sum){
					sum = temp;
					for(j=0;j<n;j++){
						MaxRequest[j] = mm[j];
					}
				}
			}

			if(sum != 0){
				printf("建议请求数组为：\n");
				for(j=0;j<n;j++){
					
					printf("%d ",MaxRequest[j]);
				}
				printf("\n");
			}
			else{
				printf("本进程无法请求\n");
			}
			
        }

        for (i=0;i<m;i++) 
            Finish[i]=0;
    }
	return 0;
}