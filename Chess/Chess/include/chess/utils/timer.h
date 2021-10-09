#pragma once
#include <ctime>
namespace Game
{
	class Timer
	{
	private:
		clock_t m_start;

	public:
		Timer();
		void reset();
		float elapsed();
	};
}
