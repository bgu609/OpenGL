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

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ŭ���� �÷�
        glClear(GL_COLOR_BUFFER_BIT); // �÷� ���۷� Ŭ���� (Ŭ���� �÷� �Լ��� ���� �÷� ���ۿ� ���� ���ǵǰ� �װŷ� ȭ���� ����µ�, �׸��� ���α׷� �����ϸ� �ɵ�)

        //glMatrixMode(GL_MODELVIEW); //���� ����� modelview matrix�� ������ �ְԵ�
        //glLoadIdentity(); //modleview matrix�� �ʱ�ȭ


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
        glutSwapBuffers(); // �̱� ���۶�� ���ۿ� �ִ� ���� ȭ�鿡 ���
    }

	void Particles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL Particles");

		glutDisplayFunc(display);
	}
}