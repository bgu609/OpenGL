#include "convex.h"

#define UNIT_NUM 10

using namespace std;

namespace Convex
{
	std::random_device rd; // 시드값을 얻기 위한 랜덤 디바이스 생성
	std::mt19937 gen(rd()); // 난수 생성 엔진 초기화
	std::uniform_int_distribution<int> dis(0, 50); // 랜덤 변화 범위
	std::uniform_int_distribution<int> theta(0, 359); // 랜덤 angle 범위

	int unit_num = UNIT_NUM;

	// 샘플 좌표
	float x_array[UNIT_NUM] = { -1.0f, -0.8f, -0.75f, -0.68f, -0.52f, -0.29f, 0.11f, 0.23f, 0.38f, 0.6f };
	float y_array[UNIT_NUM] = { 0.0f, 0.8f, -0.3f, 0.2f, 0.1f, -0.4f, 0.25f, 0.51f, -0.15f, 0.0f };
	bool convex_array_f[UNIT_NUM] = { true };
	bool convex_array_b[UNIT_NUM] = { true };

	// 벡터 회전방향 검사 ( 스택으로 검사해야 함, 0-1-2 검사때 1이 false 뜨면 1 버리고 0-2-3을 검사해야함 )
	void vector_rotate()
	{
		int start = 0;
		int judge = 1;
		int end = 2;

		while (end < UNIT_NUM)
		{
			float vx1 = x_array[judge] - x_array[start]; float vy1 = y_array[judge] - y_array[start];
			float vx2 = x_array[end] - x_array[judge]; float vy2 = y_array[end] - y_array[judge];

			float cross = vx1 * vy2 - vx2 * vy1;

			if (cross >= 0)
			{
				convex_array_f[judge] = true;
				start = judge;
				judge = end;
				end = end + 1;
			}
			else if (cross < 0)
			{
				convex_array_f[judge] = false;
				judge = end;
				end = end + 1;
			}
		}
	}

	// unit line
	void unit_line()
	{
		// 검사수행 표시
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < UNIT_NUM; i++)
		{
			glVertex2f(x_array[i], y_array[i]);
		}

		glEnd();

		// 선
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < UNIT_NUM; i++)
		{
			if (convex_array_f[i])
			{
				glVertex2f(x_array[i], y_array[i]);
			}
			else
			{

			}
		}

		glEnd();
	}

	// unit point
	void unit_point(float x, float y)
	{
		glColor3f(0.0f, 0.0f, 1.0f);

		// point 생성
		glPointSize(5.0);
		glBegin(GL_POINTS);

		// (x, y)에 그리기
		glVertex2f(x, y);

		glEnd();
	}

	// 점
	void random_point()
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		// point 생성
		glPointSize(5.0);
		glBegin(GL_POINTS);
		
		// 극좌표 랜덤값 생성
		int rand_r = dis(gen);
		int rand_th = theta(gen);

		// 좌표 변환
		float rand_x = (float)rand_r * (float)cos(rand_th * M_PI / 180) / 100.0f;
		float rand_y = (float)rand_r * (float)sin(rand_th * M_PI / 180) / 100.0f;

		// (x, y)에 그리기
		glVertex2f(rand_x, rand_y);

		glEnd();
	}

	void display()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < UNIT_NUM; i++)
		{
			unit_point(x_array[i], y_array[i]);
		}

		vector_rotate();

		unit_line();
		
		/*
		for (int i = 0; i < unit_num; i++)
		{
			random_point();
		}
		*/

		//glFlush();
		glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력

		//Sleep(1000);
	}

	void draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL Ideal Particles");

		glutDisplayFunc(display);
	}
}