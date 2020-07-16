#pragma once
#include "Core/CoreFramework.h"

namespace Pictura
{
	struct DateTime
	{
	public:
		DateTime();
		~DateTime();

		static DateTime GetCurrentDateTime();
		static String GetCurrentTimeFormat(String Format = "%T");

	public:
		int Second;
		int Minute;
		int Hour;
		int Day;
		String FullDay;
		int Month;
		String FullMonth;
		int Year;

	private:
		//Number of ticks per time unit
		const long TicksPerMillisecond = 10000;
		const long TicksPerSecond = TicksPerMillisecond * 1000;
		const long TicksPerMinute = TicksPerSecond * 60;
		const long TicksPerHour = TicksPerMinute * 60;
		const long TicksPerDay = TicksPerHour * 24;

		//Number of ms per time unit
		const int MillisPerSecond = 1000;
		const int MillisPerMinute = MillisPerSecond * 60;
		const int MillisPerHour = MillisPerMinute * 60;
		const int MillisPerDay = MillisPerHour * 24;

		// Number of days in a non-leap year
		const int DaysPerYear = 365;
	};
}