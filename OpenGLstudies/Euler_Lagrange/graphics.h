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
			float rad = 0.05f; // ���� ������
			float x = 0.0f; // ���� x��ǥ
			float y = 0.0f; // ���� y��ǥ
		};
	public:
		int unit_num;
		unit_info* units;

		graphic(int num); // Ŭ���� ������

		void draw();
	};
}
