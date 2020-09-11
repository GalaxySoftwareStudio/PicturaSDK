#pragma once
#include "PicturaPCH.h"

#pragma warning(disable : 4311 4302)
using String = std::string;
using WideString = std::wstring;

using NativeHandleType = std::thread::native_handle_type;

template <typename T>
using Function = std::function<T>;

template <typename T>
using Vector = std::vector<T>;

template <typename T, typename T2>
using Pair = std::pair<T, T2>;

template <typename T, typename T2>
using Map = std::map<T, T2>;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename T>
using List = std::list<T>;

using Mutex = std::mutex;

template <typename T>
using Atomic = std::atomic<T>;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

template <typename... A>
using Tuple = std::tuple<A...>;

template <typename T, typename... A>
auto GetTupleValue(std::tuple<A...> _tuple) {
	return std::get<T>(_tuple);
}

template <typename T, typename O>
constexpr T CastTo(O o) noexcept {
	return static_cast<T>(o);
}

template <typename T, typename O>
constexpr T DynamicCastTo(O o) noexcept {
	return dynamic_cast<T>(o);
}

template <typename T, typename O>
constexpr T ReinterpretCastTo(O o) noexcept {
	return reinterpret_cast<T>(o);
}

constexpr uint64_t UINT64_MAXVALUE = 0xffffffffffffffffULL;

namespace Pictura::Types
{
	template <class T>
	String ToString(const T& t)
	{
		try
		{
			std::stringstream ss;
			ss << t;
			return ss.str();
		}
		catch (const std::exception&)
		{
			return "";
		}
	}

	template <typename T>
	uint32 GetObjectId(const T& obj)
	{
		uint32 id = reinterpret_cast<uint32>(obj);
		return id;
	}
	#pragma warning(default : 4311 4302)

	template <typename E>
	constexpr typename std::underlying_type<E>::type ToUnderlying(E e) noexcept {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}

	template <typename T, typename... Args>
	UniquePtr<T> MakeUnique(Args ...args)
	{
		return std::make_unique<T>(args...);
	}

	template <typename T, typename... Args>
	SharedPtr<T> MakeShared(Args ...args)
	{
		return std::make_shared<T>(args...);
	}

	template <typename... A>
	Tuple<A...> MakeTuple(A ...types)
	{
		return std::make_tuple(types...);
	}

	template <class T>
	void Move(const T& a)
	{
		std::move(a);
	}

	namespace Numbers
	{
		template<class T>
		bool IsBetween(T value, T min, T max) {
			return (value >= min) && (value <= max);
		}
	}

	namespace Vectors
	{
		template <typename T>
		void RemoveElement(Vector<T>& vector, T value)
		{
			typename std::vector<T>::iterator pos = std::find(vector.begin(), vector.end(), value);
			if (pos != vector.end()) {
				vector.erase(pos);
			}
			else {
				//Debug::Log::Warning("Tried to remove a not found element of a Vector !");
			}
		}
	}

	namespace Lists
	{
		template <typename T>
		void RemoveElement(List<T>& list, T value)
		{
			list.remove(value);
		}
	}
}
