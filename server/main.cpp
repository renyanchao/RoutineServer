

#include "RoutineManager.h"
#include "ThreadPool.h"


#include "Log/LogRoutine.h"
#include "Scene/SceneRoutine.h"

int main()
{
	g_threadPool.Start();


	g_RoutineManager.RegisterRoutine(std::make_shared<LogRoutine>(), true);

	//g_RoutineManager.RegisterRoutine(std::make_shared<LoginRoutine>());
	g_RoutineManager.RegisterRoutine(std::make_shared<SceneRoutine>(), true);
	//g_RoutineManager.RegisterRoutine(std::make_shared<MailRoutine>());
	//g_RoutineManager.RegisterRoutine(std::make_shared<DBRoutine>());
	//g_RoutineManager.RegisterRoutine(std::make_shared<RedisRoutine>());
	getchar();
}