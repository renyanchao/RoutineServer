#pragma once
#include<thread>
#include<vector>
#include<iostream>
#include<map>
#include<mutex>
#include<list>
#include "GameDefine.h"

class Thread;
class Routine;
extern void TaskFunc(Thread& t);
class Thread
{
public:
	void Start();
	void AddTask(std::shared_ptr<Routine> r);
	void Tick();
	void DelTask(RoutineID nID);
private:
	std::chrono::time_point<std::chrono::system_clock> m_threadTimer = std::chrono::system_clock::now();
	std::mutex m_lock;
	std::thread t;
	std::vector<std::shared_ptr<Routine>> m_TaskList;
};
class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();


	void Start();
	void Tick();
	void AddTask(std::shared_ptr<Routine>& r);

public:

private:
	std::vector<std::shared_ptr<Thread>> m_allThread;

};
extern ThreadPool g_threadPool;


#include"Routine.h"
class RoutineManager
{
public:

	bool SendMsg2Routine(RoutineID nID, const MessagePtr& message)
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
	bool SendMsg2RoutineType(RoutineType nType, const MessagePtr& message)
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
	void RegisterRoutine(std::shared_ptr<Routine> r)
	{
		r->SetRoutineID(m_GenerateRoutineID++);
		m_AllRoutine.push_back(r);
		g_threadPool.AddTask(r);
	}
	void UnRegisterRoutine(std::shared_ptr<Routine> r)
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

private:

	std::list<std::shared_ptr<Routine>> m_AllRoutine;
	uint64_t m_GenerateRoutineID;
	std::mutex m_Lock;

};
extern RoutineManager g_RoutineManager;