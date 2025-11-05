#include"ThreadPool.h"
#include"ObjType.h"

void Thread::Start()
{
	std::thread mt(TaskFunc, std::ref(*this));
	t = std::move(mt);
	t.detach();
}
void Thread::AddTask(std::shared_ptr<Routine> r)
{
	std::lock_guard<std::mutex> lock(m_lock);
	m_TaskList.push_back(r);
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
	
	std::lock_guard<std::mutex> lock(m_lock);
	
	auto nowTime = std::chrono::system_clock::now();
	auto elpasetime = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - m_threadTimer).count();
	m_threadTimer = nowTime;
	std::list<std::shared_ptr<Routine>> dielist;
	for (auto& r : m_TaskList)
	{
		r->Tick(elpasetime);
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
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}


ThreadPool::ThreadPool()
{
	for (int i = 0; i < MAX_THREAD_NUM; i++)
	{
		m_allThread.push_back(std::make_shared<Thread>());
	}
}
ThreadPool::~ThreadPool() {}


void ThreadPool::Start()
{
	for (auto it = m_allThread.begin(); it != m_allThread.end(); it++)
	{
		(*it)->Start();
	}
}
void ThreadPool::Tick() {};
void ThreadPool::AddTask(std::shared_ptr<Routine>& r)
{
	int nIndex = r->GetRoutineID() % m_allThread.size();
	m_allThread[nIndex]->AddTask(r);
}