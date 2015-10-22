#include "StdAfx.h"
#include "curlHttpRequest.h"


curlHttpRequest::curlHttpRequest(void)
	:m_pcurl(NULL)  
{  
	m_pcurl = curl_easy_init();  
}  


curlHttpRequest::~curlHttpRequest(void)
{
	curl_easy_cleanup(m_pcurl); 
}

size_t curlHttpRequest::WriteData(char *data, size_t block_size, size_t block_count, std::string *response)
{
	if(data == NULL) return 0;  

	size_t len = block_size * block_count;  
	response->append(data, len);  
	return len;  
}

size_t curlHttpRequest::WriteFile(char *data, size_t block_size, size_t block_count, FILE *file)
{
	if(data == NULL) return 0;  

	size_t len = block_size * block_count;  
	fwrite(data, len, 1, file);   
	return len;  
}

bool curlHttpRequest::Request(const std::string &url, const std::string &request, std::string method, std::string &response, int timeout)
{
	m_response_code = 0;  

	response.clear();  
	response.reserve(64 * 1024);  

	curl_easy_reset(m_pcurl);  
	curl_easy_setopt(m_pcurl, CURLOPT_URL, url.c_str());  
	curl_easy_setopt(m_pcurl, CURLOPT_NOSIGNAL, 1);  
	curl_easy_setopt(m_pcurl, CURLOPT_TIMEOUT, timeout);  
	curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION,curlHttpRequest::WriteData);  
	curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, &response);  
	if(method == "get")  
	{  
		curl_easy_setopt(m_pcurl, CURLOPT_HTTPGET, 1);  
	}  
	else if(method == "post")  
	{  
		curl_easy_setopt(m_pcurl, CURLOPT_POST, 1L);  
		curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE, request.length());  
		curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS, request.c_str());  
	}  
	else if(method == "put")  
	{  
		curl_easy_setopt(m_pcurl, CURLOPT_CUSTOMREQUEST, "PUT");  
		curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE, request.length());  
		curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS, request.c_str());  
	}  
	else if(method == "delete")  
	{  
		curl_easy_setopt(m_pcurl, CURLOPT_CUSTOMREQUEST, "DELETE");  
	}  
	else  
	{  
		return false;  
	}  

	CURLcode rc = curl_easy_perform(m_pcurl);  
	if(rc != CURLE_OK)  
	{  
		m_error =  std::string(curl_easy_strerror(rc));  
		return false;  
	}  

	rc = curl_easy_getinfo(m_pcurl, CURLINFO_RESPONSE_CODE , &m_response_code);   
	if(rc != CURLE_OK)  
	{  
		m_error =  std::string(curl_easy_strerror(rc));  
		return false;  
	}  

	return true;  
}

bool curlHttpRequest::SaveFile(const std::string& url, const char *filename, int timeout)
{
	m_response_code = 0;  

	FILE* file = fopen(filename, "wb");  

	curl_easy_reset(m_pcurl);  
	curl_easy_setopt(m_pcurl, CURLOPT_URL, url.c_str());  
	curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION,curlHttpRequest::WriteFile);  
	curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, file);  
	curl_easy_setopt(m_pcurl, CURLOPT_FOLLOWLOCATION, 1);  
	curl_easy_setopt(m_pcurl, CURLOPT_NOSIGNAL, 1);  
	curl_easy_setopt(m_pcurl, CURLOPT_TIMEOUT, timeout);  

	CURLcode rc = curl_easy_perform(m_pcurl);  
	fclose(file);  
	if(rc != CURLE_OK)  
	{  
		m_error =  std::string(curl_easy_strerror(rc));  
		return false;  
	}  

	rc = curl_easy_getinfo(m_pcurl, CURLINFO_RESPONSE_CODE , &m_response_code);   
	if(rc != CURLE_OK)  
	{  
		m_error =  std::string(curl_easy_strerror(rc));  
		return false;  
	}  

	return true;  
}

bool curlHttpRequest::Get(const std::string& url, std::string &response, int timeout)
{
	return Request(url, "", "get", response, timeout);
}

bool curlHttpRequest::Put(const std::string &url, const std::string &request, std::string &response, int timeout)
{
	 return Request(url, request, "put", response, timeout);  
}

bool curlHttpRequest::Post(const std::string& url, const std::string &request, std::string &response, int timeout)
{
	 return Request(url, request, "post", response, timeout);  
}

bool curlHttpRequest::Delete(const std::string &url, std::string &response, int timeout)
{
	return Request(url, "", "delete", response, timeout); 
}

bool curlHttpRequest::Save(const std::string& url, const char *filename, int timeout)
{
	return SaveFile(url,filename,timeout);
}
