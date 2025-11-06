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




VOID __show__(const CHAR* szTemp)
{

}
void __assertex__(const CHAR* file, UINT line, const CHAR* func, const CHAR* expr, const CHAR* msg)
{
	CHAR szTemp[1024] = { 0 };

#ifdef __LINUX__
	sprintf(szTemp, "[%s][%d][%s][%s]\n[%s]\n", file, line, func, expr, msg);
#else
	sprintf(szTemp, "[%s][%d][%s][%s]\n[%s]", file, line, func, expr, msg);
#endif
	//__show__(szTemp);

	FILE* f = fopen("./Log/assert.log", "a");
	if (f)
	{
		fwrite(szTemp, 1, strlen(szTemp), f);
		fwrite("\r\n", 1, 2, f);
		fclose(f);
	}
	Log(szTemp);

	throw(1);
}