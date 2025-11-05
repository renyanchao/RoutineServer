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
