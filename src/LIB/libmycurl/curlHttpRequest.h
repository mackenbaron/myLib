#pragma once
class curlHttpRequest
{
public:
	curlHttpRequest(void);
	~curlHttpRequest(void);
public:
	bool Get(const std::string& url, std::string &response, int timeout);
	bool Put(const std::string &url, const std::string &request, std::string &response, int timeout);
	bool Post(const std::string& url, const std::string &request, std::string &response, int timeout);
	bool Delete(const std::string &url, std::string &response, int timeout);
	bool Save( const std::string& url, const char *filename, int timeout);
private:
	static size_t WriteData(char *data, size_t block_size, size_t block_count, std::string *response);
	static size_t WriteFile(char *data, size_t block_size, size_t block_count, FILE *file);
	bool Request(const std::string &url, const std::string &request, std::string method, std::string &response, int timeout);
	bool SaveFile( const std::string& url, const char *filename, int timeout);
private:  
	CURL  *m_pcurl;  
	std::string m_error;  
	long   m_response_code; 
};

