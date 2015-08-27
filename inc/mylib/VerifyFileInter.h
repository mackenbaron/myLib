#pragma once

#ifdef LIB_FILE_VERIFY
#define DLL_EXPORT __declspec(dllexport) 
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

typedef struct ResultData // 计算结果
{
	bool bDone; // Done
	std::string strPath; // 路径
	__int64 ulSize; // 大小
	std::string strMDate; // 修改日期
	std::string strVersion; // 版本
	std::string strMD5; // MD5
	std::string strSHA1; // SHA1
	std::string strSHA256; // SHA256
	std::string strCRC32; // CRC32
	std::string strError; // Error string
	ResultData()
		:bDone(false)
		, strPath("")
		, ulSize(0)
		, strMDate("")
		, strVersion("")
		, strMD5("")
		, strSHA1("")
		, strSHA256("")
		, strCRC32("")
		, strError("")
	{}
}Result;

extern "C" DLL_EXPORT int getFileVerify(std::vector<std::string> &infile,std::vector<Result> &outre);