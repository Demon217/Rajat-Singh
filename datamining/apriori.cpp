#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>L,C,trans;
int minsup=2,nowstep=0;

vector< vector<int> >joining()
{		vector< vector<int> >ret;
		for(int i=0;i<L.size();i++)
			{
				for(int j=i+1;j<L.size();j++)
					{
							int k;
							for(k=0;k<nowstep-1;k++)
							{
									if(L[i][k]!=L[j][k])
										break;
							}
							if(k==nowstep-1)
							{
								vector<int>temp;
								for(int k=0;k<nowstep-1;k++)
									temp.push_back(L[i][k]);
								int a=L[i][nowstep-1];
								int b=L[j][nowstep-1];
								if(a>b)
								swap(a,b);
								temp.push_back(a);
								temp.push_back(b);
								ret.push_back(temp);
							}
					}
			}
		return ret;
}

vector< vector<int> >prunning(vector< vector<int> >joined)
{
	vector< vector<int> >ret;
	set< vector<int> >st;
	for(auto &i:L)
			st.insert(i);
	for(auto &row:joined)
	{	int i;
		for(i=0;i<row.size();i++)
		{
			vector<int>temp=row;
			temp.erase(temp.begin()+i);
			if(st.find(temp)==st.end())
				break;
		}
		if(i==row.size())
			ret.push_back(row);
	}
	return ret;
}

vector< vector<int> >generateC()
{
		if(nowstep==0)
		{
				vector<vector<int>>ret;
				set<int>st;
				for(auto row:trans) for(auto col:row)	st.insert(col);
				for(auto i=st.begin();i!=st.end();i++)
						ret.push_back(vector<int>(1,*(i)));
				return ret;
		}
		else
		{
			return prunning(joining());
		}
}

int getsupport(vector<int>r)
{	int c=0,count;
	unordered_set<int>st;
	for(auto i:r)
		st.insert(i);
	for(int i=0;i<trans.size();i++)
	{		count=0;
			for(int j=0;j<trans[i].size();j++)
			{
					if(st.find(trans[i][j])!=st.end())
								count++;
			}
			if(count==r.size())
				c++;
	}
	return c;
}

vector< vector<int> >generateL()
	{
			vector< vector<int> >ret;
			for(auto row:C)
				{
						if(getsupport(row)>=minsup)
									ret.push_back(row);
				}
			return ret;
	}

int main()
{
	fstream fin,fout;
	string s;
	fin.open("input.txt",ios::in);
	while(fin)
	{
		getline(fin,s);
		vector<int>temp;
		for(int i=0;i<s.size();i++)
			if(isdigit(s[i]))
				temp.push_back(s[i]-'0');
		trans.push_back(temp);
	}

	for(auto row:trans)
	{
		for(auto col:row)
			cout<<col<<" ";
		cout<<"\n";
	}

	while(1)
	{
		C=generateC();
		if(C.size()==0)
			break;
		nowstep++;
		L=generateL();
		fout.open("output.txt",ios::app);
		for(auto &row:L)
		{
			for(auto &col:row)
				fout<<col<<" ";
			fout<<"\n";
		}
		fout.close();
	}
	fin.close();
	return 0;
}
