// testhttp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "util.h"

string buffer;
size_t write_data(char *data, size_t size, size_t nmemb, string *writerData){
	if (writerData == NULL)
		return 0;
	int len = size*nmemb;
	writerData->append(data, len);
	//cout <<writerData;
	return len;
}
void parser(string html){
	util u;
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);
	// cout << dom << endl;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	it = dom.begin();
	end = dom.end();
	for (; it != end; ++it)
	{
		if ((!it->isTag())&&(!it->isComment()))
		{
			//cout <<"tagname:"<<it->tagName()<<endl;
			std::string _tempxd = it->text();
			std::wstring _temps = u.Utf8ToUnicode(_tempxd.c_str());
			std::string _tempx = u.UnicodeToAnsi(_temps.c_str());
			cout <<"tagvalue:"<<_tempx.c_str()<<endl;
			//string node=html.substr(it->offset(),it->length());
			//cout <<"tagvalue:"<<node;
		}
	}
}

int main(int argc, char *argv[]){
	CURL *curl;
	curl_global_init(CURL_GLOBAL_ALL); 
	curl=curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, argv[1]); 
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	////CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	//cout <<buffer;
	parser(buffer);
	exit(0);

}



