#include "Particle.h"

namespace Ptc
{
    std::random_device rd; // �õ尪�� ��� ���� ���� ����̽� ����
    std::mt19937 gen(rd()); // ���� ���� ���� �ʱ�ȭ
    std::uniform_int_distribution<int> dis(0, 9); // ���� ��ȭ ����
    std::uniform_int_distribution<int> num_sign(0, 1); // ��ȣ ����

    struct units
    {
        float rad = 0.03f; // ���� ������
        float x = 0.0f; // ���� x��ǥ
        float y = 0.0f; // ���� y��ǥ
    };
    units unit[100];

    // const �ʵ� ����
    float x_field = 0.0000f;
    float y_field = -0.0003f;

    void polygon_unit(int unit_num)
    {
        // ��ǥ ������ ����
        int rand_x = dis(gen);
        int rand_y = dis(gen);
        // ��ȣ ������ ����
        int rand_x_sign = num_sign(gen);
        int rand_y_sign = num_sign(gen);

        // ���� ��ȭ��
        float dx = (float)(rand_x) / 500.0f;
        float dy = (float)(rand_y) / 500.0f;
        // ���� ��ȣ
        if (rand_x_sign) dx = dx * -1.0f;
        if (rand_y_sign) dy = dy * -1.0f;

        // ���� ��ġ���� ��ȭ����ŭ �̵�
        unit[unit_num].x += x_field + dx;
        unit[unit_num].y += y_field + dy;
        // �ٿ�������� �ݻ�
        if ((unit[unit_num].x > 1.0) || (unit[unit_num].x < -1.0)) unit[unit_num].x -= dx * 2.0f;
        if ((unit[unit_num].y > 1.0) || (unit[unit_num].y < -1.0)) unit[unit_num].y -= dy * 2.0f;

        // polygon ����
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
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Ŭ���� �÷�
        glClear(GL_COLOR_BUFFER_BIT); // �÷� ���۷� Ŭ���� (Ŭ���� �÷� �Լ��� ���� �÷� ���ۿ� ���� ���ǵǰ� �װŷ� ȭ���� ����µ�, �׸��� ���α׷� �����ϸ� �ɵ�)

        for (int i = 0; i < sizeof(unit)/sizeof(unit[0]); i++)
        {
            polygon_unit(i);
        }

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