#include "convex.h"

#define UNIT_NUM 50
#define RANDOM_DIS 100

using namespace std;

namespace Convex
{
	std::random_device rd; // �õ尪�� ��� ���� ���� ����̽� ����
	std::mt19937 gen(rd()); // ���� ���� ���� �ʱ�ȭ
	std::uniform_int_distribution<int> dis(0, RANDOM_DIS); // ���� ��ȭ ����
	std::uniform_int_distribution<int> theta(0, 359); // ���� angle ����

	// ���� ����ü
	struct vector {
		float x;
		float y;
	};

	// ��ǥ ����ü
	struct xy {
		float x;
		float y;
		bool chain;
	};

	// ���� ��ǥ (UNIT_NUM 10 ����)
	// float x_array[UNIT_NUM] = { -0.9f, -0.8f, -0.75f, -0.68f, -0.52f, -0.29f, 0.11f, 0.23f, 0.38f, 0.6f };
	// float y_array[UNIT_NUM] = { 0.0f, 0.8f, -0.3f, 0.2f, 0.1f, -0.4f, 0.25f, 0.51f, -0.15f, 0.0f };

	bool monotone_chain[UNIT_NUM];
	xy xy_array[UNIT_NUM];

	// ���� ����
	void selection_sort()
	{
		int least;
		xy temp;

		for (int i = 0; i < UNIT_NUM - 1; i++)
		{
			least = i;

			for (int j = i + 1; j < UNIT_NUM; j++)
			{
				if (xy_array[j].x < xy_array[least].x)
				{
					least = j;
				}
				else if ((xy_array[j].x == xy_array[least].x) && (xy_array[j].y < xy_array[least].y))
				{
					least = j;
				}
			}

			if (i != least)
			{
				temp = xy_array[i];
				xy_array[i] = xy_array[least];
				xy_array[least] = temp;
			}
		}

		/* // sort debug ����
		for (int i = 0; i < UNIT_NUM; i++)
		{
			cout << "[ " << xy_array[i].x << ", " << xy_array[i].y << " ]" << endl;
		}
		cout << "=================================================" << endl;*/
	}

	// ���� ��ǥ ����
	void random_point()
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glPointSize(5.0);

		int rand_r, rand_th; float rand_x, rand_y;
		float scale = (float)RANDOM_DIS;

		for (int i = 0; i < UNIT_NUM; i++)
		{
			// point ����
			glBegin(GL_POINTS);
			// ����ǥ ������ ����
			rand_r = dis(gen); rand_th = theta(gen);
			// ��ǥ ��ȯ
			rand_x = (float)rand_r * (float)cos(rand_th * M_PI / 180) / scale;
			rand_y = (float)rand_r * (float)sin(rand_th * M_PI / 180) / scale;
			xy_array[i].x = rand_x;
			xy_array[i].y = rand_y;
			xy_array[i].chain = true;
			// (x, y)�� �׸���
			glVertex2f(rand_x, rand_y);
			glEnd();
		}
	}

	// ����� ü�� �ʱ�ȭ
	void monotone_set()
	{
		for (int i = 0; i < UNIT_NUM; i++)
		{
			monotone_chain[i] = true;
			xy_array[i].chain = true;
		}
	}

	// ���� ����
	vector vector_gen(int start_idx, int end_idx)
	{
		vector v;

		v.x = xy_array[end_idx].x - xy_array[start_idx].x;
		v.y = xy_array[end_idx].y - xy_array[start_idx].y;

		return v;
	}

	// Cross��
	float cross_product(int start, int middle, int end)
	{
		vector v1 = vector_gen(start, middle);
		vector v2 = vector_gen(middle, end);

		float cross = v1.x * v2.y - v1.y * v2.x;

		return cross;
	}

	// ����� �˻�
	// �˻� ���� 4 = ���� 3�� ( �� ������ ���е�? �� �����ִ°ǰ� )
	// ������ ��� ťó�� ��� ���̱� ��. ������ convex hull ���ԵǴ°Ŵ� ���ÿ��� ���� �������� �ȵǴµ�?
	void monotone(bool forward)
	{
		monotone_set();

		int stack[UNIT_NUM];
		int stack_count = 0;

		if (forward)
		{
			for (int i = 0; i < UNIT_NUM; i++)
			{
				if (xy_array[i].chain)
				{
					stack[stack_count] = i;
					stack_count++;
				}
			}

			int start = 0; int middle = 1; int end = 2;

			while (end < stack_count)
			{
				float cross = cross_product(start, middle, end);

				if (cross < 0)
				{
					monotone_chain[middle] = false;
					xy_array[middle].chain = false;
					middle = end;
					end++;
				}
				else
				{
					start = middle;
					middle = end;
					end++;
				} // �� ����� �⺻���� �ϰ� ���е��� ���̸� �� �˻縦 �� �ݺ��ϴ� ������� convex�� ������ ���� ��

				/*
				float cross1 = cross_product(start, first, second);
				float cross2 = cross_product(first, second, end);

				if (cross1 < 0)
				{
					monotone_chain[first] = false;
					first = second;
					second = end;
					end = end + 1;
				}
				else if (cross2 < 0)
				{
					monotone_chain[second] = false;
					second = end;
					end = end + 1;
				}
				else
				{
					start = first;
					first = second;
					second = end;
					end = end + 1;
				}
				*/
			}
		}
		else
		{
			int start = UNIT_NUM - 1; int first = UNIT_NUM - 2; int second = UNIT_NUM - 3; int end = UNIT_NUM - 4;

			while (end >= 0)
			{
				float cross1 = cross_product(start, first, second);
				float cross2 = cross_product(first, second, end);

				if (cross1 < 0)
				{
					monotone_chain[first] = false;
					xy_array[first].chain = false;
					first = second;
					second = end;
					end = end - 1;
				}
				else if (cross2 < 0)
				{
					monotone_chain[second] = false;
					second = end;
					end = end - 1;
				}
				else
				{
					start = first;
					first = second;
					second = end;
					end = end - 1;
				}
			}
		}
	}

	void check_line()
	{
		// ������ �˻� ���
		glColor3f(0.0f, 1.0f, 0.0f);
		glLineWidth(3.0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < UNIT_NUM; i++)
		{
			glVertex2f(xy_array[i].x, xy_array[i].y);
		}
		glEnd();
		glLineWidth(1.0);
	}

	// unit line
	void unit_line(float R, float G, float B)
	{
		// ��
		glColor3f(R, G, B);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < UNIT_NUM; i++)
		{
			if (monotone_chain[i])
			{
				glVertex2f(xy_array[i].x, xy_array[i].y);
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

	void display()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ŭ���� �÷�
		glClear(GL_COLOR_BUFFER_BIT);
		

		random_point();
		selection_sort();

		//vector_rotate();

		check_line();

		monotone(true);
		unit_line(1.0f, 0.0f, 0.0f);
		
		monotone(false);
		unit_line(0.0f, 0.0f, 1.0f);

		//glFlush();
		glutSwapBuffers(); // �̱� ���۶�� ���ۿ� �ִ� ���� ȭ�鿡 ���

		Sleep(3000);
	}

	void draw()
	{
		glutInitWindowSize(1000, 1000);
		glutInitWindowPosition(100, 50);
		glutCreateWindow("OpenGL Monotone Chain");

		glutDisplayFunc(display);
	}
}