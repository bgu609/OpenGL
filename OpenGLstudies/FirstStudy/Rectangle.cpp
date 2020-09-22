#include "Rectangle.h"

using namespace std;

namespace Rect
{
	void display()
	{
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f); // red color
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();

		//glutSwapBuffers();
		glFlush();
	}

	void Rectangles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Rectanlge Example");

		glutDisplayFunc(display);
	}
}
