// testglog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*#include "glog/logging.h"*/
#include "util.h"

using namespace std;
/*using namespace google;*/
int main(int argc, char** argv)
{
	util u ;
	std::string src = "{\"a\":12,\"c\":[\"a\":1,\"b\:0]}";
	bool a = u.CheckFormatJson(src);
	std::cout<<a<<std::endl;
// 	google::InitGoogleLogging("");  
// 	FLAGS_servitysinglelog = true;// 用来按照等级区分log文件
// 	google::SetLogDestination(google::GLOG_FATAL, "d:\\temp\\log_fatal_"); // 设置 google::FATAL 级别的日志存储路径和文件名前缀
// 	google::SetLogDestination(google::GLOG_ERROR, "d:\\temp\\log_error_"); //设置 google::ERROR 级别的日志存储路径和文件名前缀
// 	google::SetLogDestination(google::GLOG_WARNING, "d:\\temp\\log_warning_"); //设置 google::WARNING 级别的日志存储路径和文件名前缀
// 	google::SetLogDestination(google::GLOG_INFO, "d:\\temp\\log_info_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
// 	FLAGS_logbufsecs = 0; //缓冲日志输出，默认为30秒，此处改为立即输出
// 	FLAGS_max_log_size = 100; //最大日志大小为 100MB
// 	FLAGS_stop_logging_if_full_disk = true; //当磁盘被写满时，停止日志输出
// 	// 设置日志路径  INFO WARNING ERROR FATAL    
// 	// ...    
// 	char str[202] = "中国jkkasjfkjkasjlfkjsakljflksjadf!";    
// 	LOG(INFO) << "Found " << google::COUNTER <<endl;    
// 	LOG(INFO) << str ;//<< " cookies";    
// 	LOG(WARNING) << "warning test";  // 会输出一个Warning日志    
// 	LOG(ERROR) << "error test";//会输出一个Error日志    

	return 0;  
}

