#include "chess\maths\calc.h"

namespace Chess
{
	namespace Maths
	{
		float Calc::to_radians(float degrees)
		{
			return degrees * M_PI / 180.0f;
		}
	}
}
