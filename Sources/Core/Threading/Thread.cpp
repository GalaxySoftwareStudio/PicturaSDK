#include "PicturaPCH.h"
#include "Thread.h"

namespace Pictura::Threading
{
	Map<uint64, Thread*> Thread::ThreadStack = { };
	Atomic<bool> Thread::locker = false;

	void Thread::SetPriority(Thread& thread, ThreadPriority priority)
	{

	}

	void Thread::Delay(int milliseconds)
	{
		#ifdef PLATFORM_WINDOWS
			Sleep(milliseconds);
		#else
			struct timespec request = {0};
			request.tv_nsec = milliseconds * 1000000L;
			nanosleep(&request, (struct timespec *)NULL);
		#endif
	}

	void Thread::StopThread()
	{
		if (threadObj != nullptr && isRunning)
		{
			if (threadObj->joinable())
			{
				Debug::Log::GetFrameworkLog().Debug("Joining thread [" + ThreadName + "]");
				threadObj->join();
			}

			ThreadStack.erase(ThreadId);

			isRunning = false;
			threadObj = new std::thread([]() {});
			Debug::Log::GetFrameworkLog().Debug("Stopping thread [" + ThreadName + "]");
		}
		else
		{
			Debug::Log::GetFrameworkLog().Warning("Thread [" + ThreadName + "] was stopped but not correctly...");
			Debug::Log::GetFrameworkLog().Warning("A memory leak is possible !");
		}
	}

	Thread* Thread::CurrentThread()
	{
		Thread* nullThread = new Thread();
		nullThread->ThreadName = "UnknownThread_0";
		nullThread->ThreadId = 0;
		try
		{
			uint64 CTID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			if (ThreadStack.find(CTID) == ThreadStack.end())
			{
				Debug::Log::GetFrameworkLog().Warning("Current thread handle was not found !");
				return nullThread;
			}

			return ThreadStack.at(CTID);
		}
		catch (const std::exception&)
		{
			Debug::Log::GetFrameworkLog().Warning("Current thread handle was not found !");
			return nullThread;
		}
	}

	void Thread::LockThread()
	{
		if (locker)
		{
			throw InvalidOperationException("You can't lock two thread at the same time, unlock the previous thread first.");
		}
		else
		{
			locker = true;
			while (locker)
			{

			}
		}
	}

	void Thread::UnlockThread()
	{
		locker = false;
	}

	void Thread::StopAllThread()
	{
		for (auto const& [id, thread] : ThreadStack)
		{
			thread->StopThread();
		}
	}
}