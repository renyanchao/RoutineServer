#include "DBRoutine.h"

void DBRoutine::HeartBeat(int32_t nMillisecond)
{
	Log("DBRoutine Tick() %d", std::this_thread::get_id());
}