#include<bits/stdc++.h>
using namespace std;

void fifo(vector<int>disk,int ini)
	{
		int total=abs(ini-disk[0]);
		for(int i=1;i<disk.size();i++)
			total+=abs(disk[i]-disk[i-1]);		
		cout<<"Total Disk heads:"<<total<<"\n";	
	}

void scan(vector<int>disk,int ini,int tt)
	{
		vector<int>great;
		vector<int>small;
		for(int i=0;i<disk.size();i++)
			{
				if(disk[i]<ini)	
					small.push_back(disk[i]);
				else
					great.push_back(disk[i]);
			}
		int total=0;
		sort(small.begin(),small.end());
		sort(great.begin(),great.end());
		int ch;		
		cout<<"1.Left to Right\t2.Right to Left\n";
		cin>>ch;
		if(ch==1)
		{
			reverse(small.begin(),small.end());		
			small.push_back(0);
			total+=abs(ini-small[0]);
			for(int i=1;i<small.size();i++)
				total+=abs(small[i]-small[i-1]);
			total+=abs(0-great[0]);
			for(int i=1;i<great.size();i++)
				total+=abs(great[i]-great[i-1]);			
		}
		else
		{	reverse(small.begin(),small.end());
			great.push_back(tt);	
			total+=abs(ini-great[0]);
			for(int i=1;i<great.size();i++)
				total+=abs(great[i]-great[i-1]);
			total+=abs(tt-small[0]);
			for(int i=1;i<small.size();i++)
				total+=abs(small[i]-small[i-1]);	

		}
	cout<<"Total disk heads:"<<total<<"\n";
	}

void cscan(vector<int>disk,int ini,int tt)
	{
			

	}

int main()
{
	int ini,dh,ch,tt;
	cout<<"Enter Total Disk size:\n";
	cin>>tt;	
	cout<<"Enter initial head:\n";
	cin>>ini;
	cout<<"Enter No. of disk location:\n";
	cin>>dh;	
	vector<int>disk(dh);
	cout<<"Enter Disk Locations:\n";
	for(int i=0;i<dh;i++)
		cin>>disk[i];
	while(1)
	{
		cout<<"1.FIFO\t2.SCAN\t.CSCAN\t4.EXIT\n";
		cin>>ch;
		switch(ch)
		{	
			case 1: fifo(disk,ini);
				break;	
			case 2:	scan(disk,ini,tt);
				break;
			case 3:	cscan(disk,ini,tt);
				break;
			default:exit(0);
		}
	}	
	return 0;
}
