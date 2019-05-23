#include<bits/stdc++.h>
using namespace std;

bool canallocate(vector< vector<int> >alloc,int psize,int page,int pages,int i)
	{	int c=0;
		if(alloc[i][0]!=0)		
			return false;
		for(int j=i;j<page;j++)
			{	if(alloc[j][0]!=0)
					break;		
				if(alloc[j][0]==0)		
					c+=pages;	
				if(c>=psize)
					return true;
			}
		return false;
	}
void insert(int pno,int psize,vector< vector<int> >&alloc,int page,int pages)
	{	bool flag=false;
		for(int i=0;i<page;i++)
			{
				if(canallocate(alloc,psize,page,pages,i))				
					{	int k=psize;
						for(int a=i;a<page;a++)		
							for(int b=0;b<pages&&k;b++,k--)
							{	alloc[a][b]=pno;
								flag=true;
								if(k==1)
									return;			
							}					
					}
			}
		if(flag==false)
		cout<<"Cant Allocate:\n";
	}

void remove(int pno,vector< vector<int> >&alloc)
	{
		for(int i=0;i<alloc.size();i++)
			for(int j=0;j<alloc[i].size();j++)
				if(alloc[i][j]==pno)
					alloc[i][j]=0;
	}

void display(vector< vector<int> >&alloc)
	{
		for(int i=0;i<alloc.size();i++)
			{for(int j=0;j<alloc[i].size();j++)
					cout<<alloc[i][j]<<" ";
			cout<<"\n";}

	}

int main()
{	int size,page,ch,pno,psize;	
	cout<<"Enter Size of memory:\n";
	cin>>size;
	cout<<"Enter Number Of Pages:\n";
	cin>>page;
	vector<vector<int>>alloc(page,vector<int>(size/page));
	int pages=size/page;	
	for(int i=0;i<page;i++)
		for(int j=0;j<pages;j++)
			alloc[i][j]=0;
	while(1)
	{
		cout<<"1.Insert\t2.Remove\t3.Display\t4.Exit:\n";
		cin>>ch;
		switch(ch)
		{
			case 1:	cout<<"Enter Process No. to be inserted:\n";
				cin>>pno;
				cout<<"Enter Process Size:\n";
				cin>>psize;	
				insert(pno,psize,alloc,page,pages);
				break;
			case 2:	cout<<"Enter Process No. to be inserted:\n";
				cin>>pno;
				remove(pno,alloc);
				break;
			case 3: display(alloc);
				break;	
			default:exit(0);
			
		}
	}
	
}
