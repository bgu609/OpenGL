#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include "gl/freeglut.h"

namespace controls
{
	void keyboard(unsigned char key, int x, int y); // 키보드 콜백 함수
	void special_key(int key, int x, int y); // 키보드 콜백 함수
	void mouse_button(int button, int state, int x, int y); // 마우스 버튼
	void mouse_drag(int x, int y); // 마우스 드래그
	void mouse_wheel(int button, int dir, int x, int y); // 마우스 휠
	void reshape2d(GLsizei width, GLsizei height); // reshape 콜백 함수 (2d)
	void reshape3d(GLsizei width, GLsizei height); // reshape 콜백 함수 (3d)
	void timer(int value); // 타이머 콜백 함수
}
