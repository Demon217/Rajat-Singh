#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<vector>
using namespace std;


sem_t full, empty;
pthread_mutex_t lock;
vector<int> buffer;
int productionCounter = 1;

void *producer(void *param){
	while(true){
		sem_wait(&empty);
		pthread_mutex_lock(&lock);
		buffer.push_back(productionCounter++);
		cout<<"Produced "<<productionCounter-1<<endl;
		pthread_mutex_unlock(&lock);
		sem_post(&full);
		sleep(rand() % 5);	//produce random delay
	}
}

void *consumer(void *param){
	while(true){
		sem_wait(&full);
		pthread_mutex_lock(&lock);
		cout<<"Consumed "<<buffer[buffer.size()-1]<<endl;
		buffer.pop_back();
		pthread_mutex_unlock(&lock);
		sem_post(&empty);
		sleep(rand() % 5);
	}
}

int main(){
	const int BUFFER_SIZE = 5;

	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);

	pthread_mutex_init(&lock, NULL);

	pthread_t consumerId, producerId;

	pthread_attr_t cAttr, pAttr;
	pthread_attr_init(&cAttr);
	pthread_attr_init(&pAttr);

	pthread_create(&producerId, &pAttr, producer, NULL);
	sleep(4);
	pthread_create(&consumerId, &cAttr, consumer, NULL);

	pthread_join(producerId, NULL);
	pthread_join(consumerId, NULL);
}

