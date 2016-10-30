#include "cgic.h"
#include "cgic.c"
int cgiMain()
{
	char buff[20] = {0};
	cgiFormString("led",buff,sizeof(buff));

	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<title> BOA </title>\n");
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"buff == %s\n",buff);
	if(0==strcmp("on",buff))
	{
		fprintf(cgiOut,"led == on");
	}
	else
	{
		fprintf(cgiOut,"led == off");
	}
//	if(cgiFormSuccess == cgiFormSubmitClicked("on"))
	//{
	//	fprintf(cgiOut,"led on\n");
	//}
	//if(cgiFormSuccess == cgiFormSubmitClicked("off"))
//	{
//		fprintf(cgiOut,"led off\n");
//	}
//	fprintf(cgiOut,"welcome to my boa\n");
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");
	return 0;
}
