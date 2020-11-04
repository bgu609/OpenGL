#include "convex.h"

#define UNIT_NUM 50
#define RANDOM_DIS 100
#define CHECK_NUM 2

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

	// 샘플 좌표 50
	float x_array[UNIT_NUM] = {
				0.28941f, 0.439397f, 0.515231f, -0.608676f, -0.719035f, -0.27297f, 0.39598f, -0.348569f, 0.338582f, -0.402379f,
				-0.356486f, -0.913199f, 0.00906308f, 0.76587f, 0.907783f, -0.0789068f, 0.106984f, 0.758958f, 0.315f, -0.170193f,
				-0.238396f, -0.610595f, 0.0526269f, 0.677162f, 0.26f, -0.153209f, -0.149909f, 0.325937f, -0.35105f, -0.620496f,
				-0.00866025f, -0.391086f, -0.608589f, 0.0146541f, 0.13906f, 0.0138919f, 0.423205f, -0.761151f, -0.319454f, -0.692108f,
				0.0644526f, -0.845723f, -0.529769f, -0.0398478f, 0.180611f, -0.385725f, -0.812215f, -0.0171034f, 0.679586f, 0.592006f
	};
	float y_array[UNIT_NUM] = {
				0.111094f, -0.0230278f, -0.572222f, 0.197771f, 0.350697f, -0.454299f, 0.39598f, 0.536749f, 0.172516f, -0.431499f,
				0.240453f, 0.261855f, -0.00422618f, 0.26371f, 0.063478f, -0.161783f, 0.132115f, 0.0397753f, -0.545596f, -0.0586023f,
				-0.126757f, -0.381542f, -0.172135f, -0.40688f, -0.450333f, 0.128558f, -0.00523492f, 0.0516234f, -0.327359f, 0.520658f,
				-0.005f, -0.246922f, 0.365677f, 0.279616f, 0.231435f, 0.0787846f, -0.582492f, -0.277036f, 0.240726f, 0.198459f,
				0.303226f, 0.307818f, -0.281683f, 0.00348623f, 0.187028f, -0.231767f, 0.31178f, 0.979851f, -0.0237317f, 0.215473f
	};

	bool monotone_chain[UNIT_NUM];
	xy xy_array[UNIT_NUM];

	void sample_set()
	{
		glBegin(GL_POINTS);
		for (int i = 0; i < UNIT_NUM; i++)
		{
			xy_array[i].x = x_array[i]; xy_array[i].y = y_array[i]; xy_array[i].chain = true;
			// (x, y)에 그리기
			glVertex2f(xy_array[i].x, xy_array[i].y);
			glEnd();
		}
	}

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
			// cout << rand_x << ", " << rand_y << endl; // 좌표 추출용
		}
		// cout << endl; // 좌표 추출용
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
				cout << "checked " << i << " : " << xy_array[i].x << ", " << xy_array[i].y << endl;
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
		
		//random_point();
		sample_set();

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