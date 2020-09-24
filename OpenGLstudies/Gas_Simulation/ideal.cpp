#include "ideal.h"

using namespace Cnd;
using namespace Ctrls;

namespace Ideal
{
    // =============================================================
    // ȯ��
    std::random_device rd; // �õ尪�� ��� ���� ���� ����̽� ����
    std::mt19937 gen(rd()); // ���� ���� ���� �ʱ�ȭ
    std::uniform_int_distribution<int> dis(0, 19); // ���� ��ȭ ����
    std::uniform_int_distribution<int> theta(0, 359); // ���� angle ����

    // ����
    struct units
    {
        float rad = 0.05f; // ���� ������
        float r_code = 0.0f; // R
        float g_code = 0.0f; // G
        float b_code = 1.0f; // B

        float x = 0.0f; // ���� x��ǥ
        float y = 0.0f; // ���� y��ǥ
    };
    units unit[10];

    // const �ʵ� ����
    float x_field = 0.0000f;
    float y_field = 0.0000f;

    float b_length = 0.9f; // �ٿ���� ����
    // =============================================================

    // =============================================================
    // ����

    // ������
    void polygon_unit(int unit_num)
    {
        // ����ǥ ������ ����
        int rand_r = dis(gen);
        int rand_th = theta(gen);

        // ��ǥ ��ȯ
        float dgen = 250.0f;
        float rand_dx = (float)rand_r * (float)cos(rand_th * M_PI / 180) / dgen;
        float rand_dy = (float)rand_r * (float)sin(rand_th * M_PI / 180) / dgen;

        // ���� ��ġ���� ��ȭ����ŭ �̵� + field ȿ��
        float dx = x_field + rand_dx; // x ��ȭ��
        float dy = y_field + rand_dy; // y ��ȭ��
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;
        // �ٿ�������� �ݻ�
        float pxbf = unit[unit_num].x - b_length; // +x �ʰ���
        float nxbf = unit[unit_num].x + b_length; // -x �ʰ���
        float pybf = unit[unit_num].y - b_length; // +y �ʰ���
        float nybf = unit[unit_num].y + b_length; // -y �ʰ���
        if (pxbf > 0) unit[unit_num].x -= pxbf * 2.0f - x_field * (pxbf / dx); // +x �ݻ�
        else if (nxbf < 0) unit[unit_num].x -= nxbf * 2.0f - x_field * (nxbf / dx); // -x �ݻ�
        if (pybf > 0) unit[unit_num].y -= pybf * 2.0f - y_field * (pybf / dy); // +y �ݻ�
        else if (nybf < 0) unit[unit_num].y -= nybf * 2.0f - y_field * (nybf / dy); // -y �ݻ�

        // polygon ����
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

    // ��
    void point_unit(int unit_num)
    {
        // ����ǥ ������ ����
        int rand_r = dis(gen);
        int rand_th = theta(gen);

        // ��ǥ ��ȯ
        float rand_dx = (float)rand_r * (float)cos(rand_th * M_PI / 180) / 500.0f;
        float rand_dy = (float)rand_r * (float)sin(rand_th * M_PI / 180) / 500.0f;

        // ���� ��ġ���� ��ȭ����ŭ �̵� + field ȿ��
        float dx = x_field + rand_dx; // x ��ȭ��
        float dy = y_field + rand_dy; // y ��ȭ��
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;
        // �ٿ�������� �ݻ�
        float pxbf = unit[unit_num].x - b_length; // +x �ʰ���
        float nxbf = unit[unit_num].x + b_length; // -x �ʰ���
        float pybf = unit[unit_num].y - b_length; // +y �ʰ���
        float nybf = unit[unit_num].y + b_length; // -y �ʰ���
        if (pxbf > 0) unit[unit_num].x -= pxbf * 2.0f - x_field * (pxbf / dx); // +x �ݻ�
        else if (nxbf < 0) unit[unit_num].x -= nxbf * 2.0f - x_field * (nxbf / dx); // -x �ݻ�
        if (pybf > 0) unit[unit_num].y -= pybf * 2.0f - y_field * (pybf / dy); // +y �ݻ�
        else if (nybf < 0) unit[unit_num].y -= nybf * 2.0f - y_field * (nybf / dy); // -y �ݻ�

        // polygon ����
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
    // ȭ�� ���÷���
    void display()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Ŭ���� �÷�
        glClear(GL_COLOR_BUFFER_BIT); // �÷� ���۷� Ŭ���� (Ŭ���� �÷� �Լ��� ���� �÷� ���ۿ� ���� ���ǵǰ� �װŷ� ȭ���� ����µ�, �׸��� ���α׷� �����ϸ� �ɵ�)

        glColor3f(unit[0].r_code, unit[0].g_code, unit[0].b_code);
        for (int i = 0; i < sizeof(unit) / sizeof(unit[0]); i++)
        {
            polygon_unit(i);
            //point_unit(i);
        }

        Cnd::square_boundary(b_length); // �ٿ����

        //glFlush();
        glutSwapBuffers(); // �̱� ���۶�� ���ۿ� �ִ� ���� ȭ�鿡 ���
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