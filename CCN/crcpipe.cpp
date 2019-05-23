#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int val(char a)
{
	return (a-'0');
}

string mod2(string mes,string key)
{
	string ks="";
	for(int i=0;i<key.size();i++)
		ks+=to_string(val(mes[i])^val(key[i]));
	return ks;
}

string encode(string mes,string key)
{
	int n=key.size();

	while(n>1)
	{
		mes=mes+'0';
		n--;
	}

	string ns=mes.substr(0,key.size());
	ns=mod2(ns,key);
	//cout<<ns<<"\n";
	string lg="";
	for(int i=0;i<key.size();i++)
		lg+='0';
	for(int i=key.size();i<mes.size();i++)	
		{
			ns=ns.substr(1);
			ns+=mes[i];
			if(ns[0]=='1')
				ns=mod2(ns,key);
			else
				ns=mod2(ns,lg);			
			//cout<<ns<<"\n";	
		}
	ns=ns.substr(1);
	mes=mes.substr(0,mes.size()-key.size()+1);
	mes=mes+ns;
	return mes;
}

bool valid(string mes,string key)
{
	int n=key.size();
	string ns=mes.substr(0,key.size());
	ns=mod2(ns,key);
	//cout<<ns<<"\n";
	string lg="";
	for(int i=0;i<key.size();i++)
		lg+='0';
	for(int i=key.size();i<mes.size();i++)	
		{
			ns=ns.substr(1);
			ns+=mes[i];
			if(ns[0]=='1')
				ns=mod2(ns,key);
			else
				ns=mod2(ns,lg);			
			//cout<<ns<<"\n";	
		}
	//cout<<ns<<"\n";
	ns=ns.substr(1);
	int i=0;
	while(ns[i])
	{
		if(ns[i]!='0')
			return false;
		i++;
	}	
	return true;
}

int main()
{	string mes,key;
	cout<<"Enter Message\n";
	cin>>mes;
	cout<<"Enter Key\n";
	cin>>key;
	int sender[2];	
	int receiver[2];
	pid_t p;
	string ack="successful",input;
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
	//cout<<"Enter Input string:\n";
	//cin>>input;
	p=fork();
	if(p<0)
		{
			cout<<"Fork Failed:\n";
			return 1;		
		}
	else if(p>0)
		{
			close(sender[0]);
			input=encode(mes,key);
			int n=input.length();
			char input_to_char[n+1];
			strcpy(input_to_char,input.c_str());
			//for(char i:input_to_char)
			//	cout<<i;
			//cout<<"\n";
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
			string kk="";
			//cout<<sender_read;
			for(int i=0;sender_read[i];i++)
				kk=kk+sender_read[i];
			cout<<kk<<"\n";
			//sender_read[input.size()+ack.size()]='\0';
			string ans;	
			//cout<<kk<<"\n";
			if(valid(kk,key))
				ans="Received Message";
			else
				ans="Resend Message\n";
			close(sender[0]);
			close(receiver[0]);
			char ans_s[ans.size()+1];
			strcpy(ans_s,ans.c_str());
			write(receiver[1],ans_s,strlen(ans_s)+1);
			close(receiver[1]);
			exit(0);			
		}
	return 0;		
}
