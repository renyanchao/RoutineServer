#include "LogRoutine.h"
#include <iostream>


void LogRoutine::HandleMsg(const MessagePtr& msgPtr)
{
	const Message_log& logMsg = dynamic_cast<const Message_log&>(*msgPtr);
	std::cout << logMsg.szLog << std::endl;
}