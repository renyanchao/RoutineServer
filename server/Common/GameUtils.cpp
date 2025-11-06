#include "RoutineManager.h"
#include "stdarg.h"
#include "stdio.h"
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