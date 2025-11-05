#include"ThreadPool.h"
#include "GameDefine.h"
#include"Routine.h"


extern void TaskFunc(Thread& t)
{
	while (true)
	{
		t.Tick();
	}
}
ThreadPool g_threadPool;
RoutineManager g_RoutineManager;

int main()
{
	g_threadPool.Start();


	g_RoutineManager.RegisterRoutine(std::make_shared<LogRoutine>());

	//g_RoutineManager.RegisterRoutine(std::make_shared<LoginRoutine>());
	g_RoutineManager.RegisterRoutine(std::make_shared<SceneRoutine>());
	//g_RoutineManager.RegisterRoutine(std::make_shared<MailRoutine>());
	//g_RoutineManager.RegisterRoutine(std::make_shared<DBRoutine>());
	//g_RoutineManager.RegisterRoutine(std::make_shared<RedisRoutine>());
	getchar();
}