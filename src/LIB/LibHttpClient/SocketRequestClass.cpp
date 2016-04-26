#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "SocketRequestClass.h"

#define  BUFSIZ 1024

SocketRequest::SocketRequest()
	:mInitSocket(false)
{

}

SocketRequest::~SocketRequest()
{
}

int SocketRequest::setRequestGetRequest( char* Request,std::string& Body,std::string& RErrorMesg )
{
	HtppRequest_t  mRequestMessage;
	int ReslutInt = -100;
	ReslutInt = GetRequest(Request,mRequestMessage);
	if(ReslutInt != 0)
		return ReslutInt;
 	ReslutInt = AnalysisResult(mRequestMessage);
 	if(ReslutInt != 0)
 		return ReslutInt;
 	ReslutInt = mRequestMessage._head.ReturnNumber;
	Body = mRequestMessage._body.Result;
	RErrorMesg = mRequestMessage._head.ReturnResult;
	return ReslutInt==200?0:ReslutInt;
}

int SocketRequest::setRequestPostRequest( char* RequestBody,char* RequestPar,std::string& Body,std::string& RErrorMesg )
{
	HtppRequest_t  mRequestMessage;
	int ReslutInt = -100;
	ReslutInt = PostRequest(RequestBody,RequestPar,mRequestMessage);
	if(ReslutInt != 0)
		return ReslutInt;
 	ReslutInt = AnalysisResult(mRequestMessage);
 	if(ReslutInt != 0)
 		return ReslutInt;
 	ReslutInt = mRequestMessage._head.ReturnNumber;
 	Body = mRequestMessage._body.Result;
 	RErrorMesg = mRequestMessage._head.ReturnResult;
	return ReslutInt==200?0:ReslutInt;
}

int SocketRequest::AnalysisResult( HtppRequest_t &re )
{
	if(re.RequestResult.empty())
	{
		return 4;
	}
	int HtmlSrca  = re.RequestResult.find("\r\n\r\n");
	if(HtmlSrca > 0)
	{
		std::string _tempHttpHead = re.RequestResult.substr(0,HtmlSrca);
		std::string _tempJsonsrc = re.RequestResult.substr(HtmlSrca,re.RequestResult.size());

		re._head.RequestHead = _tempHttpHead;
		re._body.Result = _tempJsonsrc;

		std::string  _tempHttp1 = _tempHttpHead.substr(0,_tempHttpHead.find("\r\n"));

		int _tempa = _tempHttp1.find(" ");
		if(_tempa <= 0)
		{
			return 4;
		}
		re._head.ReturnNumber = atoi( _tempHttp1.substr(_tempa,4).c_str());
		re._head.ReturnResult= _tempHttp1.substr(_tempa+4,_tempHttp1.size());
	}
	return 0;
}

int SocketRequest::PostRequest( char* RequestBody,char* RequestPar,HtppRequest_t &re )
{
	int retslut = 0;
	memset(&re,0,sizeof(re));
	re.RequesType = HR_POST;
	int RequsetLine = strlen(RequestBody) + strlen(RequestPar)+512;
	WSADATA WsaData;
	SOCKET socketfd;
	SOCKADDR_IN addr;
	HOSTENT *pURL;
	char *host = new char[RequsetLine];
	char *Req = new char[RequsetLine];
	char *Header= new char[RequsetLine];
	int port;

	static char text[BUFSIZ];

	if (WSAStartup(MAKEWORD(2,2),&WsaData))
	{
		printf("The socket failed");
		delete[] host;
		host = NULL;
		delete[] Req;
		Req = NULL;
		delete[]Header;
		Header = NULL;
		return -1;
	}
	parse_url(RequestBody,&host,&port,&Req);

	strnset(Header,'\0',RequsetLine);


	socketfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	pURL = gethostbyname(host);
	if(pURL == NULL)
	{
		delete[] host;
		host = NULL;
		delete[] Req;
		Req = NULL;
		delete[]Header;
		Header = NULL;
		return -2;
	}

	addr.sin_addr.s_addr = *((unsigned long *)pURL->h_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	

	strcat(Header,"POST ");
	strcat(Header,Req);
	strcat(Header," HTTP/1.0\r\n");
	strcat(Header,"Accept: */*\r\n");
	strcat(Header,"Accept-Language: zh-cn/r/n");
	strcat(Header,"User-Agent: Mozilla/4.0\r\n");
	char content_header[100];
	sprintf(content_header,"Content-Length: %d\r\n", strlen(RequestPar));
	strcat(Header, content_header);
	strcat(Header,"Accept-Language: en-us\r\n");
	strcat(Header,"Accept-Encoding: gzip, deflate\r\n");
	strcat(Header,"Host: ");
	strcat(Header,host);
	strcat(Header,"\r\nContent-Type: application/x-www-form-urlencoded\r\n");
	strcat(Header,"Connection: Keep-Alive\r\n");
	
	strcat(Header,"\r\n");
	
	strcat(Header, RequestPar);
	//strcat(Header,"\r\n");
	
	connect(socketfd,(SOCKADDR *)&addr,sizeof(addr));
	send(socketfd,Header,strlen(Header),0);
	//printf("%s",Header);
	while(recv(socketfd,text,BUFSIZ,0)>0){
		re.RequestResult.append(text);
		strnset(text,'\0',BUFSIZ);
	}
	closesocket(socketfd);
	WSACleanup();
	delete[] host;
	host = NULL;
	delete[] Req;
	Req = NULL;
	delete[]Header;
	Header = NULL;
	return retslut;
}

int SocketRequest::GetRequest( char* Request,HtppRequest_t& re )
{
	int retslut = 0;
	memset(&re,0,sizeof(re));
	re.RequesType = HR_GET;
	int RequsetLine = strlen(Request)+512;
	WSADATA WsaData;
	SOCKET socketfd;
	SOCKADDR_IN addr;
	HOSTENT *pURL;
	char *host = new char[256],*GET = new char[RequsetLine];
	char *Header = new char[RequsetLine];
	int port;

	static char text[BUFSIZ];

	if (WSAStartup(MAKEWORD(2,2),&WsaData))
	{
		printf("The socket failed");
		delete[] host;
		host = NULL;
		delete[] GET;
		GET = NULL;
		delete []Header;
		Header = NULL;
		return -1;
	}
	parse_url(Request,&host,&port,&GET);

	strnset(Header,'\0',RequsetLine);


	socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	pURL = gethostbyname(host);
	if(pURL == NULL)
	{
		delete[] host;
		host = NULL;
		delete[] GET;
		GET = NULL;
		delete []Header;
		Header = NULL;
		return -2;
	}

	addr.sin_addr.s_addr = *((unsigned long *)pURL->h_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	

	strcat(Header,"GET ");
	strcat(Header,GET);
	strcat(Header," HTTP/1.0\r\n");
	strcat(Header,"Accept: */*\r\n");
	strcat(Header,"Accept-Language: zh-cn/r/n");
	strcat(Header,"User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; InfoPath.2)\r\n");
	strcat(Header,"Accept-Encoding: gzip, deflate\r\n");
	strcat(Header,"Host: ");
	strcat(Header,host);
	strcat(Header,"\r\nConnection: Keep-Alive\r\n");
	
	strcat(Header,"\r\n\r\n");
	
	connect(socketfd,(SOCKADDR *)&addr,sizeof(addr));
	send(socketfd,Header,strlen(Header),0);
	//printf("%s",Header);
	while(recv(socketfd,text,BUFSIZ,0)>0){
		re.RequestResult.append(text);
		strnset(text,'\0',BUFSIZ);
	}
	delete[] host;
	host = NULL;
	delete[] GET;
	GET = NULL;
	delete []Header;
	Header = NULL;
	closesocket(socketfd);
	WSACleanup();
	return retslut;
}
int SocketRequest::parse_url(char *url, char **serverstrp, int *portp, char **pathstrp)
{
char buf[256];
	int serverlen, numread=0;

	url = url+7;

	sscanf(url, "%255[^/:]", buf);
	serverlen = strlen(buf);
	*serverstrp = (char *)malloc(serverlen+1);
	strcpy(*serverstrp, buf);
	if(url[serverlen]==':')
	{

		sscanf(&url[serverlen+1], "%d%n", portp, &numread);
		
		numread++;
	}
	else
	{
		*portp = 80;
	}
	
	//*pathstrp = &url[serverlen+numread];
	strcpy(*pathstrp,&url[serverlen+numread]);
	return 0;
}
