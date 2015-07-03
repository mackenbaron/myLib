#pragma once
class HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);
public:
	int clientGet(IN std::string url,OUT std::string &ResponseHeader,OUT std::string &ResponseContent);
	int clinetPost(IN std::string url,IN std::string contentData,OUT std::string &ResponseHeader,OUT std::string &ResponseContent);

};

