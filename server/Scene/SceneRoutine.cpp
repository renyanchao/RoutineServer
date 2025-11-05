#include "SceneRoutine.h"


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