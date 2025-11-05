#include"Routine.h"
#include"ObjType.h"
#include<iostream>
#include"ThreadPool.h"

#include"stdarg.h"

Routine::Routine()
{
	RegisterHandlerInit();
}
Routine:: ~Routine()
{}



void Routine::Tick(int32_t nMillisecond)
{
	m_elapsetime += nMillisecond;
	if (m_elapsetime < TickInteral())return;
	m_elapsetime = 0;
	for (int i = 0; i < 128; i++)
	{
		auto msgPtr = Pop();
		if (msgPtr == nullptr)break;
		
		if (m_HandlerList[msgPtr->GetID()])
		{
			m_HandlerList[msgPtr->GetID()](msgPtr);
		}
		
	}
	HeartBeat(nMillisecond);
}

//Local Other Routine Push to me
void Routine::Push(MessagePtr ptr)
{
	std::lock_guard<std::mutex> pushlock(m_PushLock);
	m_PushList.push_back(ptr);
}
//Self Pop
MessagePtr Routine::Pop()
{
	if (m_PopList.empty() == false)
	{
		auto p = m_PopList.front();
		m_PopList.pop_front();
		return p;
	}

	std::lock_guard<std::mutex> pushlock(m_PushLock);
	std::lock_guard<std::mutex> poplock(m_PopLock);

	m_PopList.swap(m_PushList);
	if (m_PopList.empty() == false)
	{
		auto p = m_PopList.front();
		m_PopList.pop_front();
		return p;
	}
	return nullptr;
}

void Routine::RegisterHandler(MsgID nMsgID, std::function<void(const MessagePtr)> handler)
{
	m_HandlerList[nMsgID] = handler;
}

void Routine::MsgDefaultHandler(const MessagePtr& rMsgPtr)
{
	std::cout << "MsgDefaultHandler " << std::endl;
}

void Routine::RegisterHandlerInit()
{
	RegisterHandler(MsgID::Message_Invalid, std::bind(&Routine::MsgDefaultHandler, this, std::placeholders::_1));
}

void LogRoutine::HandleMsg(const MessagePtr& msgPtr)
{
	const Message_log& logMsg = dynamic_cast<const Message_log&>(*msgPtr);
	std::cout << logMsg.szLog << std::endl;
}

void Log(const char* msg, ...)
{
	auto msgPtr = POOL_NEW(Message_log);
	
	va_list argptr;

	va_start(argptr, msg);
	vsprintf_s(msgPtr->szLog, msg, argptr);
	va_end(argptr);
	g_RoutineManager.SendMsg2RoutineType(RoutineType::LOG, msgPtr);
}

void LoginRoutine::HeartBeat(int32_t nMillisecond)
{
	//Log("LoginRoutine Tick() %d", std::this_thread::get_id());
	
}



void MailRoutine::HeartBeat(int32_t nMillisecond)
{
	//Log("MailRoutine Tick() %d", std::this_thread::get_id());
}

void DBRoutine::HeartBeat(int32_t nMillisecond)
{
	//Log("DBRoutine Tick() %d", std::this_thread::get_id());
}
void RedisRoutine::HeartBeat(int32_t nMillisecond)
{
	//Log("RedisRoutine Tick() %d", std::this_thread::get_id());
}



void SceneRoutine::HeartBeat(int32_t nMillisecond)
{
	if (m_LeftLifeTime <= 0)return;

	Log("RoutineID(%d) SceneRoutine Tick() m_LeftLifeTime(%d) ", GetRoutineID(), m_LeftLifeTime);
	m_LeftLifeTime = std::max(0, m_LeftLifeTime - nMillisecond);
	if (m_LeftLifeTime == 0)
	{
		//Scene die
		m_PlayerManager.Clear();
		m_MonsterManager.Clear();
		Log("RoutineID(%d) SceneRoutine Die() ", GetRoutineID());;
		return;

	}


	if (std::rand() % 100 <= 50)
	{
		//CreateScene
	}
	if (std::rand() % 100 <= 80)
	{
		CreatePlayer();
	}
	if (std::rand() % 100 <= 80)
	{
		CreateMonster();
	}

	m_PlayerManager.HeartBeat();
	m_MonsterManager.HeartBeat();
}

void SceneRoutine::CreateMonster()
{
	ObjMonsterPtr ptr = POOL_NEW(ObjMonster);
	m_MonsterManager.AddMonster(ptr);

	Log("RoutineID(%d) SceneRoutine CreateMonster() ", GetRoutineID());;
}

void SceneRoutine::CreatePlayer()
{
	ObjPlayerPtr ptr = POOL_NEW(ObjPlayer);
	m_PlayerManager.AddPlayer(ptr);

	Log("RoutineID(%d) SceneRoutine CreatePlayer() ", GetRoutineID());;
}
void SceneRoutine::CreateScene()
{

}