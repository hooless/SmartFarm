#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
	long type;
	int cmd;
}MSG;

int main()
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
		exit(1);
	}

	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0660);
	if (-1 == msgid)
	{
		if (errno == EEXIST)
		{
			msgid = msgget(key,0660);
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
		
}
