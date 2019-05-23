#include<bits/stdc++.h>
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


void valid(vector<string>bitrep,vector<int>&data)
{	string ns="";
	int l=0;
	for(int i=0;i<data.size();i++)
	{
		if(i==(int)pow(2,l)-1)
			{	l++;
				int sum=0;								
				vector<int>loc=location(bitrep,l);
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
	for(int i=0;i<ns.size();i++,l++)
	{
		if(ns[i]=='1')
			sum+=(int)pow(2,l);	
	}		
	cout<<"Error At"<<sum<<"position\n";
	if(sum!=0)
	{
		if(data[sum-1]==0)
			data[sum-1]=1;
		else if(data[sum-1]==1)
			data[sum-1]=0;
	}

}



void encode(string mes)
{
	int r=build(mes.size());		//Redundant Bits
	int n=r+mes.size();			//Total Transfer  Size
	vector<int>data(n,0);			//initial data
	reverse(mes.begin(),mes.end());			
	vector<string>bitrep(n);
	for(int i=1;i<=n;i++)
		bitrep[i-1]=generate(i);	
	int k=0,i=0,l=0;
	while(mes[k])
	{
		if(i==(int)pow(2,l)-1){l++;data[i]=9;}	
		else{data[i]=mes[k]-'0';k++;}	
		i++;
	}	
	//reverse(data.begin(),data.end());
	cout<<"Raw Data \n";
	string ns="";
	for(int i:data)
		ns+=to_string(i);
	reverse(ns.begin(),ns.end());
	cout<<ns<<"\n";
	l=0;
	for(int i=0;i<n;i++)
		{
			if(data[i]==9)
				{
					l++;
					vector<int>loc=location(bitrep,l);
					//for(int i:loc)
					//	cout<<i<<" ";	
					int sum=0;					
					for(int j=0;j<loc.size();j++)
					    {	
						if(data[loc[j]]==9)
							continue;	
						sum+=data[loc[j]];
					    }
					//cout<<sum<<"\n";
					if(sum&1)data[i]=1;
					else data[i]=0;	
				}
		}
	ns="";	
	for(int i:data)	
		ns+=to_string(i);
	reverse(ns.begin(),ns.end());
	cout<<"Encoded Data:"<<ns<<"\n";
	int ch;
	cout<<"Want to Generate Error(1/0):\n";
	cin>>ch;
	if(ch==1)
		{	int k;
			//cout<<mes<<"\n";
			cout<<"Which bit to alter(Not Redundant Bits):\n";
			cin>>k;
			if(data[k-1]==1)
				data[k-1]=0;
			else if(data[k-1]==0)
				data[k-1]=1;
			//if(ch==1)
			cout<<"Error Detected In Transfer:"<<"\n";
			ns="";	
			for(int i:data)	
				ns+=to_string(i);
			reverse(ns.begin(),ns.end());
			cout<<ns<<"\n";
			valid(bitrep,data);
		}

	ns="";	
	for(int i:data)	
		ns+=to_string(i);
	reverse(ns.begin(),ns.end());
	cout<<"Corrected Data:"<<ns<<"\n";
	int c=0;
	string kk="";
	for(int i=0;i<data.size();i++)
		if(i==(int)pow(2,c)-1)
			{c++;
			continue;}	
		else
			kk+=to_string(data[i]);
	reverse(kk.begin(),kk.end());
	cout<<"Received Message"<<kk<<"\n";
}

int main()
{
	string mes;
	cout<<"Enter Message\n";
	cin>>mes;
	encode(mes);	
	return 0;
}
