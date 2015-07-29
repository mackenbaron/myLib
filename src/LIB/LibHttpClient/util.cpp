#include "stdafx.h"
#include "util.h"
#ifdef WIN32
void util::readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def)
{
	WCHAR char_temp[512] = {L'\0'};
	GetPrivateProfileString(util::AnsiToUnicode(root.c_str()),util::AnsiToUnicode(userkey.c_str()),util::AnsiToUnicode(def.c_str()),char_temp,MAX_PATH,util::AnsiToUnicode(path.c_str()));
	uservalue = util::UnicodeToAnsi(char_temp);
}

void util::readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def)
{
	userValue = GetPrivateProfileInt(util::AnsiToUnicode(root.c_str()),util::AnsiToUnicode(userkey.c_str()),def,util::AnsiToUnicode(path.c_str()));
}

void util::writeINIFileString(std::string path,std::string root,std::string userkey,std::string value)
{
	WritePrivateProfileString(util::AnsiToUnicode(root.c_str()),util::AnsiToUnicode(userkey.c_str()),util::AnsiToUnicode(value.c_str()),util::AnsiToUnicode(path.c_str()));
}
#endif
void util::UTF_8ToUnicode(wchar_t* pOut,char *pText){
	char* uchar = (char *)pOut;
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	return;
}

void util::UnicodeToUTF_8(char* pOut,wchar_t* pText){
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后z
	char* pchar = (char *)pText;
	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
	return;
}

void util::UnicodeToGB2312(char* pOut,wchar_t uData){
	WideCharToMultiByte(CP_ACP,NULL,&uData,1,pOut,sizeof(wchar_t),NULL,NULL);
	return;
}    

void util::Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer){
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	return ;
}

void util::GB2312ToUTF_8(std::string& pOut,char *pText, int pLen){
	char buf[4];
	int nLength = pLen* 3;
	char* rst = new char[nLength];

	memset(buf,0,4);
	memset(rst,0,nLength);

	int i = 0;
	int j = 0;     
	while(i < pLen){
		//如果是英文直接复制就能
		if( *(pText + i) >= 0){
			rst[j++] = pText[i++];
		}else{
			wchar_t pbuffer;
			Gb2312ToUnicode(&pbuffer,pText+i);
			UnicodeToUTF_8(buf,&pbuffer);
			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];   
			j += 3;

			i += 2;

		}

	}

	rst[j] ='\0';
	//返回结果
	pOut = rst;            
	delete []rst;    
	return;
}

void util::UTF_8ToGB2312(std::string &pOut, char *pText, int pLen){
	char * newBuf = new char[pLen];
	char Ctemp[4];
	memset(Ctemp,0,4);
	int i =0;
	int j = 0;

	while(i < pLen){

		if(pText > 0){
			newBuf[j++] = pText[i++];                      
		}else{
			WCHAR Wtemp;
			UTF_8ToUnicode(&Wtemp,pText + i);
			UnicodeToGB2312(Ctemp,Wtemp);
			newBuf[j] = Ctemp[0];
			newBuf[j + 1] = Ctemp[1];

			i += 3;   
			j += 2;  
		}
	}

	newBuf[j] ='\0';
	pOut = newBuf;
	delete []newBuf;
	return;
}

WCHAR* util::AnsiToUnicode( const char* szStr )
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	if (nLen == 0)
	{
		return NULL;
	}
	WCHAR* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
	return pResult;
}

char* util::UnicodeToAnsi( const WCHAR* szStr )
{
	int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte( CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL );
	return pResult;
}

char* util::UnicodeToUTF8( const WCHAR* szStr )
{
	int nLen = WideCharToMultiByte( CP_UTF8, 0, szStr, -1, NULL, 0, NULL, NULL );
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte( CP_UTF8, 0, szStr, -1, pResult, nLen, NULL, NULL );
	return pResult;
}

wchar_t* util::Utf8ToUnicode( const char* utf )
{
	if(!utf || !strlen(utf))  
	{  
		return NULL;  
	}  
	int dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,utf,-1,NULL,0);  
	size_t num = dwUnicodeLen*sizeof(wchar_t);  
	wchar_t *pwText = (wchar_t*)malloc(num);  
	memset(pwText,0,num);  
	MultiByteToWideChar(CP_UTF8,0,utf,-1,pwText,dwUnicodeLen);   
	return pwText;  
}

char* util::intTOStirng(const int n)
{
	char _temp[128]={'\0'};
	if(n>=0)
	{
		sprintf(_temp,"%d",n);
		
	}else
	{
		sprintf(_temp,"%d",0);
	}
	return _temp;
	
}

char* util::DoubleTOString(const double n)
{
	char _temp[128]={'\0'};
	if(n>=0)
	{
		sprintf(_temp,"%f",n);

	}else
	{
		sprintf(_temp,"%f",0.0);
	}
	return _temp;
}

int util::StringToInt(const char* src)
{
	return atoi(src);
}
double util::StringTODouble(const char* src)
{
	return atof(src);
}
