#include "PicturaPCH.h"
#include "Thread.h"

namespace Pictura::Threading
{
	Vector<Tuple<uint64, Thread*>> Thread::ThreadStack = { };
	bool Thread::locker = false;

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
			isRunning = false;
			threadObj = Types::MakeUnique<std::thread>([]() {});
			Debug::Log::GetFrameworkLog().Debug("Stopping thread [" + ThreadName + "]");

			threadObj.reset();
		}
		else
		{
			Debug::Log::GetFrameworkLog().Warning("Thread [" + ThreadName + "] was stopped but not correctly...");
			Debug::Log::GetFrameworkLog().Warning("A memory leak is possible !");
		}
	}

	Thread* Thread::CurrentThread()
	{
		uint64 CTID = std::hash<std::thread::id>{}(std::this_thread::get_id());
		for (auto& t : ThreadStack)
		{
			if (GetTupleValue<Thread*>(t)->ThreadId == CTID)
			{
				return GetTupleValue<Thread*>(t);
			}
		}

		throw ThreadException("The current thread was not found... Avoid to call this function from the main thread.");
		return nullptr;
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
}