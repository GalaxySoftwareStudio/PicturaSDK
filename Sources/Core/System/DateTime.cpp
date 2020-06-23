#include "PicturaPCH.h"
#include "DateTime.h"

#ifdef PLATFORM_WINDOWS
struct tm* gmtime_r(time_t* _clock, struct tm* _result)
{
	struct tm* p = gmtime(_clock);

	if (p)
		*(_result) = *p;

	return p;
}

struct tm* localtime_r(time_t* _clock, struct tm* _result)
{
	struct tm* p = localtime(_clock);

	if (p)
		*(_result) = *p;

	return p;
}
#endif // !HAVE_TIME_R

namespace Pictura
{
	DateTime::DateTime()
	{
		Second = 0;
		Minute = 0;
		Hour = 0;
		Day = 0;
		Month = 0;
		Year = 0;
	}

	DateTime::~DateTime()
	{

	}

	DateTime DateTime::GetCurrentDateTime()
	{
		DateTime r;
		r.Second = std::atoi(GetCurrentTimeFormat("%S").c_str());
		r.Minute = std::atoi(GetCurrentTimeFormat("%M").c_str());
		r.Hour = std::atoi(GetCurrentTimeFormat("%H").c_str());

		r.Day = std::atoi(GetCurrentTimeFormat("%d").c_str());
		r.FullDay = GetCurrentTimeFormat("%A");
		r.Month = std::atoi(GetCurrentTimeFormat("%m").c_str());
		r.FullMonth = GetCurrentTimeFormat("%B");
		r.Year = std::atoi(GetCurrentTimeFormat("%Y").c_str());

		return r;
	}

	String DateTime::GetCurrentTimeFormat(String format)
	{
		auto currentTime = std::chrono::system_clock::now();
		std::time_t time = std::chrono::system_clock::to_time_t(currentTime);

		std::time_t t = std::time(nullptr);
		std::tm tm;
		
		localtime_r(&t, &tm);

		try
		{
			std::stringstream buffer;
			buffer << std::put_time(&tm, format.c_str());

			return buffer.str();
		}
		catch (const std::exception&)
		{
			return "INVALID TIME";
		}
	}
}