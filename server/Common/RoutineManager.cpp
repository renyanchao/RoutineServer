#include "RoutineManager.h"
#include "ThreadPool.h"
#include "Routine.h"
RoutineManager g_RoutineManager;


bool RoutineManager::SendMsg2Routine(RoutineID nID, const MessagePtr& message)
{
	for (auto it = m_AllRoutine.begin(); it != m_AllRoutine.end(); it++)
	{
		if ((*it)->GetRoutineID() == nID)
		{
			(*it)->Push(message);
		}
	}
	return false;
}
bool RoutineManager::SendMsg2RoutineType(RoutineType nType, const MessagePtr& message)
{
	for (auto it = m_AllRoutine.begin(); it != m_AllRoutine.end(); it++)
	{
		if ((*it)->GetRoutineType() == nType)
		{
			(*it)->Push(message);
		}
	}
	return false;
}
void RoutineManager::RegisterRoutine(std::shared_ptr<Routine> r)
{
	r->SetRoutineID(m_GenerateRoutineID++);
	m_AllRoutine.push_back(r);
	g_threadPool.AddTask(r);
}
void RoutineManager::UnRegisterRoutine(std::shared_ptr<Routine> r)
{

	for (auto it = m_AllRoutine.begin(); it != m_AllRoutine.end(); it++)
	{
		if ((*it)->GetRoutineID() == r->GetRoutineID())
		{
			m_AllRoutine.erase(it);
			break;
		}
	}
}