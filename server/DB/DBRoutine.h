#pragma once

#include "Routine.h"

class DBRoutine :public Routine
{
public:
	virtual int32_t GetRoutineType()
	{
		return RoutineType::DB;
	}
	void HeartBeat(int32_t nMillisecond);
};