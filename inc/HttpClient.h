#pragma once
class HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);
public:

	int clientGet(IN std::string url,
		OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
		IN std::string UserAgent="",IN std::string Prox="",IN std::string Cookies="");

	int clinetPost(IN std::string url,IN std::string contentData,
		OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
		IN std::string UserAgent="",IN std::string Prox="",IN std::string Cookies="");



};

