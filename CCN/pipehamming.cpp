#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

int build(int n)
{	int r=0;			
	while((int)pow(2,r)<n+r+1)
		r++;
	return r;
}

string generate(int i)
{
	string ns="";
	while(i)
	{	ns+=to_string(i%2);	
		i=i/2;	}
	return ns;
}

vector<int>location(vector<string>bitrep,int r)
{	vector<int>l;
	for(int i=0;i<bitrep.size();i++)
		{	
			if(r>bitrep[i].size())
				continue;
			if(bitrep[i][r-1]=='1')
				l.push_back(i);	
		}	
	return l;
}

bool valid(vector<string>bitrep,vector<int>data)
{	string ns="";
	int l=0;
	for(int i=0;i<data.size();i++)
	{
		if(i==(int)pow(2,l)-1)
			{	l++;
				int sum=0;								
				vector<int>loc=location(bitrep,l);
				//for(int i:loc)cout<<i<<" ";cout<<"\n";
				for(int j=0;j<loc.size();j++)	
					sum+=data[loc[j]];
				if(sum&1)
					ns+=to_string(1);
				else
					ns+=to_string(0);	
			}
	}	
	int sum=0;
	l=0;
	cout<<ns<<"\n";
	for(int i=0;i<ns.size();i++,l++)
	{
		if(ns[i]=='1')
			sum+=(int)pow(2,l);	
	}		
	//cout<<"Error At"<<sum<<"position\n";
	if(sum!=0)
	{
/*		if(data[sum-1]==0)
			data[sum-1]=1;
		else if(data[sum-1]==1)
			data[sum-1]=0;
*/
		return false;
	}
	return true;
}


string encode(string mes)
{
	int r=build(mes.size());		//Redundant Bits
	int n=r+mes.size();			//Total Transfer  Size
	vector<int>data(n,0);			//initial data
	reverse(mes.begin(),mes.end());			
	vector<string>bitrep(n);
	for(int i=1;i<=n;i++)
		bitrep[i-1]=generate(i);
	//for(string s:bitrep)cout<<s<<"\n";	
	int k=0,i=0,l=0;
	while(mes[k])
	{
		if(i==(int)pow(2,l)-1){l++;data[i]=9;}	
		else{data[i]=mes[k]-'0';k++;}	
		i++;
	}	
	string ns="";
	l=0;
	for(int i=0;i<n;i++)
		{
			if(data[i]==9)
				{
					l++;
					vector<int>loc=location(bitrep,l);
					int sum=0;					
					for(int j=0;j<loc.size();j++)
					    {	
						if(data[loc[j]]==9)
							continue;	
						sum+=data[loc[j]];
					    }
					if(sum&1)data[i]=1;
					else data[i]=0;	
				}
		}
	ns="";	
	for(int i:data)	
		ns+=to_string(i);
	reverse(ns.begin(),ns.end());
	return ns;
}


int main()
{	string mes;
	cout<<"Enter Message\n";
	cin>>mes;
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
	p=fork();
	if(p<0)
		{
			cout<<"Fork Failed:\n";
			return 1;		
		}
	else if(p>0)
		{
			close(sender[0]);
			mes=encode(mes);
			cout<<mes<<"\n";
			char input_to_char[mes.size()+1];
			strcpy(input_to_char,mes.c_str());
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
			string ans;
			char sender_read[100];	
			read(sender[0],sender_read,100);
			int k=strlen(sender_read);
			vector<string>bitrep(k);
			for(int i=1;i<=k;i++)
				bitrep[i-1]=generate(i);
			vector<int>data(k);
			for(int i=0;i<k;i++)
				data[i]=(int)(sender_read[i]-'0');
			reverse(data.begin(),data.end());
			//cout<<"\n";
			//for(int i:data)
				//cout<<i<<" ";
			//cout<<"\n";
			if(valid(bitrep,data))
				ans="correct received";
			else 
				ans="Retransfer";
			close(sender[0]);
			close(receiver[0]);
			char input_to_char[ans.size()+1];
			strcpy(input_to_char,ans.c_str());
			write(receiver[1],input_to_char,strlen(input_to_char)+1);
			close(receiver[1]);
			exit(0);			
		}
	return 0;		
}
