#pragma once
#include <Windows.h>

namespace Chess
{
	namespace Utils
	{
		class Timer
		{
		private:
			LARGE_INTEGER m_start;
			double m_frequency;

		public:
			Timer();
			void reset();
			float elapsed();
		};

	}
}
