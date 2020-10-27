#pragma once

#include "gl/freeglut.h"
#include <iostream>

namespace Ctrls
{
	void keyboard(unsigned char key, int x, int y); // Ű���� �ݹ� �Լ�
	void special(int key, int x, int y); // Ű���� �ݹ� �Լ�
	void reshape2d(GLsizei width, GLsizei height); // reshape �ݹ� �Լ� (2d)
	void reshape3d(GLsizei width, GLsizei height); // reshape �ݹ� �Լ� (3d)
	void timer(int value); // Ÿ�̸� �ݹ� �Լ�
}