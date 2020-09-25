#pragma once

#include "gl/freeglut.h"
#include <iostream>

namespace controls
{
	void keyboard(unsigned char key, int x, int y); // 키보드 콜백 함수
	void special(int key, int x, int y); // 키보드 콜백 함수
	void reshape2d(GLsizei width, GLsizei height); // reshape 콜백 함수 (2d)
	void reshape3d(GLsizei width, GLsizei height); // reshape 콜백 함수 (3d)
	void timer(int value); // 타이머 콜백 함수
}
