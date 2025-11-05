#pragma once

#include "Routine.h"

class RedisRoutine :public Routine
{
public:
	virtual int32_t GetRoutineType()
	{
		return RoutineType::Redis;
	}
	void HeartBeat(int32_t nMillisecond);
};