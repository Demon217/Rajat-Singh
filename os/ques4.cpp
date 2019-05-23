#include<bits/stdc++.h>
using namespace std;

void build(vector< vector<int> >&need,vector< vector<int> >maxA,vector< vector<int> >alloc,int n,int m)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			need[i][j]=maxA[i][j]-alloc[i][j];
}

void check(vector<int>proc,vector<int>avail,vector< vector<int> >maxA,vector< vector<int> >alloc,int n,int m)
{
	vector< vector<int> >need(n,vector<int>(m));
	build(need,maxA,alloc,n,m);
	vector<int>finish(n);
	vector<int>seq(n);
	vector<int>res=avail;
	int count=0;
	while(count<n)
	{
		bool flag=false;		
		for(int i=0;i<n;i++)
		{
			if(finish[i]==0)
			{	int j;
				for(j=0;j<m;j++)
					if(res[j]<need[i][j])									
						break;
				if(j==m)
					{
						for(int k=0;k<m;k++)	
							res[k]+=alloc[i][k];
						finish[i]=1;
						seq[count]=i;		
						count++;
						flag=true;
					}		
			}	
			
		}
	if(flag==false)
		{cout<<"Not safe state:\n";	
		return;}
	}
cout<<"Safe Sequence is:\n";
for(int i=0;i<n;i++)
	cout<<seq[i]<<" ";			
}

int main()
{
	int n,m;
	cout<<"Enter No of process:\n";
	cin>>n;
	cout<<"Enter No of resources:\n";
	cin>>m;
	vector< vector<int> >maxA(n,vector<int>(m)),alloc(n,vector<int>(m));
	vector<int>proc(n),avail(m);	
	for(int i=0;i<n;i++)
		proc[i]=i;
	for(int i=0;i<m;i++)
		cin>>avail[i];
	cout<<"Max Allocation for each process:\n";	
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>maxA[i][j];
	cout<<"Allocated Resource for each process:\n";
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>alloc[i][j];
	check(proc,avail,maxA,alloc,n,m);				
	return 0;
}
