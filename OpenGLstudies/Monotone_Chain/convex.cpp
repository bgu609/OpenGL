#include "convex.h"

#define UNIT_NUM 50
#define RANDOM_DIS 100
#define CHECK_NUM 50

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

	// 좌표 구조체
	struct xy {
		float x;
		float y;
		bool chain;
	};

	// 샘플 좌표 (UNIT_NUM 10 기준)
	// float x_array[UNIT_NUM] = { -0.9f, -0.8f, -0.75f, -0.68f, -0.52f, -0.29f, 0.11f, 0.23f, 0.38f, 0.6f };
	// float y_array[UNIT_NUM] = { 0.0f, 0.8f, -0.3f, 0.2f, 0.1f, -0.4f, 0.25f, 0.51f, -0.15f, 0.0f };

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
			xy_array[i].chain = true;
			// (x, y)에 그리기
			glVertex2f(rand_x, rand_y);
			glEnd();
			cout << rand_x << ", " << rand_y << endl; // 좌표 추출용
		}
		cout << endl; // 좌표 추출용
	}

	// 모노톤 체인 초기화
	void monotone_set()
	{
		for (int i = 0; i < UNIT_NUM; i++)
		{
			monotone_chain[i] = true;
			xy_array[i].chain = true;
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

	// 모노톤 검사
	// 검사 스택 4 = 벡터 3개 ( 이 갯수가 정밀도? 랑 연관있는건가 )
	// 지금은 사실 큐처럼 사용 중이긴 함. 원래는 convex hull 포함되는거는 스택에서 절대 내보내면 안되는듯?
	void monotone()
	{
		int stack[UNIT_NUM];
		int stack_count;
		int start, middle, end;

		monotone_set();

		for (int i = 0; i < CHECK_NUM; i++)
		{
			stack_count = 0;
			for (int j = 0; j < UNIT_NUM; j++)
			{
				if (xy_array[j].chain)
				{
					stack[stack_count] = j;
					stack_count++;
				}
			}

			start = 0; middle = 1; end = 2;

			while (end < stack_count)
			{
				float cross = cross_product(stack[start], stack[middle], stack[end]);

				if (cross < 0)
				{
					monotone_chain[stack[middle]] = false;
					xy_array[stack[middle]].chain = false;
					stack[middle] = stack[end];
					stack[end] = stack[end++];
				}
				else
				{
					stack[start] = stack[middle];
					stack[middle] = stack[end];
					stack[end] = stack[end++];
				}
			}
		}

		unit_line(1.0f, 0.0f, 0.0f);

		monotone_set();

		for (int i = 0; i < CHECK_NUM; i++)
		{
			stack_count = 0;
			for (int j = 0; j < UNIT_NUM; j++)
			{
				if (xy_array[j].chain)
				{
					stack[stack_count] = j;
					stack_count++;
				}
			}

			start = stack_count - 1; middle = stack_count - 2; end = stack_count - 3;

			while (end >= 0)
			{
				float cross = cross_product(stack[start], stack[middle], stack[end]);

				if (cross < 0)
				{
					monotone_chain[stack[middle]] = false;
					xy_array[stack[middle]].chain = false;
					stack[middle] = stack[end];
					stack[end] = stack[end--];
				}
				else
				{
					stack[start] = stack[middle];
					stack[middle] = stack[end];
					stack[end] = stack[end--];
				}
			}
		}

		unit_line(0.0f, 0.0f, 1.0f);
	}

	void display()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
		glClear(GL_COLOR_BUFFER_BIT);
		

		random_point();

		selection_sort();

		check_line();

		monotone();

		//glFlush();
		glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력

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