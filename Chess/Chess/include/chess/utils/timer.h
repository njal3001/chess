#pragma once
#include <ctime>
namespace Chess
{
	namespace Utils
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
}
