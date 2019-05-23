#include<bits/stdc++.h>
#include<unistd.h>
#include<pthread.h>
using namespace std;

pthread_mutex_t lock[5];

void *runner(void *param)
	{
		int id=atoi((char*)param);
		while(true)	
		{
			if(id%2==0)
				{
					pthread_mutex_lock(&lock[(id+1)%5]);
					pthread_mutex_lock(&lock[(id)%5]);
					cout<<"Eating"<<id<<"\n";
					sleep(3);	
					pthread_mutex_unlock(&lock[(id+1)%5]);
					pthread_mutex_unlock(&lock[(id+4)%5]);
					cout<<"Stopped Eating"<<id<<"\n";
				}
			else
				{	
					
				        pthread_mutex_lock(&lock[(id)%5]);
					pthread_mutex_lock(&lock[(id+1)%5]);
					cout<<"Eating"<<id<<"\n";
					sleep(3);
					pthread_mutex_unlock(&lock[(id+4)%5]);
					pthread_mutex_unlock(&lock[(id+1)%5]);
					cout<<"Stopped Eating"<<id<<"\n";
				}
		}
		pthread_exit(0);
	}


int main()
{	char *s[]={"1","2","3","4","5"};
	pthread_t pt[5];	
	pthread_attr_t ptattr[5];
	for(int i=0;i<5;i++)
		pthread_mutex_init(&lock[i],NULL);
	for(int i=0;i<5;i++)
		pthread_attr_init(&ptattr[i]);
	for(int i=0;i<5;i++)
		pthread_create(&pt[i],&ptattr[i],runner,s[i]);
	for(int i=0;i<5;i++)
		pthread_join(pt[i],NULL);
	return 0;
}	
