#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include "gl/freeglut.h"

namespace controls
{
	void keyboard(unsigned char key, int x, int y); // Ű���� �ݹ� �Լ�
	void special_key(int key, int x, int y); // Ű���� �ݹ� �Լ�
	void mouse_button(int button, int state, int x, int y); // ���콺 ��ư
	void mouse_drag(int x, int y); // ���콺 �巡��
	void mouse_wheel(int button, int dir, int x, int y); // ���콺 ��
	void reshape2d(GLsizei width, GLsizei height); // reshape �ݹ� �Լ� (2d)
	void reshape3d(GLsizei width, GLsizei height); // reshape �ݹ� �Լ� (3d)
	void timer(int value); // Ÿ�̸� �ݹ� �Լ�
}
