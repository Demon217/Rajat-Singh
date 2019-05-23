#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> ipair;
class mst
	{
		int v;	
		list<pair<int,int>>*adj;
		public:
		mst(int v)
		{	
			this->v=v;
			adj=new list<pair<int,int>>[v];
		}

		void addedge(int a,int b,int wt)
		{
			adj[a].push_back(make_pair(b,wt));
			adj[b].push_back(make_pair(a,wt));
		}	

		void span(int src)
		{
			int dist[v];
			bool vis[v];
			int par[v]={0};
			for(int i=0;i<v;i++)
			{
				dist[i]=INT_MAX;
				vis[i]=false;	
			}
			priority_queue<ipair,vector<ipair>,greater<ipair>>pq;			
			pq.push(make_pair(0,src));
			dist[src]=0;
			par[src]=-1;
			while(!pq.empty())
			{	
				int u=pq.top().second;
				vis[u]=true;
				pq.pop();
				for(auto i=adj[u].begin();i!=adj[u].end();i++)
				{
					int v=(*i).first;
					int wt=(*i).second;	
					if(vis[v]==false&&dist[v]>wt)
					{	
						dist[v]=wt;
						par[v]=u;
						pq.push(make_pair(wt,v));
					}		
				}
			}
			for(int i=0;i<v;i++)
				cout<<par[i]<<"-->"<<i<<"--->"<<dist[i]<<"\n";	
		}	
	};	


int main()
{	
	int n,e;
	cout<<"Enter Number Of Nodes:\n";
	cin>>n;		
	cout<<"Enter Number Of Edges:\n";
	cin>>e;
	mst m(n);
	for(int i=0;i<e;i++)
	{
		int a,b,wt;
		cout<<"Enter Node Src , Dest , Wt:\n";
		cin>>a>>b>>wt;
		m.addedge(a,b,wt);	
	}	
	int src;
	cout<<"Enter Source:\n";
	cin>>src;
	m.span(src);
	return 0;
}
