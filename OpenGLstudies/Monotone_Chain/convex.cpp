#include "convex.h"

#define UNIT_NUM 50
#define RANDOM_DIS 100

using namespace std;

namespace Convex
{
	std::random_device rd; // 시드값을 얻기 위한 랜덤 디바이스 생성
	std::mt19937 gen(rd()); // 난수 생성 엔진 초기화
	std::uniform_int_distribution<int> dis(0, RANDOM_DIS); // 랜덤 변화 범위
	std::uniform_int_distribution<int> theta(0, 359); // 랜덤 angle 범위

	// 벡터 구조체
	struct vector {
		float x;
		float y;
	};

	struct xy {
		float x;
		float y;
	};

	// 샘플 좌표 (UNIT_NUM 10 기준)
	// float x_array[UNIT_NUM] = { -0.9f, -0.8f, -0.75f, -0.68f, -0.52f, -0.29f, 0.11f, 0.23f, 0.38f, 0.6f };
	// float y_array[UNIT_NUM] = { 0.0f, 0.8f, -0.3f, 0.2f, 0.1f, -0.4f, 0.25f, 0.51f, -0.15f, 0.0f };
	// bool convex_array_f[UNIT_NUM] = { true, true, true, true, true, true, true, true, true, true };
	// bool convex_array_b[UNIT_NUM] = { true, true, true, true, true, true, true, true, true, true };

	bool monotone_chain[UNIT_NUM];
	xy xy_array[UNIT_NUM];

	// 선택 정렬
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

		/* // sort debug 전용
		for (int i = 0; i < UNIT_NUM; i++)
		{
			cout << "[ " << xy_array[i].x << ", " << xy_array[i].y << " ]" << endl;
		}
		cout << "=================================================" << endl;*/
	}

	// 랜덤 좌표 생성
	void random_point()
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glPointSize(5.0);

		int rand_r, rand_th; float rand_x, rand_y;
		float scale = (float)RANDOM_DIS;

		for (int i = 0; i < UNIT_NUM; i++)
		{
			// point 생성
			glBegin(GL_POINTS);
			// 극좌표 랜덤값 생성
			rand_r = dis(gen); rand_th = theta(gen);
			// 좌표 변환
			rand_x = (float)rand_r * (float)cos(rand_th * M_PI / 180) / scale;
			rand_y = (float)rand_r * (float)sin(rand_th * M_PI / 180) / scale;
			xy_array[i].x = rand_x;
			xy_array[i].y = rand_y;
			// (x, y)에 그리기
			glVertex2f(rand_x, rand_y);
			glEnd();
		}
	}

	// 모노톤 체인 초기화
	void monotone_set()
	{
		for (int i = 0; i < UNIT_NUM; i++)
		{
			monotone_chain[i] = true;
		}
	}

	// 벡터 생성
	vector vector_gen(int start_idx, int end_idx)
	{
		vector v;

		v.x = xy_array[end_idx].x - xy_array[start_idx].x;
		v.y = xy_array[end_idx].y - xy_array[start_idx].y;

		return v;
	}

	// Cross곱
	float cross_product(int start, int middle, int end)
	{
		vector v1 = vector_gen(start, middle);
		vector v2 = vector_gen(middle, end);

		float cross = v1.x * v2.y - v1.y * v2.x;

		return cross;
	}

	// 모노톤 검사
	// 검사 스택 3 = 벡터 3개 ( 이 갯수가 정밀도? 랑 연관있는건가 )
	// 지금은 사실 큐처럼 사용 중이긴 함. 원래는 convex hull 포함되는거는 스택에서 절대 내보내면 안되는듯?
	void monotone(bool forward)
	{
		monotone_set();

		if (forward)
		{
			int start = 0; int first = 1; int second = 2; int end = 3;

			while (end < UNIT_NUM)
			{
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
	/*
	// 벡터 회전방향 검사 ( 벡터 3개를 가지고 검사해야 함 )
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
	}*/

	void check_line()
	{
		// 순방향 검사 경로
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
		// 선
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

		/*// 선
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = UNIT_NUM - 1; i >= 0; i--)
		{
			if (convex_array_b[i])
			{
				glVertex2f(x_array[i], y_array[i]);
			}
		}
		glEnd();*/
	}

	// unit point
	void unit_point(float x, float y)
	{
		glColor3f(0.0f, 0.0f, 0.0f);

		// point 생성
		glPointSize(5.0);
		glBegin(GL_POINTS);
		// (x, y)에 그리기
		glVertex2f(x, y);

		glEnd();
	}

	void display()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
		glClear(GL_COLOR_BUFFER_BIT);
		/*
		for (int i = 0; i < UNIT_NUM; i++)
		{
			unit_point(x_array[i], y_array[i]);
		}*/

		random_point();
		selection_sort();

		//vector_rotate();

		check_line();

		monotone(true);
		unit_line(1.0f, 0.0f, 0.0f);
		
		monotone(false);
		unit_line(0.0f, 0.0f, 1.0f);

		//glFlush();
		glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력

		Sleep(3000);
	}

	void draw()
	{
		glutInitWindowSize(1000, 1000);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Monotone Chain");

		glutDisplayFunc(display);
	}
}