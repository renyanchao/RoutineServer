#pragma once

#define MAX_THREAD_NUM 24
#define MAX_THREAD_LOCAL_POOL_SIZE 1024
#define MAX_THREAD_TOTAL_POOL_SIZE (1024 * 64)
#define THREAD_SLEEP_TIME_MS 10
#define INVALID_ID (-1)

#define RoutineID unsigned long long
#define RoldID unsigned long long


#if defined(_WIN32)
#include <Windows.h>
#include "crtdbg.h"
#elif defined(__LINUX__)
	#include <sys/types.h>
	#include <pthread.h>
	#include <execinfo.h>
	#include <signal.h>
	#include <exception>
	#include <setjmp.h>
	#include <sys/epoll.h>
#include <sys/utsname.h>
#include <sys/time.h>
#endif
enum RoutineType
{
	LOG = 0,
	LOGIN,
	MANAGER,//Manager
	SCNE,
	MAIL,
	DB,
	Net,
	Redis,
	Max,
};

enum MsgID
{
	MsgID_Message_Invalid = -1,
	MsgID_Message_1 = 0,
	MsgID_Message_2,
	MsgID_Message_3,
	MsgID_Message_log,
	MsgID_Message_createscene,
};

void Log(const char* msg, ...);


struct TimeElpaseInfo
{
	uint64_t m_nCurrencyTime = 0;
	uint32_t m_nElpaseTime = 0;
};
uint64_t GetCurrencyTime();


#include <thread>
#include <shared_mutex>

#define lock_read(MUTEX) std::shared_lock<std::shared_mutex> __Lock__(MUTEX)
#define lock_write(MUTEX) std::lock_guard<std::shared_mutex> __Lock__(MUTEX)
#define sleep_ms(MS) std::this_thread::sleep_for(std::chrono::milliseconds(MS));