#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>	ipair;
class kruskal
{
	int v,e;
	int *par,*rank;
	vector< pair<int,ipair> > edge;
	public:
	kruskal(int v,int e)
	{
		this->v=v;
		this->e=e;
		par=new int[v];
		rank=new int[v];
		for(int i=0;i<v;i++)
		{	
			rank[i]=0;	
			par[i]=i;
		}		
	}

	void add(int a,int b,int wt)	
	{	
		pair<int,int>p=make_pair(a,b);
		edge.push_back(make_pair(wt,p));
	}
	
	int findp(int u)
	{
		if(par[u]!=u)	
			par[u]=findp(par[u]);
		return par[u];
	}

	void merge(int a,int b)
	{
		a=findp(a);
		b=findp(b);
		if(rank[a]>rank[b])
			par[b]=a;
		else
			par[a]=b;
		if(rank[a]==rank[b])
			rank[b]++;	
	}
	
	void span()
	{	
		sort(edge.begin(),edge.end());	
		for(auto i=edge.begin();i!=edge.end();i++)
		{
			pair<int,int>p=(*i).second;
			int a=p.first;
			int b=p.second;
			int wt=(*i).first;
			int set_a=findp(a);
			int set_b=findp(b);
			if(set_a!=set_b)
			{	
				cout<<a<<"-----"<<b<<"----"<<wt<<"\n";
				merge(set_a,set_b);
			}			
		}
	}
};	

int main()
{
	int v,e;
	cout<<"Enter No Of Nodes and Edges:\n";
	cin>>v>>e;
	kruskal m(v,e);
	for(int i=0;i<e;i++)
	{
		int a,b,wt;
		cout<<"Enter Src , Dest ,Weight:\n";
		cin>>a>>b>>wt;
		m.add(a,b,wt);		
	}
	m.span();
	return 0;
}
