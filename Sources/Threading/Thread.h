#pragma once
#include "Core/CoreFramework.h"
#include "Core/Exceptions/Exceptions.h"

namespace Pictura::Threading
{
	class Thread
	{
	public:
		typedef void* ThreadHandle;

		enum class ThreadPriority
		{
			Low = -2,
			BelowNormal = -1,
			Normal = 0,
			AboveNormal = 1,
			High = 2
		};

	public:
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
				threadObj->detach();

				ThreadStack.push_back(Types::MakeTuple(ThreadId, this));

				Debug::Log::GetFrameworkLog().Debug("Creating thread [" + ThreadName + "]");
			}
		}

		template <typename U, typename... _Args>
		Thread(void(U::* function)(_Args...), U* thisPtr, _Args ...args)
		{
			if (function != nullptr)
			{
				threadObj = Types::MakeUnique<std::thread>(function, thisPtr, args...);
				isRunning = true;

				ThreadId = std::hash<std::thread::id>{}(threadObj->get_id());
				ThreadName = "THREAD_" + Types::ToString(ThreadId);
				Handle = threadObj->native_handle();
				threadObj->detach();

				ThreadStack.push_back(Types::MakeTuple(ThreadId, this));

				Debug::Log::GetFrameworkLog().Debug("Creating thread [" + ThreadName + "]");
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

	public:
		String ThreadName;
		ThreadHandle Handle;

	private:
		static bool locker;
		bool isRunning;
		UniquePtr<std::thread> threadObj;
		uint64 ThreadId;

		static Vector<Tuple<uint64, Thread*>> ThreadStack;
	};
}


