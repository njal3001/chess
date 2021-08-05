#include "chess/utils/timer.h"

namespace Chess
{
	namespace Utils
	{
		Timer::Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_frequency = frequency.QuadPart;
			QueryPerformanceCounter(&m_start);
		}

		void Timer::reset()
		{
			QueryPerformanceCounter(&m_start);
		}

		float Timer::elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
			return (float)(cycles * (1.0 / m_frequency));
		}
	}
}
