#include "Particle.h"

namespace Ptc
{
    clock_t rand_clock = clock();

    float x = 0.0f;
    float y = 0.0f;

    void display()
    {
        srand(clock());
        int rand_x = rand();
        int rand_x_sign = rand();
        int rand_y = rand();
        int rand_y_sign = rand();

        float rad = 0.05f;
        float angle = 0.0f;

        float dx = (float)(rand_x % 10) / 1000.0f;
        float dy = (float)(rand_y % 10) / 1000.0f;

        if (rand_x_sign % 2) dx = dx * -1.0f;
        if (rand_y_sign % 2) dy = dy * -1.0f;

        x += dx;
        y += dy;

        if ((x > 1.0) || (x < -1.0)) x -= dx * 2.0f;
        if ((y > 1.0) || (y < -1.0)) y -= dy * 2.0f;

        float rx = 0.0f;
        float ry = 0.0f;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
        glClear(GL_COLOR_BUFFER_BIT); // 컬러 버퍼로 클리어 (클리어 컬러 함수를 쓰면 컬러 버퍼에 색상 정의되고 그거로 화면을 지우는듯, 그림판 프로그램 생각하면 될듯)

        //glMatrixMode(GL_MODELVIEW); //이후 계산은 modelview matrix에 영향을 주게됨
        //glLoadIdentity(); //modleview matrix를 초기화


        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++)
        {
            angle = (float)(i * M_PI / 180);
            rx = x + rad * (float)cos(angle);
            ry = y + rad * (float)sin(angle);
            glVertex2f(rx, ry);
        }
        glEnd();

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