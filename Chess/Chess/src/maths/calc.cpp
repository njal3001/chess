#include "chess\maths\calc.h"

namespace Game
{
	float Calc::to_radians(float degrees)
	{
		return (float)(degrees * M_PI / 180.0f);
	}

	int Calc::sgn(int x)
	{
		return (x < 0) ? -1 : 1;
	}
}

