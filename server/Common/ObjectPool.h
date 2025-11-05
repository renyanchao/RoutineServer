#pragma once

#include<vector>
#include<deque>
#include<array>
#include<memory>
#include <algorithm>
#include"GameDefine.h"
#include<thread>

template<typename T, int32_t nMaxPoolSize = MAX_THREAD_LOCAL_POOL_SIZE, int32_t nInitPoolSize = MAX_THREAD_LOCAL_POOL_SIZE>
class ObjPool_v3
{
	using Ptr = std::shared_ptr<T>;
	using PtrList = std::vector<Ptr>;



public:
	ObjPool_v3()
	{
		m_thread_objlist.reserve(nMaxPoolSize);
		for (int32_t size = 0; size < nMaxPoolSize; size++)
		{
			m_thread_objlist.push_back(std::make_shared<T>());
		}
	}
	~ObjPool_v3()
	{

	}
	Ptr New()
	{

		PtrList& thread_local_list = m_thread_objlist;
		for (int i = 0; i < thread_local_list.size(); i++)
		{
			if (thread_local_list[i].use_count() == 1)
			{
				return thread_local_list[i];
			}

		}
		return std::make_shared<T>();
	}

	void OutLog()
	{
		int nTotalNum = 0;
		int nFreeNum = 0;
		PtrList& list = m_thread_objlist;
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i].use_count() == 1)
			{
				nFreeNum += 1;
			}
			nTotalNum += 1;
		}
		{

			printf("ThreadID = %d , nTotalNum = %d, nFreeNum = %d\n", std::this_thread::get_id(), nTotalNum, nFreeNum);
		}
	}

private:
	PtrList m_thread_objlist;
};


#define POOL_DEFINE(T) extern thread_local ObjPool_v3<T> g_ObjPool_##T;\
	using T##Ptr = std::shared_ptr<T>;
#define POOL_NEW(T) g_ObjPool_##T.New();
#define POOL_INST(T) thread_local ObjPool_v3<T> g_ObjPool_##T;
