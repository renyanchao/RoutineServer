#pragma once

#define MAX_THREAD_NUM 64
#define MAX_THREAD_LOCAL_POOL_SIZE 1024
#define MAX_THREAD_TOTAL_POOL_SIZE (1024 * 64)

#define INVALID_ID (-1)

#define RoldID uint64_t
#define RoutineID uint64_t
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

enum class MsgID
{
	Message_Invalid = -1,
	Message_1 = 0,
	Message_2,
	Message_3,
	Message_log,
	Message_createscene,
};

void Log(const char* msg, ...);