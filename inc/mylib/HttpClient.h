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

	int clientPost(IN std::string url,IN std::string contentData,
		OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
		IN std::string UserAgent="",IN std::string Prox="",IN std::string Cookies="");

	int clientNewGet(IN std::string url,
		OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
		IN int resolveTimeout=0,IN int connectTimeout = 60000,IN int sendTimeout = 30000,IN int receiveTimeout = 30000,
		IN std::string UserAgent="",IN std::string Prox="",IN std::string Cookies="");

	int clientNewPost(IN std::string url,IN std::string contentData,
		OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
		IN int resolveTimeout=0,IN int connectTimeout = 60000,IN int sendTimeout = 30000,IN int receiveTimeout = 30000,
		IN std::string UserAgent="",IN std::string Prox="",IN std::string Cookies="");


	int ClientDownload(IN std::string sourSrc,IN std::string destSrc,IN std::string Cookies);
};

