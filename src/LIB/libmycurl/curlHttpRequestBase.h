#pragma once

class curlHttpRequestBase
{
public:
	curlHttpRequestBase(void);
	virtual ~curlHttpRequestBase(void);
	int init();   
protected:
    virtual int process( void* data, size_t size, size_t nmemb );
public:
    int doHttpPost( const char* url, const char* data, long timeout = 10, long withheader = 0 );
	int doHttpGet( const char* url, const char* data, long timeout = 10, long withheader = 0 );
public:
    void resetOpt();
private:
    static size_t processFunc( void* ptr, size_t size, size_t nmemb, void *usrptr );
private:
    CURL * m_curl;
};

