#include "StdAfx.h"
#include "curlHttpRequestBase.h"


curlHttpRequestBase::curlHttpRequestBase(void)
	: m_curl(NULL)
{
}


curlHttpRequestBase::~curlHttpRequestBase(void)
{
	curl_easy_cleanup( m_curl );
	curl_global_cleanup();
}
int curlHttpRequestBase::init()
{
	CURLcode res = ::curl_global_init( CURL_GLOBAL_ALL );
	if( CURLE_OK != res )
	{
		fprintf( stderr, "curl_global_init failed: %d \n", res );
		return -1;
	}

	m_curl = ::curl_easy_init();
	if( NULL == m_curl )
	{
		fprintf( stderr, "curl_easy_init failed\n" );
		return -1;
	}
	return 0;
}


int curlHttpRequestBase::doHttpPost( const char* url, const char* data, long timeout, long withheader )
{
	resetOpt();
	::curl_easy_setopt( m_curl, CURLOPT_HEADER, withheader );
	::curl_easy_setopt( m_curl, CURLOPT_URL, url );
	::curl_easy_setopt( m_curl, CURLOPT_POST, 1 );
	::curl_easy_setopt( m_curl, CURLOPT_POSTFIELDS, data );
	::curl_easy_setopt( m_curl, CURLOPT_TIMEOUT, timeout );
	::curl_easy_setopt( m_curl, CURLOPT_WRITEFUNCTION, curlHttpRequestBase::processFunc );
	::curl_easy_setopt( m_curl, CURLOPT_WRITEDATA, this );
	CURLcode res = ::curl_easy_perform( m_curl);
	return ( 0 == res ) ? 0 : -1;
}

int curlHttpRequestBase::doHttpGet( const char* url, const char* data, long timeout, long withheader )
{
	resetOpt();
	size_t urllen = strlen( url );
	size_t datalen = strlen( data );
	char* surl = new char[ urllen + datalen + 1 + 1];
	if( !surl )
	{
		fprintf( stderr, "doHttpGet failed, unable to malloc memery\n" );
		return -1;
	}
	strncpy( surl, url, urllen );
	surl[ urllen ] = '?';
	strcpy( surl + urllen + 1, data );
	::curl_easy_setopt( m_curl, CURLOPT_URL, surl );
	::curl_easy_setopt( m_curl, CURLOPT_HTTPGET, 1 );
	::curl_easy_setopt( m_curl, CURLOPT_HEADER, withheader );
	::curl_easy_setopt( m_curl, CURLOPT_TIMEOUT, timeout );
	::curl_easy_setopt( m_curl, CURLOPT_WRITEFUNCTION, curlHttpRequestBase::processFunc );
	::curl_easy_setopt( m_curl, CURLOPT_WRITEDATA, this );

	CURLcode res = ::curl_easy_perform( m_curl);

	delete [] surl;
	return ( 0 == res ) ? 0 : -1;
}

void curlHttpRequestBase::resetOpt()
{
	::curl_easy_reset( m_curl );
	//::curl_easy_setopt( m_curl, CURLOPT_VERBOSE, 1 );//set this to show debug message

}

size_t curlHttpRequestBase::processFunc( void* ptr, size_t size, size_t nmemb, void *usrptr )
{
	curlHttpRequestBase* p =(curlHttpRequestBase*) usrptr;
	return p->process( ptr, size, nmemb );
}



int curlHttpRequestBase::process( void* data, size_t size, size_t nmemb )
{
	return size * nmemb;
}
