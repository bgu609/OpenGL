#include "ideal.h"

using namespace std;
using namespace Cnd;
using namespace Ctrls;

namespace Ideal
{
    // =============================================================
    // 환경
    std::random_device rd; // 시드값을 얻기 위한 랜덤 디바이스 생성
    std::mt19937 gen(rd()); // 난수 생성 엔진 초기화
    std::uniform_int_distribution<int> dis(0, 19); // 랜덤 변화 범위
    std::uniform_int_distribution<int> theta(0, 359); // 랜덤 angle 범위

    // 유닛
    struct units
    {
        float rad = 0.05f; // 유닛 반지름

        float x = 0.0f; // 유닛 x좌표
        float y = 0.0f; // 유닛 y좌표

        float mass = 1.0f; // 유닛 질량
        float vel = 0.0f; // 유닛 속력
        float acc = 0.0f; // 유닛 가속
    };
    units unit[50];

    // 필드 조건
    float r_field = 0.0005f;
    int th_field = 30;
    float x_field = r_field * (float)cos(th_field * M_PI / 180);
    float y_field = r_field * (float)sin(th_field * M_PI / 180);

    float b_length = 0.7f; // 바운더리 길이
    float w_length = 0.01f;
    float h_length = 0.01f;

    // 바운더리 정의
    float b_x = w_length / 2.0f;
    float b_y = h_length / 2.0f;
    // =============================================================

    // =============================================================
    // physics

    // 다음 위치 계산
    void unit_position(int unit_num)
    {
        // 극좌표 랜덤값 생성
        int rand_r = dis(gen);
        int rand_th = theta(gen);
        unit[unit_num].vel = (float)rand_r / 0.010f;

        // 좌표 변환
        float dgen = unit[unit_num].mass * 250.0f; // distance generate, 질량 효과 느낌나게 임의로 설정해봄
        float rand_dx = (float)rand_r * (float)cos(rand_th * M_PI / 180) / dgen;
        float rand_dy = (float)rand_r * (float)sin(rand_th * M_PI / 180) / dgen;

        // 원래 위치에서 변화량만큼 이동 + field 효과
        float dx = x_field + rand_dx; // x 변화량
        float dy = y_field + rand_dy; // y 변화량
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;

        // 바운더리에서 반사
        while (true) // 반사 후 바운더리 내부에 위치할 때까지 반복
        {
            if ((fabs(unit[unit_num].x) <= b_x) && (fabs(unit[unit_num].y) <= b_y))
            {
                break;
            }
            else
            {
                if (unit[unit_num].x > b_x) // +x 초과
                {
                    unit[unit_num].x -= rand_dx * 2.0f; // +x 반사

                    if (unit[unit_num].x > b_x) // 반사 불가 상황
                    {
                        unit[unit_num].x = b_x;
                    }
                    else if (unit[unit_num].x < -b_x) // 과다 반사 상황
                    {
                        unit[unit_num].x = -b_x;
                    }
                }
                else if (unit[unit_num].x < -b_x) // -x 초과
                {
                    unit[unit_num].x += rand_dx * 2.0f; // -x 반사

                    if (fabs(unit[unit_num].x) > b_x) // 반사 불가 상황
                    {
                        unit[unit_num].x = -b_x;
                    }
                    else if (unit[unit_num].x > b_x) // 과다 반사 상황
                    {
                        unit[unit_num].x = b_x;
                    }
                }

                if (unit[unit_num].y > b_y) // +y 초과
                {
                    unit[unit_num].y -= rand_dy * 2.0f; // +y 반사

                    if (unit[unit_num].y > b_y) // 반사 불가 상황
                    {
                        unit[unit_num].y = b_y;
                    }
                    else if (unit[unit_num].y < -b_y) // 과다 반사 상황
                    {
                        unit[unit_num].y = -b_y;
                    }
                }
                else if (unit[unit_num].y < -b_y) // -y 초과
                {
                    unit[unit_num].y += rand_dy * 2.0f; // -y 반사

                    if (unit[unit_num].y < -b_y) // 반사 불가 상황
                    {
                        unit[unit_num].y = -b_y;
                    }
                    else if (unit[unit_num].y > b_y) // 과다 반사 상황
                    {
                        unit[unit_num].y = b_y;
                    }
                }
            }
        }
    }
    // =============================================================

    // =============================================================
    // 형태

    // 폴리곤
    void polygon_unit(int unit_num)
    {
        unit_position(unit_num);

        // polygon 생성
        glBegin(GL_POLYGON);
        float rx = 0.0f;
        float ry = 0.0f;
        for (int i = 0; i < 360; i++)
        {
            rx = unit[unit_num].x + unit[unit_num].rad * (float)(cos(i * M_PI / 180) / 4); // 4 나눈 건 그래픽 표현 보정치
            ry = unit[unit_num].y + unit[unit_num].rad * (float)(sin(i * M_PI / 180) / 4); // 4 나눈 건 그래픽 표현 보정치
            glVertex2f(rx, ry);
        }

        glEnd();
    }

    // 점
    void point_unit(int unit_num)
    {
        unit_position(unit_num);

        // point 생성
        glPointSize(1.0);
        glBegin(GL_POINTS);
        float rx = 0.0f;
        float ry = 0.0f;

        rx = unit[unit_num].x;
        ry = unit[unit_num].y;
        glVertex2f(rx, ry);

        glEnd();
    }
    // =============================================================

    // =============================================================
    // 화면 디스플레이
    void display()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 클리어 컬러
        glClear(GL_COLOR_BUFFER_BIT); // 컬러 버퍼로 클리어 (클리어 컬러 함수를 쓰면 컬러 버퍼에 색상 정의되고 그거로 화면을 지우는듯, 그림판 프로그램 생각하면 될듯)

        int unit_nums = sizeof(unit) / sizeof(unit[0]);
        glColor3f(0.0f, 0.0f, 1.0f);
        for (int i = 0; i < unit_nums; i++)
        {
            if (i > unit_nums * 0.7)
            {
                glColor3f(1.0f, 0.0f, 0.0f);
                unit[i].rad = 0.1f;
                unit[i].mass = 4.0f;
            }

            polygon_unit(i);
            //point_unit(i);

            // cout << i << " : " << unit[i].x << " " << unit[i].y << endl; // 디버깅용
            // cout << x_field << " " << y_field << endl; // 디버깅용
        }

        //Cnd::square_boundary(b_length); // 바운더리
        Cnd::rect_boundary(w_length, h_length); // 바운더리

        //glFlush();
        glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력
    }

	void Particles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL Ideal Particles");

		glutDisplayFunc(display);
	}
    // =============================================================
}