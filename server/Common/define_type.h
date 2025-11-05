#pragma once
#include<basetsd.h>
#include<functional>


#define REGCALLBACK(id,func) add_message_handler(id,func)
#define MAX_MESSAGE_PTR_ARRAY_SIZE 512
#define READMESSAGESPACESIZE 20

#define MAX_ACCEPT_SESSION_COUNT 1024

#define MAX_IO_WORKER_THREAD 2

typedef UINT64 PlayerID;
typedef UINT32 RoomId;
typedef UINT32 SessionID;
typedef UINT32 SOCKID;


typedef std::function<bool(char*, PlayerID, SessionID SessionId)> MESSAGEHANDLER;


struct SOCKTYPE{
	SOCKID sockfd;
	enum Type
	{
		connect,
		close,
		normal,
	};
	Type type;
	SOCKTYPE(SOCKID,Type) {}
};

enum READTYPE{
	CLOSE,
	READHEAD,
	READBODY,

	MAX
}


enum MESSAGEINDEX {

	LOG = 1,
	LOGOUT,
	REGISTER,


	

	GT_REG_DB,
	GT_REG_GM,
	GM_REG_DB,
	GM_REG_GT,
	DB_REG_GT,
	DB_REG_GM,

	MESSAGE_MAX
};


//1）从流read后，组装成PACKET结构 交付给逻辑线程
//2）待发送数据，组装成PACKET结构 交付给发送线程
struct PACKET{		
	uint64_t m_sockfd;
	char m_data[MAX_MESSAGE_PTR_ARRAY_SIZE];

	PACKET(uint64_t sockfd):m_sockfd(sockfd){}
	~PACKET()
}


//消息结构
struct message_head{
	int32_t m_length;

	message_head(char*buf){
		memcpy(m_length,buf,buf+sizeof(m_length));


	}
};

struct message_body:public message_head{
	MESSAGEINDEX m_index;

};