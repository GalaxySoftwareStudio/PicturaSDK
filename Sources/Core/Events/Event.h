#pragma once
#include "Core/CoreFramework.h"
#include "EventArgs/EventArgs.h"

using namespace Pictura::Events;

namespace Pictura
{
	template<typename T>
	class EventHandlerImplBase
	{
	public:
		EventHandlerImplBase() {}
		virtual ~EventHandlerImplBase() {}
		virtual bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>*) = 0;
		bool IsSametype(EventHandlerImplBase<T>* pHandler2)
		{
			return !static_cast<bool>(!pHandler2 || typeid(*this) != typeid(*pHandler2));
		}
	};

	template<typename T>
	class EventHandlerImpl : public EventHandlerImplBase<T>
	{
	public:
		virtual void OnEvent(T&) = 0;
	};
	template<typename T>
	class EventHandlerImplForNonMemberFunction : public EventHandlerImpl<T>
	{
	public:
		EventHandlerImplForNonMemberFunction(void(*functionToCall)(T&))
			: m_pFunctionToCall(functionToCall)
		{
		}

		void OnEvent(T& evt) override
		{
			m_pFunctionToCall(evt);
		}

		bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>* pHandler2) override
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}
			EventHandlerImplForNonMemberFunction<T>* pHandlerCasted = dynamic_cast<EventHandlerImplForNonMemberFunction<T>*>(pHandler2);
			if (!pHandlerCasted)
			{
				return false;
			}

			return this->m_pFunctionToCall == pHandlerCasted->m_pFunctionToCall;
		}

	private:
		void(*m_pFunctionToCall)(T&);
	};
	template<typename T, typename U>
	class EventHandlerImplForMemberFunction : public EventHandlerImpl<T>
	{
	public:
		EventHandlerImplForMemberFunction(void(U::* memberFunctionToCall)(T&), U* thisPtr)
			: m_pCallerInstance(thisPtr)
			, m_pMemberFunction(memberFunctionToCall)
		{
		}

		void OnEvent(T& evt) override
		{
			if (m_pCallerInstance)
			{
				(m_pCallerInstance->*m_pMemberFunction)(evt);
			}
		}

		bool IsBindedToSameFunctionAs(EventHandlerImplBase<T>* pHandler2) override
		{
			if (!this->IsSametype(pHandler2))
			{
				return false;
			}
			auto* pHandlerCasted = dynamic_cast<EventHandlerImplForMemberFunction<T, U>*>(pHandler2);
			if (!pHandlerCasted)
			{
				return false;
			}

			return this->m_pCallerInstance == pHandlerCasted->m_pCallerInstance && this->m_pMemberFunction == pHandlerCasted->m_pMemberFunction;
		}

	private:
		U* m_pCallerInstance;
		void(U::* m_pMemberFunction)(T&);
	};
	template<>
	class EventHandlerImpl<void> : public EventHandlerImplBase<void>
	{
	public:
		virtual void OnEvent() = 0;
	};
	template<>
	class EventHandlerImplForNonMemberFunction<void> : public EventHandlerImpl<void>
	{
	public:
		EventHandlerImplForNonMemberFunction(void(*functionToCall)())
			: m_pFunctionToCall(functionToCall)
		{
		}

		void OnEvent() override
		{
			m_pFunctionToCall();
		}

		bool IsBindedToSameFunctionAs(EventHandlerImplBase<void>* pHandler2) override
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}
			auto* pHandlerCasted = dynamic_cast<EventHandlerImplForNonMemberFunction<void>*>(pHandler2);
			if (!pHandlerCasted)
			{
				return false;
			}

			return this->m_pFunctionToCall == pHandlerCasted->m_pFunctionToCall;
		}

	private:
		void(*m_pFunctionToCall)();
	};
	template<typename U>
	class EventHandlerImplForMemberFunction<void, U> : public EventHandlerImpl<void>
	{
	public:
		EventHandlerImplForMemberFunction(void(U::* memberFunctionToCall)(), U* thisPtr)
			: m_pCallerInstance(thisPtr)
			, m_pMemberFunction(memberFunctionToCall)
		{
		}

		void OnEvent() override
		{
			if (m_pCallerInstance)
			{
				(m_pCallerInstance->*m_pMemberFunction)();
			}
		}

		bool IsBindedToSameFunctionAs(EventHandlerImplBase<void>* pHandler2) override
		{
			if (!IsSametype(pHandler2))
			{
				return false;
			}
			auto* pHandlerCasted = dynamic_cast<EventHandlerImplForMemberFunction<void, U>*>(pHandler2);
			if (!pHandlerCasted)
			{
				return false;
			}

			return this->m_pCallerInstance == pHandlerCasted->m_pCallerInstance && this->m_pMemberFunction == pHandlerCasted->m_pMemberFunction;
		}

	private:
		U* m_pCallerInstance;
		void(U::* m_pMemberFunction)();
	};
	class EventHandler
	{
	public:
		template<typename T>
		static EventHandlerImpl<T>* Bind(void(*nonMemberFunctionToCall)(T&))
		{
			return new EventHandlerImplForNonMemberFunction<T>(nonMemberFunctionToCall);
		}
		template<typename T, typename U>
		static EventHandlerImpl<T>* Bind(void(U::* memberFunctionToCall)(T&), U* thisPtr)
		{
			return new EventHandlerImplForMemberFunction<T, U>(memberFunctionToCall, thisPtr);
		}
		static EventHandlerImpl<void>* Bind(void(*nonMemberFunctionToCall)())
		{
			return new EventHandlerImplForNonMemberFunction<void>(nonMemberFunctionToCall);
		}
		template<typename U>
		static EventHandlerImpl<void>* Bind(void(U::* memberFunctionToCall)(), U* thisPtr)
		{
			return new EventHandlerImplForMemberFunction<void, U>(memberFunctionToCall, thisPtr);
		}

	private:
		EventHandler();
	};
	template<typename T>
	class EventBase
	{
	public:
		EventBase() = default;

		virtual ~EventBase()
		{
			for (auto iter = m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<T>* pHandler = *iter;
				if (pHandler)
				{
					delete pHandler;
					pHandler = 0;
				}
			}
			m_eventHandlers.clear();
		}
		EventBase<T>& operator += (EventHandlerImpl<T>* pHandlerToAdd)
		{

			if (pHandlerToAdd)
			{
				m_eventHandlers.push_back(pHandlerToAdd);
			}

			return *this;
		}
		EventBase<T>& operator -= (EventHandlerImpl<T>* pHandlerToRemove)
		{
			if (!pHandlerToRemove)
			{
				return *this;
			}

			for (typename std::list< EventHandlerImpl<T>* >::iterator iter = m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<T>* pHandler = *iter;
				if (pHandlerToRemove->IsBindedToSameFunctionAs(pHandler))
				{
					EventHandlerImpl<T>* pFoundHandler = *iter;
					if (pFoundHandler)
					{
						delete pFoundHandler;
						pFoundHandler = 0;
					}
					m_eventHandlers.erase(iter);
					break;
				}
			}
			if (pHandlerToRemove)
			{
				delete pHandlerToRemove;
				pHandlerToRemove = 0;
			}

			return *this;
		}

	private:
		EventBase(const EventBase&);
		EventBase& operator=(const EventBase&);

	protected:
		std::list< EventHandlerImpl<T>* > m_eventHandlers{};

	};
	template<typename T>
	class Event : public EventBase<T>
	{
	public:
		void operator()(T& eventData)
		{
			for (auto iter = EventBase<T>::m_eventHandlers.begin(); iter != EventBase<T>::m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<T>* pHandler = *iter;
				if (pHandler)
				{
					pHandler->OnEvent(eventData);
				}
			}
		}
	};

	template<>
	class Event<void> : public EventBase<void>
	{
	public:
		void operator()()
		{
			for (std::list< EventHandlerImpl<void>* >::iterator iter = m_eventHandlers.begin(); iter != m_eventHandlers.end(); ++iter)
			{
				EventHandlerImpl<void>* pHandler = *iter;
				if (pHandler)
				{
					pHandler->OnEvent();
				}
			}
		}
	};

#define event(EventArgsClass, EventName)\
	virtual void On##EventName(EventArgsClass& e) { EventName(e); }\
	Event<EventArgsClass> EventName
}