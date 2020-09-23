#pragma once

#include "gl/freeglut.h"
#include <iostream>

void keyboard(unsigned char key, int x, int y);
void reshape2d(GLsizei width, GLsizei height);
void reshape3d(GLsizei width, GLsizei height);
void timer(int value);