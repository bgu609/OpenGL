#include "convex.h"

#define UNIT_NUM 10

using namespace std;

namespace Convex
{
	std::random_device rd; // �õ尪�� ��� ���� ���� ����̽� ����
	std::mt19937 gen(rd()); // ���� ���� ���� �ʱ�ȭ
	std::uniform_int_distribution<int> dis(0, 50); // ���� ��ȭ ����
	std::uniform_int_distribution<int> theta(0, 359); // ���� angle ����

	int unit_num = UNIT_NUM;

	// ���� ��ǥ
	float x_array[UNIT_NUM] = { -0.9f, -0.8f, -0.75f, -0.68f, -0.52f, -0.29f, 0.11f, 0.23f, 0.38f, 0.6f };
	float y_array[UNIT_NUM] = { 0.0f, 0.8f, -0.3f, 0.2f, 0.1f, -0.4f, 0.25f, 0.51f, -0.15f, 0.0f };
	bool convex_array_f[UNIT_NUM] = { true, true, true, true, true, true, true, true, true, true };
	bool convex_array_b[UNIT_NUM] = { true, true, true, true, true, true, true, true, true, true };

	// ���� ȸ������ �˻� ( �������� �˻��ؾ� ��, 0-1-2 �˻綧 1�� false �߸� 1 ������ 0-2-3�� �˻��ؾ��� )
	// 1�� ó�� true ���� 2�� false �Ǹ� �� �̻������� ��� ����
	void vector_rotate()
	{
		int start = 0;
		int judge = 1;
		int next = 2;
		int end = 3;

		while (end < UNIT_NUM)
		{
			float vx1 = x_array[judge] - x_array[start]; float vy1 = y_array[judge] - y_array[start];
			float vx2 = x_array[next] - x_array[judge]; float vy2 = y_array[next] - y_array[judge];
			float vx3 = x_array[end] - x_array[next]; float vy3 = y_array[end] - y_array[next];

			float cross12 = vx1 * vy2 - vx2 * vy1;
			float cross23 = vx2 * vy3 - vx3 * vy2;

			if (cross12 < 0)
			{
				convex_array_f[judge] = false;
				judge = next;
				next = end;
				end = end + 1;
			}
			else if (cross23 < 0)
			{
				convex_array_f[next] = false;
				next = end;
				end = end + 1;
			}
			else
			{
				convex_array_f[judge] = true;
				start = judge;
				judge = next;
				next = end;
				end = end + 1;
			}
		}

		start = UNIT_NUM - 1;
		judge = UNIT_NUM - 2;
		next = UNIT_NUM - 3;
		end = UNIT_NUM - 4;

		while (end >= 0)
		{
			float vx1 = x_array[judge] - x_array[start]; float vy1 = y_array[judge] - y_array[start];
			float vx2 = x_array[next] - x_array[judge]; float vy2 = y_array[next] - y_array[judge];
			float vx3 = x_array[end] - x_array[next]; float vy3 = y_array[end] - y_array[next];

			float cross12 = vx1 * vy2 - vx2 * vy1;
			float cross23 = vx2 * vy3 - vx3 * vy2;

			if (cross12 < 0)
			{
				convex_array_b[judge] = false;
				judge = next;
				next = end;
				end = end - 1;
			}
			else if (cross23 < 0)
			{
				convex_array_b[next] = false;
				next = end;
				end = end - 1;
			}
			else
			{
				convex_array_b[judge] = true;
				start = judge;
				judge = next;
				next = end;
				end = end - 1;
			}
		}
	}

	// unit line
	void unit_line()
	{
		// �˻���� ǥ��
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i < UNIT_NUM; i++)
		{
			glVertex2f(x_array[i], y_array[i]);
		}

		glEnd();

		// ��
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < UNIT_NUM; i++)
		{
			if (convex_array_f[i])
			{
				
				glVertex2f(x_array[i], y_array[i]);
			}
		}
		glEnd();

		// ��
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = UNIT_NUM - 1; i >= 0; i--)
		{
			if (convex_array_b[i])
			{

				glVertex2f(x_array[i], y_array[i]);
			}
		}
		glEnd();
	}

	// unit point
	void unit_point(float x, float y)
	{
		glColor3f(0.0f, 0.0f, 0.0f);

		// point ����
		glPointSize(5.0);
		glBegin(GL_POINTS);

		// (x, y)�� �׸���
		glVertex2f(x, y);

		glEnd();
	}

	// ��
	void random_point()
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		// point ����
		glPointSize(5.0);
		glBegin(GL_POINTS);
		
		// ����ǥ ������ ����
		int rand_r = dis(gen);
		int rand_th = theta(gen);

		// ��ǥ ��ȯ
		float rand_x = (float)rand_r * (float)cos(rand_th * M_PI / 180) / 100.0f;
		float rand_y = (float)rand_r * (float)sin(rand_th * M_PI / 180) / 100.0f;

		// (x, y)�� �׸���
		glVertex2f(rand_x, rand_y);

		glEnd();
	}

	void display()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ŭ���� �÷�
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
		glutSwapBuffers(); // �̱� ���۶�� ���ۿ� �ִ� ���� ȭ�鿡 ���

		//Sleep(1000);
	}

	void draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL Monotone Chain");

		glutDisplayFunc(display);
	}
}