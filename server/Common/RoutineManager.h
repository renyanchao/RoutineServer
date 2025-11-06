#pragma once


#include <list>
#include <shared_mutex>
#include "GameDefine.h"
#include "ObjType.h"


class Routine;
class RoutineManager
{
public:

	bool SendMsg2Routine(RoutineID nID, const MessagePtr& message);
	bool SendMsg2RoutineType(RoutineType nType, const MessagePtr& message);
	void RegisterRoutine(std::shared_ptr<Routine> r, bool startserver = false);
	//void UnRegisterRoutine(std::shared_ptr<Routine> r);

private:

	std::list<std::shared_ptr<Routine>> m_AllRoutine;
	uint64_t m_GenerateRoutineID;
	std::shared_mutex m_Lock;

};
extern RoutineManager g_RoutineManager;