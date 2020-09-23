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

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ŭ���� �÷�
        glClear(GL_COLOR_BUFFER_BIT); // �÷� ���۷� Ŭ���� (Ŭ���� �÷� �Լ��� ���� �÷� ���ۿ� ���� ���ǵǰ� �װŷ� ȭ���� ����µ�, �׸��� ���α׷� �����ϸ� �ɵ�)

        glMatrixMode(GL_MODELVIEW); //���� ����� modelview matrix�� ������ �ְԵ�
        glLoadIdentity(); //modleview matrix�� �ʱ�ȭ


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

        glutSwapBuffers(); // �̱� ���۶�� ���ۿ� �ִ� ���� ȭ�鿡 ���
    }

	void Particles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Particles");

		glutDisplayFunc(display);
	}
}