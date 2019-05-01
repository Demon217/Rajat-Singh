#include<bits/stdc++.h>
using namespace std;

int nowStep=1;
int minsupport;
vector<vector<int> > transaction;
int mincount=2;
vector<vector<int>>L,C;
unordered_map<int,vector< pair<int,int> > >hashmap;
vector<vector<vector<int> > > frequentset;

vector<vector<int> > joining () 
{
        vector<vector<int> > ret;
        for(int i=0;i<L.size();i++)
	{
            for(int j=i+1;j<L.size(); j++) 
	    {
                int k;
                for(k=0;k<nowStep-1; k++) 
		{
                    if(L[i][k] != L[j][k]) break;
                }
                if(k == nowStep-1) {
                    vector<int> tmp;
                    for(int k=0;k<nowStep-1; k++) {
                        tmp.push_back(L[i][k]);
                    }
                    int a = L[i][nowStep-1];
                    int b = L[j][nowStep-1];
                    if(a>b) swap(a,b);
                    tmp.push_back(a);
		    tmp.push_back(b);
                    ret.push_back(tmp);
                }
            }
        }
        return ret;
}

int getsupport(vector<int> item) 
    {
        int ret = 0;
        for(auto&row:transaction)
	{
            int i, j;
            if(row.size() < item.size()) continue;
            for(i=0, j=0; i < row.size();i++)
	    {
                if(j==item.size()) break;
                if(row[i] == item[j]) j++;
            }
            if(j==item.size())
		{
                ret++;
            	}
        }
        return ret;
    }
    

vector<vector<int> > pruning (vector<vector<int> > joined) 
{
        vector<vector<int> > ret;        
        set<vector<int> > lSet;
        for(auto&row:L) lSet.insert(row);
        for(auto&row:joined)
	{
            int i;
            for(i=0;i<row.size();i++)
	    {
                vector<int> tmp = row;
                tmp.erase(tmp.begin()+i);
                if(lSet.find(tmp) == lSet.end())
                    break;
            }
            if(i==row.size())
                ret.push_back(row);
        }
        return ret;
    }

vector<vector<int> > generateNextC() 
	{	
		if(nowStep==1)
			return C;	
            return pruning(joining());
        }
        
vector<vector<int> > generateL() 
 {
        vector<vector<int> > ret;
        for(auto&row:C)
	{
            if(getsupport(row)>=mincount)	
		{	
			//for(int &i:row)
			//	cout<<i<<"";
            		ret.push_back(row);
			//cout<<"\n";	
		}	
        }
        return ret;
}

void display(vector<vector<int>>k)
	{
		for(auto &row:k)
			{for(auto &col:row)
				cout<<col<<" ";
			cout<<"\n";}
	}

int main()
{
	fstream fin,fout;
	fin.open("input.txt",ios::in);
	fout.open("output.txt",ios::out);
	string s;
	while(fin)
	{		    
		getline(fin,s);
		vector<int>r;
		for(auto &i:s)
			if(i>=48 and i<=57)
				r.push_back(i-'0');
		transaction.push_back(r);
	}

	for(int i=0;i<transaction.size();i++)
		for(int j=0;j<transaction[i].size();j++)
			for(int k=j+1;k<transaction[i].size();k++)
				{
					pair<int,int>p=make_pair(transaction[i][j],transaction[i][k]);
					hashmap[(transaction[i][j]*10+transaction[i][k])%7].push_back(p);			
				}

	for(auto i=hashmap.begin();i!=hashmap.end();i++)
		{
			if((i->second).size()>=minsupport)				
			{	
				vector< pair<int,int> >p=i->second;
				set<pair<int,int>>st;
				for(int i=0;i<p.size();i++)
					st.insert(p[i]);
				for(auto i=st.begin();i!=st.end();i++)
				{
					pair<int,int>p=*(i);	
					vector<int>r;
					r.push_back(p.first);
					r.push_back(p.second);
					C.push_back(r);	
				}
			}
		}
	sort(C.begin(),C.end());
	//display(C);	
	cout<<"\n";	
	while(1)
	{		
		//if(nowStep!=1)		
		C=generateNextC();
		frequentset.push_back(C);
		//display(C);cout<<"\n";	
		nowStep++;
		if(C.size()==0)break;
		L = generateL();
		//display(L);cout<<"\n";	
		//frequentset.push_back(L);	
	}

	for(int i=0;i<frequentset.size();i++)
		{	string ns;
			fout<<"\n";	
			vector<vector<int>>l=frequentset[i];			
			for(auto &row:l)
			{	ns="";	
				for(auto &col:row)
					fout<<col<<" ";
				fout<<"\n";	
			}	
		}	

	fin.close();
	fout.close();
	return 0;
}

