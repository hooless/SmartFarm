#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>

typedef struct {
	long type;
	int cmd;
}MSG;

void * msgfun()
{
	int msgid;
	key_t key;
	int ret;
	MSG msg;
	int errno;

	key = ftok("/var/www/",'b');
	if(-1 == key)
	{
		perror("ftok");
		printf("ftok created failed!!!\n");
	}

	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0660);
	if (-1 == msgid)
	{
		if (errno == EEXIST)
		{
			msgid = msgget(key,0660);
			printf("msgid  exist\n");
		}else{
			perror("msgget failed!!!\n");
		}
	}

	while(1)
	{
		ret = msgrcv(msgid ,&msg, sizeof(msg)-sizeof(long),0,0);
		if (ret <0)
		{
			printf("msgrcv failed\n");
		}else{
			printf("Recived message is %d\n",msg.cmd);
		}
	}
	pthread_exit(NULL);
		
}

void * shmfun()
{
	char buff[20] = "good good study";
	char buff1[20] = "day day up";

	int shmid;
	key_t key;
	int ret;
	int errno;
	void *shmaddr;
	

	key = ftok("/var/www/",'b');
	if(-1 == key)
	{
		perror("ftok");
		printf("ftok created failed!!!\n");
		exit(1);
	}

	shmid = shmget(key,4096,IPC_CREAT|IPC_EXCL|0660);
	if (-1 == shmid)
	{
		if (errno == EEXIST)
		{
			shmid = shmget(key,4096,0660);
			printf("shmid  exist\n");
		}else{
			perror("shmget failed!!!\n");
		}
	}

	shmaddr = shmat(shmid,NULL,0);
	if((void *)-1 == shmaddr)
	{
		printf("shmat failed\n");
		printf("errno == %d\n",errno);
	}

	while(1)
	{
		strcpy(shmaddr ,buff);
		printf("write buffer %s over\n",buff);
		sleep(1);
		strcpy(shmaddr ,buff1);
		printf("write buffer1 %s over\n",buff1);
		sleep(1);
	}
	pthread_exit(NULL);
		
}

int main()
{
	pthread_t  pth1,pth2;
	int  ret;
	ret = pthread_create(&pth1,NULL,msgfun,NULL);
	if(0 != ret)
	{
		perror("pth1 create failed");
	}
	ret = pthread_create(&pth2,NULL,shmfun,NULL);
	if(0 != ret)
	{
		perror("pth2 create failed");
	}
	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);
}
