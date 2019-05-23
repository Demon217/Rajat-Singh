#include<bits/stdc++.h>
using namespace std;
struct node
{
	int pno;	
	int freq;
	node(int pno,int freq)
		{
			this->pno=pno;
			this->freq=freq;
		}
};

void fifo(int pagem,int pages,vector<int>pageA)
	{	int pf=0;
		vector<int>check;
		for(int i=0;i<pages;i++)
			{
				if(check.size()<pagem)
					{
						check.push_back(pageA[i]);
						pf++;
					}
				else 
					{
						if(find(check.begin(),check.end(),pageA[i])==check.end())
							{		
								check.erase(check.begin());	
								pf++;
								check.push_back(pageA[i]);
							}
					}	

			}
cout<<"Page Faults:"<<pf<<"\n";

	}

void lru(int pagem,int pages,vector<int>pageA)
	{	int pf=0;
		unordered_set<int>st; 	
		unordered_map<int,int>mp;
		for(int i=0;i<pages;i++)
		{
			if(st.size()<pagem)
				{	pf++;
					st.insert(pageA[i]);	
					mp[pageA[i]]=i;
				}
			else
				{
					if(st.find(pageA[i])==st.end())
						{
							int l,leastoc=INT_MAX;								
							for(auto j=st.begin();j!=st.end();j++)
							{
									if(mp[*j]<leastoc)
										{
											leastoc=mp[*j];						
											l=*j;
										}							
							}
							st.erase(l);
							st.insert(pageA[i]);
							pf++;
						}
					mp[pageA[i]]=i;
				}	
		}
cout<<"Page Faults:"<<pf<<"\n";

	}

void searchandremove(vector<node>&cache,unordered_set<int>&st)
	{
		int index,leastfreq=INT_MAX;
		for(int i=0;i<cache.size();i++)
			if(cache[i].freq<leastfreq)
				{leastfreq=cache[i].freq;
				index=i;}
		/*int c=0;
		for(int i=0;i<cache.size();i++)
		  	if(cache[i].freq==cache[index].freq)
				c++;
		if(c>1)
		{
			for(int i=0;i<cache.size();i++)
				if(cache[i].freq==cache[index].freq)
					{index=i;	
					break;}
		}*/
		int val=cache[index].pno;
		st.erase(val);	
		swap(cache[0],cache[index]);	
		cache.erase(cache.begin());
	}	

void lfuinsert(unordered_set<int>&st,int pagem,int val,vector<node>&cache,int &pf,unordered_map<int,int>mp)
{	
	if(cache.size()<pagem)	
		{
			cache.push_back(node(val,mp[val]));			
			st.insert(val);
		}
	else
		{
			searchandremove(cache,st);
			cache.push_back(node(val,mp[val]));			
			st.insert(val);
		}
	pf++;				
}

void lfuincre(int val,vector<node>&cache)
	{
		for(int i=0;i<cache.size();i++)
			if(cache[i].pno==val)
				cache[i].freq++;

	}

void build(unordered_set<int>&st,int pagem,int val,vector<node>&cache,int &pf,unordered_map<int,int>mp)
	{
		if(st.find(val)==st.end())
			lfuinsert(st,pagem,val,cache,pf,mp);	
		else
			lfuincre(val,cache);	
	}

void lfu(int pagem,vector<int>pageA)
	{
		int pf=0;
		unordered_set<int>st;
		vector<node>cache;
		unordered_map<int,int>mp;
		for(int i=0;i<pageA.size();i++)
		{	mp[pageA[i]]++;
			build(st,pagem,pageA[i],cache,pf,mp);
		}
	cout<<"Page Faults:"<<pf<<endl;	
	}

int main()
{
	int pagem,pages,ch;
	cout<<"Enter Page Memory:\n";
	cin>>pagem;
	cout<<"Enter No of pages:\n";
	cin>>pages;
	vector<int>pageA(pages);
	cout<<"Enter Page Sequence:\n";
	for(int i=0;i<pages;i++)
		cin>>pageA[i];
	while(1)
 	{
		cout<<"1.Fifo\t2.Lru\t3.Lfu\t4.Exit:\n";
		cin>>ch;
		switch(ch)
		{
			case 1:	fifo(pagem,pages,pageA);
				break;
			case 2:	lru(pagem,pages,pageA);
				break;
			case 3:	lfu(pagem,pageA);
				break;
			default:exit(0);	
		}	
	}
	return 0;
}
