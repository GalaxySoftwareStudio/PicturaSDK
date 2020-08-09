#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Threading
{
	class Thread
	{
	public:
		typedef NativeHandleType ThreadHandle;
		
		enum class ThreadPriority
		{
			Low = -2,
			BelowNormal = -1,
			Normal = 0,
			AboveNormal = 1,
			High = 2
		};

	public:
		Thread()
		{

		}

		template <typename... _Args>
		Thread(void(*function)(_Args...), _Args ...args)
		{
			if (function != nullptr)
			{
				threadObj = new std::thread(function, args...);
				isRunning = true;

				ThreadId = std::hash<std::thread::id>{}(threadObj->get_id());
				ThreadName = "THREAD_" + Types::ToString(ThreadId);
				Handle = threadObj->native_handle();
				ThreadStack.insert(ThreadStack.begin(), { ThreadId, this });
				threadObj->detach();
			}
		}

		template <typename U, typename... _Args>
		Thread(void(U::* function)(_Args...), U* thisPtr, _Args ...args)
		{
			if (function != nullptr)
			{
				threadObj = new std::thread(function, thisPtr, args...);
				isRunning = true;

				ThreadId = std::hash<std::thread::id>{}(threadObj->get_id());
				ThreadName = "THREAD_" + Types::ToString(ThreadId);
				Handle = threadObj->native_handle();
				ThreadStack.insert(ThreadStack.begin(), { ThreadId, this });
				threadObj->detach();
			}
		}

		~Thread()
		{
			StopThread();
		}

	public:
		void StopThread();

	public:
		static void LockThread();
		static void UnlockThread();
		static void Delay(int milliseconds);
		static void SetPriority(Thread& thread, ThreadPriority priority);
		static Thread* CurrentThread();
		static void StopAllThread();

	public:
		String ThreadName;
		ThreadHandle Handle;

	private:
		static Atomic<bool> locker;
		bool isRunning;
		std::thread* threadObj;
		uint64 ThreadId;

		static Map<uint64, Thread*> ThreadStack;
	};
}


