#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include "gl/freeglut.h"

namespace graphics
{
	class graphic
	{
	private:
		struct unit_info
		{
			float rad = 0.05f; // À¯´Ö ¹İÁö¸§
			float x = 0.0f; // À¯´Ö xÁÂÇ¥
			float y = 0.0f; // À¯´Ö yÁÂÇ¥
		};
	public:
		int unit_num;
		unit_info* units;

		graphic(int num); // Å¬·¡½º »ı¼ºÀÚ

		void draw();
	};
}
