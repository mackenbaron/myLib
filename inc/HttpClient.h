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


	int ClientDownload(IN std::string sourSrc,IN std::string destSrc,IN std::string Cookies);
};

