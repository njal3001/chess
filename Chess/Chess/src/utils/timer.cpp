#include "chess/utils/timer.h"

namespace Chess
{
	namespace Utils
	{
		Timer::Timer()
		{
			reset();
		}

		void Timer::reset()
		{
			m_start = clock();
		}

		float Timer::elapsed()
		{
			clock_t ticks = clock() - m_start;
			return (ticks / (float)CLOCKS_PER_SEC) * 1000;
		}
	}
}
