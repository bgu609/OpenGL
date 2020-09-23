#include "Particle.h"

namespace Ptc
{
    void display()
    {
        srand((unsigned int)time(NULL));
        int rand_x = rand();
        int rand_x_sign = rand();
        int rand_y = rand();
        int rand_y_sign = rand();

        double rad = 0.05;
        double angle = 0.0;

        double x = (double)(rand_x % 10) / 10;
        double y = (double)(rand_y % 10) / 10;
        if (rand_x_sign % 2) x = x * -1.0;
        if (rand_y_sign % 2) y = y * -1.0;

        double rx = 0.0;
        double ry = 0.0;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 클리어 컬러
        glClear(GL_COLOR_BUFFER_BIT); // 컬러 버퍼로 클리어 (클리어 컬러 함수를 쓰면 컬러 버퍼에 색상 정의되고 그거로 화면을 지우는듯, 그림판 프로그램 생각하면 될듯)

        glMatrixMode(GL_MODELVIEW); //이후 계산은 modelview matrix에 영향을 주게됨
        glLoadIdentity(); //modleview matrix를 초기화


        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++)
        {
            angle = i * M_PI / 180;
            rx = x + rad * cos(angle);
            ry = y + rad * sin(angle);
            glVertex2f(rx, ry);
        }
        glEnd();

        glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력
    }

	void Particles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Particles");

		glutDisplayFunc(display);
	}
}