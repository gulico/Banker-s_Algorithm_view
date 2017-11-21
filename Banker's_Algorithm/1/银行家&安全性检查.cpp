#include <iostream.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////////////////////////
//ȫ�ֱ�������
int Available[100]; //��������Դ����
int Max[50][100];   //����������
int Allocation[50][100];  //�ѷ������
int Need[50][100];        //�������
int Request[50][100];     //M�����̻���ҪN����Դ����Դ��
int Finish[50];
int p[50];
int m,n;   //M������,N����Դ

struct BestRequest{
	int id;
	int request[100];
	int sum;
	bool nav;

}bestRequest[50];
int MaxRequest[100];
/////////////////////////////////////////////////////////////////////////
//��ȫ���㷨
bool camp(BestRequest a ,BestRequest b)
{
	return a.sum > b.sum ;			
}
int Safe()                      
{
    int i,j,l=0;
    int Work[100]; //��������Դ����
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
            if (j==n)//������ȫ����Ҫ��Դ���ɵ�
            {
                Finish[i]=1;//��Ǳ������Ѿ��������
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];//��ǰ��������ռ�õ������ѷ�����Դ���ͷţ���������Դ���ӡ�
                p[l++]=i;//��������ż������p
                i=-1;//��ͷѰ�ҿ�ִ�н���
            }
            else continue;
        }
        if (l==m)//ȫ�����̼������
        {
            cout<<"ϵͳ�ǰ�ȫ��"<<'\n';
            cout<<"ϵͳ��ȫ������:\n";
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
//���м��㷨
int main()
{
	FILE *fp = NULL;
	fp = fopen("in.txt", "r");
    int i,j,mi;
	printf("������̵���Ŀ:\n");
    //cout<<"������̵���Ŀ:\n";
    //cin>>m;
	fscanf(fp,"%d",&m);
	printf("%d\n",m);
	printf("������Դ������:\n");
    //cout<<"������Դ������:\n";
    //cin>>n;
	fscanf(fp,"%d",&n);
	printf("%d\n",n);
	printf("����ÿ�������������ĸ�����Դ��:\n");
    //cout<<"����ÿ�������������ĸ�����Դ��,����"<<m<<"x"<<n<<"��������\n";
    for (i=0;i<m;i++){
        for(j=0;j<n;j++){
			fscanf(fp,"%d",&Max[i][j]);
			printf("%d ",Max[i][j]);
            //cin>>Max[i][j];
		}
		printf("\n");
	}
	printf("����ÿ�������Ѿ�����ĸ�����Դ��\n");
    //cout<<"����ÿ�������Ѿ�����ĸ�����Դ��,����"<<m<<"x"<<n<<"��������\n";
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
                cout<<"������ĵ�"<<i+1<<"��������ӵ�еĵ�"<<j+1<<"����Դ��������������:\n";
                j--;
                continue;
            }
        }
		printf("\n");
    }
    //cout<<"�����������Դ���е���Ŀ:\n";
	printf("�����������Դ���е���Ŀ\n");
    for (i=0;i<n;i++){
    //cin>>Available[i];
		fscanf(fp,"%d",&Available[i]);
		printf("%d ",Available[i]);
	}
	printf("\n");
    Safe();
    while (1)
    {
        cout<<"����Ҫ�������Դ�Ľ��̺ţ�����һ�����̺�Ϊ0���ڶ������̺�Ϊ1���������ƣ�\n";
        cin>>mi;
        cout<<"�������������ĸ�����Դ������\n";
        for (i=0;i<n;i++)
        cin>>Request[mi][i];
		int flag = 1;
        for (i=0;i<n;i++)
        {

            if (Request[mi][i]>Need[mi][i])
            {
				flag=0;
                cout<<"��������Դ���������̵���������\n";
                break;
            }
            if (Request[mi][i]>Available[i])
            {
				flag=0;
                cout<<"��������Դ������ϵͳ���е���Դ����\n";
                break;
            }
        }
		
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];//ϵͳ�ɷ������
            Allocation[mi][i]+=Request[mi][i];//�ѷ�������
            Need[mi][i]-=Request[mi][i];//����������������
        }
        if (Safe()&& flag){
            cout<<"ͬ���������\n";
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
			sort(bestRequest,bestRequest+m,camp);//����
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
				printf("������������Ϊ��\n");
				for(j=0;j<n;j++){
					
					printf("%d ",MaxRequest[j]);
				}
				printf("\n");
			}
			else{
				printf("�������޷�����\n");
			}
		}
        else
        {
            cout<<"������󱻾ܾ���\n";
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
			sort(bestRequest,bestRequest+m,camp);//����
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
				printf("������������Ϊ��\n");
				for(j=0;j<n;j++){
					
					printf("%d ",MaxRequest[j]);
				}
				printf("\n");
			}
			else{
				printf("�������޷�����\n");
			}
			
        }

        for (i=0;i<m;i++) 
            Finish[i]=0;
    }
	return 0;
}