#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
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
	string input;	
	int ch;	
	while(1)
	{
		cin>>input;
		data.push_back(input);
		cout<<"Want to transmit more data(1/0):\n";
		cin>>ch;
		if(ch==0)break;
	}
	
        int sender[2];	
	int receiver[2];
	pid_t p;
	string ack="successful";
	if(pipe(sender)==-1)
		{
			cout<<"Pipe Failed\n";
			return 1;
		}
	if(pipe(receiver)==-1)
		{
			cout<<"Pipe Failed\n";
			return 1;
		}
	p=fork();
	if(p<0)
		{
			cout<<"Fork Failed:\n";
			return 1;		
		}
	else if(p>0)
		{
			close(sender[0]);
			string checksum="0000";	
			for(int i=0;i<data.size();i++)
				checksum=oneadd(checksum,data[i]);
			checksum=compliment(checksum);
			data.push_back(checksum);
			string input="";
			for(string s:data)
				{	input+=s;
					input=input+" ";
				}
			char input_to_char[input.size()+1];	
			strcpy(input_to_char,input.c_str());
			write(sender[1],input_to_char,strlen(input_to_char)+1);
			close(sender[1]);
			wait(NULL);
			close(receiver[1]);
			char child_read[100];
			read(receiver[0],child_read,100);
			cout<<"Parent Part:\n";
			for(int i=0;child_read[i];i++)
				cout<<child_read[i];
			cout<<"\n";
			close(receiver[0]);	
		}	
	else	{
			close(sender[1]);
			char sender_read[100];	
			read(sender[0],sender_read,100);
			int k=strlen(sender_read);
			data.clear();
			string ns="";
			for(int i=0;i<k;i++)
				{
					if(sender_read[i]!=' ')
						ns+=sender_read[i];
					else
						{
							data.push_back(ns);
							ns="";		
						}	
				}
			//data.push_back(ns);
			for(string s:data)cout<<s.size()<<" ";
			string checksum="0000";
			string ans;
			for(int i=0;i<data.size();i++)
				checksum=oneadd(checksum,data[i]);
			//cout<<checksum;			
			checksum=compliment(checksum);	
			bool flag=false;
			for(char a:checksum)
				if(a!='0')
					flag=true;
			if(flag)ans="Retransfer data";
			else ans="Received data success";
			close(sender[0]);
			close(receiver[0]);
			char ans_read[ans.size()+1];
			strcpy(ans_read,ans.c_str());
			write(receiver[1],ans_read,strlen(ans_read)+1);
			close(receiver[1]);
			exit(0);			
		}
	return 0;		
}
