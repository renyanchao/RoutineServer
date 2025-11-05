#pragma once
#include "Routine.h"

class MailRoutine : public Routine
{
public:
	virtual int32_t GetRoutineType()
	{
		return RoutineType::MAIL;
	}
	void HeartBeat(int32_t nMillisecond);
};