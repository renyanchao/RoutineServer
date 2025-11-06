#include "SceneRoutine.h"
#include "RoutineManager.h"

void SceneRoutine::HeartBeat(const TimeElpaseInfo& info)
{
	if (m_LeftLifeTime <= 0)return;

	Log("RoutineID(%d) SceneRoutine Tick() m_LeftLifeTime(%d), nCurrencyTime(%d) ", GetRoutineID(), m_LeftLifeTime, info.m_nCurrencyTime);
	m_LeftLifeTime =  m_LeftLifeTime - info.m_nElpaseTime;
	if (m_LeftLifeTime <= 0)
	{
		//Scene die
		m_PlayerManager.Clear();
		m_MonsterManager.Clear();
		Log("RoutineID(%d) SceneRoutine Die() ", GetRoutineID());;
		return;

	}


	if (std::rand() % 100 <= 50)
	{
		CreateScene();
	}
	if (std::rand() % 100 <= 100)
	{
		CreatePlayer();
	}
	if (std::rand() % 100 <= 100)
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
	Log("RoutineID(%d) SceneRoutine CreatePlayer() Try Begin", GetRoutineID());
	g_RoutineManager.RegisterRoutine(std::make_shared<SceneRoutine>());
	Log("RoutineID(%d) SceneRoutine CreatePlayer() Try Finish", GetRoutineID());
}