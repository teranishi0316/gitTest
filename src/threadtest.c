/*
 ============================================================================
 Name        : threadtest.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "threadtest.h"

void *threadA(void *argc) {
	int i;
	printf("Thread A Start!\r\n");
	for(i = 0; i < 1000; i++ ) {
		printf("threadA : %d\r\n", i+1);
		usleep(0);
	}
	printf("Thread A End!\r\n");

	return NULL;
}

void *threadB(void *argc) {
	int i;
	printf("Thread B Start!\r\n");
	for(i = 0; i < 1000; i++ ) {
		printf("threadB : %d\r\n", i+1);
		usleep(0);
	}
	printf("Thread B End!\r\n");

	return NULL;
}

int main(void) {
	pthread_t thread_id[2];
	void *result[2];
	int status;
	struct sched_param p;
	int policy;
	int i;

	status = pthread_create(&thread_id[0], NULL, &threadA, (void*)NULL);

	if(status != 0) {
		printf("ERROR threadA\r\n");
		return EXIT_FAILURE;
	}
	usleep(0);
	status = pthread_create(&thread_id[1], NULL, threadB, (void*)NULL);

	if(status != 0) {
		printf("ERROR threadB\r\n");
		return EXIT_FAILURE;
	}

	pthread_getschedparam(thread_id[0],&policy,&p);
	printf("スレッドA Priority:%d\r\n",p.sched_priority);
	pthread_getschedparam(thread_id[1],&policy,&p);
	printf("スレッドB Priority:%d\r\n",p.sched_priority);

	printf("メインスレッドの処理Start!\r\n");
	for(i = 0; i < 1000; i++) {
		printf("メインスレッドの処理%d\r\n",i+1);
		usleep(0);
	}
	printf("メインスレッドの処理End!\r\n");

	pthread_join(thread_id[0], &result[0]);
	pthread_join(thread_id[1], &result[1]);

	printf("Thread Programing End!\r\n");

	return EXIT_SUCCESS;
}


