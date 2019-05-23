#include<bits/stdc++.h>
using namespace std;

char utility [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

unordered_map<char,int>mp;

string compliment(string s)
	{
		string up="FFFF";
		for(int i=0;i<s.size();i++)	
			s[i]=utility[mp[up[i]]-mp[s[i]]];
		return s;
	}


string oneadd(string a,string b)
{	string ns="";
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	int carry=0;
	for(int i=0;i<a.size();i++)	
		{
			int val=mp[a[i]]+mp[b[i]]+carry;
			ns+=utility[val%16];		
			carry=val/16;	
		}
	if(carry)
		{
			string cr=to_string(carry);
			while(cr.size()<4)
				cr = cr + '0';
			carry=0;
			for(int i=0;i<ns.size();i++)
				{
					int val=mp[ns[i]]+mp[cr[i]]+carry;
					ns[i]=utility[val%16];		
					carry=val/16;
				}
		}
	reverse(ns.begin(),ns.end());
	return ns;
}

int main()
{	
	for(int i=0;i<16;i++)
		mp[utility[i]]=i;
	vector<string>data;
	int ch;
	string input;	
	while(1)
	{
		cin>>input;
		data.push_back(input);
		cout<<"Want to transmit more data(1/0):\n";
		cin>>ch;
		if(ch==0)break;
	}
	cout<<"-----------------Sender Side --------------\n";
	cout<<"Data to be transfered :\n";
	for(string s:data)cout<<s<<" ";
	cout<<"\n";
	string checksum="0000";	
	for(int i=0;i<data.size();i++)
		checksum=oneadd(checksum,data[i]);
	cout<<"checksum value"<<checksum<<"\n";
	checksum=compliment(checksum);
	cout<<"checksum compliment:"<<checksum<<"\n";
	data.push_back(checksum);
	cout<<"Transfered data :\n";
	for(string s:data)cout<<s<<" ";
	cout<<"\n";	
	cout<<"================Receiver Side ============\n";
	checksum="0000";
	for(int i=0;i<data.size();i++)
		checksum=oneadd(checksum,data[i]);
	//cout<<checksum<<"\n";
	bool flag=false;
	// checksum[2]='B';  ERROR GENERATION
	checksum=compliment(checksum);	
	for(char a:checksum)
		if(a!='0')
			flag=true;
	if(flag)cout<<"Retransfer data\n";
	else
		{
			data.pop_back();
			cout<<"Received data\n";
			for(string s:data)cout<<s<<" ";
		}	
	return 0;
}
