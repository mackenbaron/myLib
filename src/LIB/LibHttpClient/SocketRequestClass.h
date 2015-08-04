#pragma once


typedef enum HttpRequesDateType
{
	HRDT_UNKNOW = -1,
	HRDT_INSERT = 1,
	HRDT_UPDATE = 2,
	HRDT_FIND= 3,
	HRDT_DELETE = 4
}HttpRequesDateType_e;

typedef enum HttpRequesType
{
	HR_UNKNOW =-1,
	HR_GET=1,
	HR_POST=2,
}HttpRequesType_e;

typedef struct HttpRequestHead
{
	std::string RequestHead;
	int ReturnNumber;
	std::string ReturnResult;
}HttpResponseHead;

typedef struct HttpRequestResult
{
	std::string Result;
}HttpResponseResult;

typedef struct HtppRequest
{
	HttpRequesDateType_e RequestDateType;
	HttpRequesType_e RequesType;
	std::string RequestResult;
	HttpResponseHead _head;
	HttpResponseResult _body;
}HtppRequest_t;

class SocketRequest
{
public:
	SocketRequest();
	~SocketRequest();
	int setRequestGetRequest( char* Request,char* Body,char* RErrorMesg);
	int setRequestPostRequest( char* RequestBody,char* RequestPar,char* Body,char* RErrorMesg);
private:
	int parse_url(char *url, char **serverstrp, int *portp, char **pathstrp);
	int GetRequest(char* Request,HtppRequest_t& re);
	int PostRequest(char* RequestBody,char* RequestPar,HtppRequest_t &re);
	int AnalysisResult(HtppRequest_t &re);
private:
	bool		mInitSocket;
	std::string mRequestIP;
	int			mRequestPort;
	int			mRequestClientSocket;
	HtppRequest_t  mRequestMessage;
};