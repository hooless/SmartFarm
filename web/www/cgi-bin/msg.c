#include "cgic.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


typedef struct {
	long type;
	int cmd;
}MSG;
int cgiMain()
{
	MSG msg;
	int msgid;
	key_t key;
	int ret;
	int errno;

	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
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
	msgid = msgget(key, IPC_CREAT|IPC_EXCL|0660);
	if (-1 == msgid)
	{
		if (errno == EEXIST)
		{
			msgid = msgget(key,0660);
		}
	}
	if (cgiFormSuccess == cgiFormSubmitClicked("on"))
	{
		fprintf(cgiOut,"led on \n");
		msg.cmd=1;
		ret = msgsnd(msgid,&msg,sizeof(msg)-sizeof(long),0);
		if(-1 == ret)
		{
			fprintf(cgiOut,"msgsnd failed\n");
		}

	}
	if (cgiFormSuccess == cgiFormSubmitClicked("off"))
	{
		fprintf(cgiOut,"led off \n");
		msg.cmd=0;
		ret = msgsnd(msgid,&msg,sizeof(msg)-sizeof(long),0);
		if(-1 == ret)
		{
			fprintf(cgiOut,"msgsnd failed\n");
		}

	}


	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");
	return 0;
}
