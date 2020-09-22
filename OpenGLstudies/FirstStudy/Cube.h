#pragma once

#include "gl/freeglut.h"

namespace Cb
{
	class Cubes
	{
	public:
		void draw();
	};

	void special(int key, int x, int y);
	void keyboard(unsigned char key, int x, int y);
}
