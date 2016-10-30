#include "cgic.h"
#include "cgic.c"
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int cgiMain()
{
	int shmid;
	key_t key;
	int ret;
	int errno;
	void *shmaddr;

	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\" />\n");
	fprintf(cgiOut,"<title> BOA </title>\n");
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"<body>\n");
	fprintf(cgiOut,"test\n");


	key = ftok("/var/www/",'b');
	if (-1 == key)
	{
		fprintf(cgiOut,"ftok failed\n");
		fprintf(cgiOut,"error == %d\n", errno);
	}
	shmid = shmget(key, 4096, IPC_CREAT|IPC_EXCL|0660);
	if (-1 == shmid)
	{
		if (errno == EEXIST)
		{
			shmid = shmget(key,4096,0660);
		}else{
			fprintf(cgiOut,"shmget failed\n");
		}
	}
	shmaddr = shmat(shmid,NULL,0);
	if((void *)-1 == shmaddr)
	{
		fprintf(cgiOut,"shmat failed\n");
		fprintf(cgiOut,"errno == %d\n",errno);
	}
	fprintf(cgiOut,"buff == %s\n",(char *)shmaddr);


	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");
	return 0;
}
