#include<bits/stdc++.h>
using namespace std;
//int tt=0;
struct node
{
	int item; //item set
	int count; // item set count
	vector<node*> child; // its children node
	node *parent; // ptr to parent
};

bool cmp(pair<int,int>a,pair<int,int>b)
{
		return a.second > b.second;
}

vector<vector<int>>freqset;
vector<vector<int>>trans;
//vector<pair<int,vector<node*>>>header_table;		// node mapping for each node
vector< pair<int,int> >desc_sorted_freq_map;	 // sorted form
map<int,int>freq_map;								// items count
int minsup=2;
vector<node*>root;


/*void conditionalfp(vector<pair<int,int>>res,int val,int f)
{
	vector<pair<int,int>>rk;
	for(int i=0;i<res.size();i++)
	{
		if(res[i].second>=f)
			rk.push_back(res[i]);
	}zz

}
*/
void conditionalpatt(vector<vector<pair<int,int>>>res)
{
	unordered_map<int,int>mp;
	int ele;
	for(int i=0;i<res.size();i++)
	{
		pair<int,int>s=res[i][res[i].size()-1];
		res[i].pop_back();
		int v = s.second;
		ele = s.first;
		for(int j=0;j<res[i].size();j++)
				mp[res[i][j].first]+=v;
	}
	vector<int>ans;
	for(auto i=mp.begin();i!=mp.end();i++)
	{
			if(i->second>=minsup)
				ans.push_back(i->first);
	}
	vector<vector<int>>subset;

	for(int i=0;i<(int)pow(2,ans.size());i++)
	{
		vector<int>temp;
		for(int j=0;j<ans.size();j++)
				if( i& (1<<j))
						temp.push_back(ans[j]);
		subset.push_back(temp);
	}

	for(int i=0;i<subset.size();i++)
		subset[i].push_back(ele);

	for(int i=0;i<subset.size();i++)
		freqset.push_back(subset[i]);
}

void mineutil(vector<node*>head,vector<vector<pair<int,int>>>&res,pair<int,int>ref[],int index,int val)
{
	for(int i=0;i<head.size();i++)
	{
		if(head[i]->item==val)
		{
			ref[index]=make_pair(head[i]->item,head[i]->count);
			vector<pair<int,int>>p;
			for(int i=0;i<=index;i++)
			p.push_back(ref[i]);
			res.push_back(p);
			//return;
		}else
		{
		ref[index]=make_pair(head[i]->item,head[i]->count);
		mineutil(head[i]->child,res,ref,index+1,val);
		}
	}
}

void mining()
{
	reverse(desc_sorted_freq_map.begin(),desc_sorted_freq_map.end());
	for(int i=0;i<desc_sorted_freq_map.size();i++)
	{
		vector<vector<pair<int,int>>>res;
		pair<int,int>ref[1000];
		mineutil(root,res,ref,0,desc_sorted_freq_map[i].first);
		/*for(int i=0;i<res.size();i++)
		{
			for(int j=0;j<res[i].size();j++)
				cout<<res[i][j].first;
			cout<<"\n";
		}*/
		conditionalpatt(res);
  }
}


/*void initialise_header_table()
{
	vector<node*>temp;
	for(int i=0;i<desc_sorted_freq_map.size();i++)
		header_table.push_back(make_pair(desc_sorted_freq_map[i].first,temp));
}
*/

void insertx(vector<node*>&head,vector<int>item,int str,node *ptr)
{
	bool found=false;
	if(head.size()>0)
	{
		for (int j=0;j<head.size();j++)
		{
			if(head[j]->item==item[str])
			{
				found=true;
				head[j]->count++;
				if(str+1<item.size())
					insertx(head[j]->child,item,str+1,head[j]);
			}
		}
	}
	if(!found)
	{
		node *new_node = new node;
		new_node->item=item[str];
		new_node->count=1;
		new_node->parent=ptr;
		new_node->child.clear();
		if(str+1<item.size())
		{
			insertx(new_node->child,item,str+1,new_node);
		}
		head.push_back(new_node);
		//cout<<"a"<<"\n";
	}
//	cout<<tt++;
}

void tree_creation()
{
	for(int i=0;i<trans.size();i++)
	{
			vector<int>element_eligible_from_trans;
			unordered_set<int>st;
			for(int j=0;j<trans[i].size();j++)
					st.insert(trans[i][j]);
			for(int j=0;j<desc_sorted_freq_map.size();j++)
				{
						if(st.find(desc_sorted_freq_map[j].first)!=st.end())
							element_eligible_from_trans.push_back(desc_sorted_freq_map[j].first);
					//cout<<"transaction"<<i<<"\n";
				}
			if(element_eligible_from_trans.size()>0)
				insertx(root,element_eligible_from_trans,0,NULL);
	}
}
void output_tree()
{
	queue< vector<node*> >q;
	queue< vector<node*> >p;
	q.push(root);
	int l=1;
	cout<<"Level 1\n";
	while(!q.empty())
	{
		vector<node*>temp=q.front();
		q.pop();
		if(temp.size()>0)
		{
			//q.push(empty);
			//if(temp[0]->parent)
			//cout<<"parent "<<temp[0]->parent->item;//<<" freq "<<temp[0]->parent->count<<"\n";
			//else cout<<"NULL\n";
			for (int i = 0; i < temp.size(); ++i)
			{
				//cout<<temp[i]->item<<"-->>"<<temp[i]->count<<"\n";
				if(temp[i]->child.size()>0)
						p.push(temp[i]->child);
			}
			//cout<<"\n";
		}
		if(q.size()==0)
		{	l++;
			cout<<"Level"<<l<<"\n";
			q=p;
			queue<vector<node*>>t;
			p=t;
		}
	}
		/*temp = q.front();
	 	q.pop();
	 	if(temp.size()==0)
	 	{
	 		cout<<"\n";
	 		if(q.size()==0)
	 			break;
	 		else
	 			q.push(temp);
	 	}
    else
	 		q.push(temp);
		}*/
}

void printfreqpatt()
{
	for(int i=0;i<freqset.size();i++)
	{
		for(int j=0;j<freqset[i].size();j++)
			cout<<freqset[i][j]<<" ";
		cout<<"\n";
	}
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

	for(auto i:trans)for(auto j:i)freq_map[j]++;		//map items_sets
	map<int,int>temp;

	for(auto i=freq_map.begin();i!=freq_map.end();i++)
			{
					if(i->second>=minsup)
							temp[i->first]=i->second;
			}
	freq_map=temp;																// minimum support set
	for(auto i=freq_map.begin();i!=freq_map.end();i++)
			{	//cout<<i->first<<" ";
				desc_sorted_freq_map.push_back(make_pair(i->first,i->second));
			}
	stable_sort(desc_sorted_freq_map.begin(),desc_sorted_freq_map.end(),cmp);
	//for(int i=0;i<desc_sorted_freq_map.size();i++)
		//			cout<<desc_sorted_freq_map[i].first<<" ";
	//initialise_header_table();									// header table call
	tree_creation();
	//output_tree();
	mining();
	printfreqpatt();
	return 0;
}

