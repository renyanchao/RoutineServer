#include "Thread.h"
#include "Routine.h"

void Thread::Start()
{
//	std::thread mt(TaskFunc, std::ref(*this));
	std::thread mt([this] {while (true)this->Tick(); });
	t = std::move(mt);
	t.detach();
}
void Thread::AddTask(std::shared_ptr<Routine> r)
{
	std::lock_guard<std::mutex> lock(m_lock);
	m_AddTaskList.push_back(r);
}
void Thread::DelTask(RoutineID nID)
{
	std::lock_guard<std::mutex> lock(m_lock);
	for (auto it = m_TaskList.begin(); it != m_TaskList.end(); it++)
	{
		if (nID == (*it)->GetRoutineID())
		{
			m_TaskList.erase(it);
			return;
		}
	}
}
void Thread::Tick()
{
	{
		std::lock_guard<std::mutex> lock(m_lock);
		m_TaskList.insert(m_TaskList.end(), std::make_move_iterator(m_AddTaskList.begin()), std::make_move_iterator(m_AddTaskList.end()));
		m_AddTaskList.clear();

	}
	

	TimeElpaseInfo elpasetimeInfo;
	elpasetimeInfo.m_nCurrencyTime = GetCurrencyTime();
	elpasetimeInfo.m_nElpaseTime = elpasetimeInfo.m_nCurrencyTime - m_nCurrencyTime;

	m_nCurrencyTime = elpasetimeInfo.m_nCurrencyTime;

	std::list<std::shared_ptr<Routine>> dielist;
	for (auto& r : m_TaskList)
	{
		try
		{
			r->Tick(elpasetimeInfo);
		}
		catch (...)
		{
		}
		if (r->GetLeftTime() <= 0)
		{
			dielist.push_back(r);
		}
	}
	for (auto& r : dielist)
	{
		for (auto it = m_TaskList.begin(); it != m_TaskList.end(); it++)
		{
			if ((*it)->GetRoutineID() == r->GetRoutineID())
			{
				m_TaskList.erase(it);
				break;
			}
		}
	}
	if (THREAD_SLEEP_TIME_MS > 0)
		sleep_ms(THREAD_SLEEP_TIME_MS);
}
