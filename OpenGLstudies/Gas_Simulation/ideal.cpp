#include "ideal.h"

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
        float r_code = 0.0f; // R
        float g_code = 0.0f; // G
        float b_code = 1.0f; // B

        float x = 0.0f; // 유닛 x좌표
        float y = 0.0f; // 유닛 y좌표
    };
    units unit[10];

    // const 필드 조건
    float x_field = 0.0000f;
    float y_field = 0.0000f;

    float b_length = 0.9f; // 바운더리 길이
    // =============================================================

    // =============================================================
    // 형태

    // 폴리곤
    void polygon_unit(int unit_num)
    {
        // 극좌표 랜덤값 생성
        int rand_r = dis(gen);
        int rand_th = theta(gen);

        // 좌표 변환
        float dgen = 250.0f;
        float rand_dx = (float)rand_r * (float)cos(rand_th * M_PI / 180) / dgen;
        float rand_dy = (float)rand_r * (float)sin(rand_th * M_PI / 180) / dgen;

        // 원래 위치에서 변화량만큼 이동 + field 효과
        float dx = x_field + rand_dx; // x 변화량
        float dy = y_field + rand_dy; // y 변화량
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;
        // 바운더리에서 반사
        float pxbf = unit[unit_num].x - b_length; // +x 초과량
        float nxbf = unit[unit_num].x + b_length; // -x 초과량
        float pybf = unit[unit_num].y - b_length; // +y 초과량
        float nybf = unit[unit_num].y + b_length; // -y 초과량
        if (pxbf > 0) unit[unit_num].x -= pxbf * 2.0f - x_field * (pxbf / dx); // +x 반사
        else if (nxbf < 0) unit[unit_num].x -= nxbf * 2.0f - x_field * (nxbf / dx); // -x 반사
        if (pybf > 0) unit[unit_num].y -= pybf * 2.0f - y_field * (pybf / dy); // +y 반사
        else if (nybf < 0) unit[unit_num].y -= nybf * 2.0f - y_field * (nybf / dy); // -y 반사

        // polygon 생성
        glBegin(GL_POLYGON);
        float rx = 0.0f;
        float ry = 0.0f;
        for (int i = 0; i < 360; i++)
        {
            rx = unit[unit_num].x + unit[unit_num].rad * (float)cos(i * M_PI / 180);
            ry = unit[unit_num].y + unit[unit_num].rad * (float)sin(i * M_PI / 180);
            glVertex2f(rx, ry);
        }

        glEnd();
    }

    // 점
    void point_unit(int unit_num)
    {
        // 극좌표 랜덤값 생성
        int rand_r = dis(gen);
        int rand_th = theta(gen);

        // 좌표 변환
        float rand_dx = (float)rand_r * (float)cos(rand_th * M_PI / 180) / 500.0f;
        float rand_dy = (float)rand_r * (float)sin(rand_th * M_PI / 180) / 500.0f;

        // 원래 위치에서 변화량만큼 이동 + field 효과
        float dx = x_field + rand_dx; // x 변화량
        float dy = y_field + rand_dy; // y 변화량
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;
        // 바운더리에서 반사
        float pxbf = unit[unit_num].x - b_length; // +x 초과량
        float nxbf = unit[unit_num].x + b_length; // -x 초과량
        float pybf = unit[unit_num].y - b_length; // +y 초과량
        float nybf = unit[unit_num].y + b_length; // -y 초과량
        if (pxbf > 0) unit[unit_num].x -= pxbf * 2.0f - x_field * (pxbf / dx); // +x 반사
        else if (nxbf < 0) unit[unit_num].x -= nxbf * 2.0f - x_field * (nxbf / dx); // -x 반사
        if (pybf > 0) unit[unit_num].y -= pybf * 2.0f - y_field * (pybf / dy); // +y 반사
        else if (nybf < 0) unit[unit_num].y -= nybf * 2.0f - y_field * (nybf / dy); // -y 반사

        // polygon 생성
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

        glColor3f(unit[0].r_code, unit[0].g_code, unit[0].b_code);
        for (int i = 0; i < sizeof(unit) / sizeof(unit[0]); i++)
        {
            polygon_unit(i);
            //point_unit(i);
        }

        Cnd::square_boundary(b_length); // 바운더리

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