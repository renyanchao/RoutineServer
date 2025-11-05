#pragma once

#include "Routine.h"

class SceneRoutine : public Routine
{
public:
	virtual int32_t GetRoutineType()
	{
		return RoutineType::SCNE;
	}
	void HeartBeat(int32_t nMillisecond);
	void CreateMonster();
	void CreatePlayer();
	void CreateScene();
	uint32_t GetLeftTime()const { return m_LeftLifeTime; }
private:
	int32_t m_LeftLifeTime = 6 * 1000;
private:
	ScenePlayerManager m_PlayerManager;
	SceneMonsterManager m_MonsterManager;
	//ScenePtr m_pScene;
};