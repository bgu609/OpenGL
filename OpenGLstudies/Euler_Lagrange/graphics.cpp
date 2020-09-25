#include "graphics.h"

namespace graphics
{
	int scale_conver = 20; // 1.0f == 0~20

	float xs[] = { 0, 1, -2, 3, -4, -5, 6, -7, 8, 19 };
	float ys[] = { 0, 15, 8, 5, -10, 10, -5, 2, 10, 19 };

	void path()
	{
		glColor3f(0.0f, 0.0f, 1.0f);

		for (int i = 1; i < 10; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f((float)xs[i-1] / (float)scale_conver, (float)ys[i-1] / (float)scale_conver);
			glVertex2f((float)xs[i] / (float)scale_conver, (float)ys[i] / (float)scale_conver);
			glEnd();
		}
	}

	void nodes() // polygon 생성
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		float rx = 0.0f;
		float ry = 0.0f;

		for (int j = 0; j < 10; j++)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++)
			{
				rx = xs[j] / (float)scale_conver + 0.05f * (float)(cos(i * M_PI / 180) / 4); // 4 나눈 건 그래픽 표현 보정치
				ry = ys[j] / (float)scale_conver + 0.05f * (float)(sin(i * M_PI / 180) / 4); // 4 나눈 건 그래픽 표현 보정치
				glVertex2f(rx, ry);
			}
			glEnd();
		}
	}

	void scale_bar()
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-1.0f, 0);
		glVertex2f(1.0f, 0);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex2f(0, -1.0f);
		glVertex2f(0, 1.0f);
		glEnd();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(0.0f, 0.0f, 0.0f, 0.1f);

		for (int i = -scale_conver; i <= scale_conver; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(-1.0f, (float)i / (float)scale_conver);
			glVertex2f(1.0f, (float)i / (float)scale_conver);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex2f((float)i / (float)scale_conver, -1.0f);
			glVertex2f((float)i / (float)scale_conver, 1.0f);
			glEnd();
		}
		glDisable(GL_BLEND);
	}

	void display()
	{
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
        glClear(GL_COLOR_BUFFER_BIT); // 컬러 버퍼로 클리어 (클리어 컬러 함수를 쓰면 컬러 버퍼에 색상 정의되고 그거로 화면을 지우는듯, 그림판 프로그램 생각하면 될듯)
		
		scale_bar();

		path();

		nodes();
		
        glutSwapBuffers();
	}

	graphic::graphic(int num) // 클래스 생성자
	{
		unit_num = num;
		units = new unit_info[num];
	}

	void graphic::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL EL");

		glutDisplayFunc(display);
	}
}