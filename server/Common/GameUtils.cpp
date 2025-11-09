#include "RoutineManager.h"
#include "stdarg.h"
#include <stdio.h>


void Log(const char* msg, ...)
{
	auto msgPtr = POOL_NEW(Message_log);

	va_list argptr;

	va_start(argptr, msg);
	vsnprintf(msgPtr->szLog, sizeof(msgPtr->szLog), msg, argptr);
	va_end(argptr);
	g_RoutineManager.SendMsg2RoutineType(RoutineType::LOG, msgPtr);
}


uint64_t GetCurrencyTime()
{
#ifdef _WIN32
	return GetTickCount();
#else
	struct timeval _tstart, _tend;
	struct timezone tz;
	gettimeofday(&_tend, &tz);
	double t1, t2;
	t1 = (double)_tstart.tv_sec * 1000 + (double)_tstart.tv_usec / 1000;
	t2 = (double)_tend.tv_sec * 1000 + (double)_tend.tv_usec / 1000;
	return uint64_t(t2 - t1);
#endif
}


#include <chrono>
#include <iomanip>
#include <sstream>
std::string getCurrentTimestamp() {
	// 获取当前系统时间（精确到毫秒）
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		now.time_since_epoch()) % 1000;
	auto timer = std::chrono::system_clock::to_time_t(now);

	// 转换为本地时间
	std::tm bt = *std::localtime(&timer);

	// 格式化为字符串
	std::ostringstream oss;
	oss << std::put_time(&bt, "%Y-%m-%d-%H-%M-%S");
	oss << "-" << std::setfill('0') << std::setw(3) << ms.count();

	return oss.str();
}



#include <fstream>
#include <string>
void __show__(const char* szTemp)
{

}
void __assertex__(const char* filename, int line, const char* func, const char* expr, const char* msg)
{
	char szTemp[1024] = { 0 };

#ifdef __LINUX__
	sprintf(szTemp, "[T=%s][%s][%d][%s][%s]\n[%s]\n", getCurrentTimestamp().c_str(), filename, line, func, expr, msg);
#else
	sprintf(szTemp, "[T=%s][%s][%d][%s][%s]\n[%s]", getCurrentTimestamp().c_str(), filename, line, func, expr, msg);
#endif
	//__show__(szTemp);
	static std::ofstream file(std::string("../../log/assert.log"), std::ios::app | std::ios::binary);

	if (!file.is_open()) {
		return;
	}

	file << szTemp;
	//file.close();

	Log(szTemp);

	throw(1);
}