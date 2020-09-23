#include "Particle.h"

namespace Ptc
{
    std::random_device rd; // 시드값을 얻기 위한 랜덤 디바이스 생성
    std::mt19937 gen(rd()); // 난수 생성 엔진 초기화
    std::uniform_int_distribution<int> dis(0, 9);
    std::uniform_int_distribution<int> num_sign(0, 1);

    struct units
    {
        float rad = 0.03f;
        float x = 0.0f;
        float y = 0.0f;
    };
    units unit[10];

    void polygon_unit(int unit_num)
    {
        // 좌표 랜덤값 생성
        int rand_x = dis(gen);
        int rand_y = dis(gen);
        // 부호 랜덤값 생성
        int rand_x_sign = num_sign(gen);
        int rand_y_sign = num_sign(gen);

        // 랜덤 변화량
        float dx = (float)(rand_x) / 500.0f;
        float dy = (float)(rand_y) / 500.0f;
        // 랜덤 부호
        if (rand_x_sign) dx = dx * -1.0f;
        if (rand_y_sign) dy = dy * -1.0f;

        // 원래 위치에서 변화량만큼 이동
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;
        // 바운더리에서 반사
        if ((unit[unit_num].x > 1.0) || (unit[unit_num].x < -1.0)) unit[unit_num].x -= dx * 2.0f;
        if ((unit[unit_num].y > 1.0) || (unit[unit_num].y < -1.0)) unit[unit_num].y -= dy * 2.0f;

        // polygon 생성
        glColor3f(0.0f, 0.0f, 1.0f);
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

    void display()
    {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
        glClear(GL_COLOR_BUFFER_BIT); // 컬러 버퍼로 클리어 (클리어 컬러 함수를 쓰면 컬러 버퍼에 색상 정의되고 그거로 화면을 지우는듯, 그림판 프로그램 생각하면 될듯)

        for (int i = 0; i < sizeof(unit)/sizeof(unit[0]); i++)
        {
            polygon_unit(i);
        }

        //glFlush();
        glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력
    }

	void Particles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL Particles");

		glutDisplayFunc(display);
	}
}