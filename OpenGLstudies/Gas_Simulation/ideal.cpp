#include "ideal.h"

using namespace std;
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

        float x = 0.0f; // ���� x��ǥ
        float y = 0.0f; // ���� y��ǥ

        float mass = 1.0f; // ���� ����
        float vel = 0.0f; // ���� �ӷ�
        float acc = 0.0f; // ���� ����
    };
    units unit[50];

    // const �ʵ� ����
    float x_field = 0.0000f;
    float y_field = 0.0000f;

    float b_length = 0.7f; // �ٿ���� ����
    float w_length = 1.0f;
    float h_length = 1.4f;
    // =============================================================

    // =============================================================
    // physics

    // ���� ��ġ ���
    void unit_position(int unit_num)
    {
        // �ٿ���� ����
        float b_x = w_length / 2.0f;
        float b_y = h_length / 2.0f;

        // ����ǥ ������ ����
        int rand_r = dis(gen);
        int rand_th = theta(gen);
        unit[unit_num].vel = (float)rand_r / 0.010f;

        // ��ǥ ��ȯ
        float dgen = unit[unit_num].mass * 250.0f; // distance generate, ���� ȿ�� �������� ���Ƿ� �����غ�
        float rand_dx = (float)rand_r * (float)cos(rand_th * M_PI / 180) / dgen;
        float rand_dy = (float)rand_r * (float)sin(rand_th * M_PI / 180) / dgen;

        // ���� ��ġ���� ��ȭ����ŭ �̵� + field ȿ��
        float dx = x_field + rand_dx; // x ��ȭ��
        float dy = y_field + rand_dy; // y ��ȭ��
        unit[unit_num].x += dx;
        unit[unit_num].y += dy;

        // �ٿ�������� �ݻ�
        float pxbf; float nxbf; float pybf; float nybf;
        while (true) // �ݻ� �� �ٿ���� ���ο� ��ġ�� ������ �ݺ�
        {
            pxbf = unit[unit_num].x - b_x; // +x �ʰ���
            nxbf = unit[unit_num].x + b_x; // -x �ʰ���
            pybf = unit[unit_num].y - b_y; // +y �ʰ���
            nybf = unit[unit_num].y + b_y; // -y �ʰ���
            if ((pxbf > 0) || (nxbf < 0) || (pybf > 0) || (nybf < 0))
            {
                if (pxbf > 0) unit[unit_num].x -= pxbf * 2.0f - x_field * (pxbf / dx); // +x �ݻ�
                else if (nxbf < 0) unit[unit_num].x -= nxbf * 2.0f - x_field * (nxbf / dx); // -x �ݻ�
                if (pybf > 0) unit[unit_num].y -= pybf * 2.0f - y_field * (pybf / dy); // +y �ݻ�
                else if (nybf < 0) unit[unit_num].y -= nybf * 2.0f - y_field * (nybf / dy); // -y �ݻ�
            }
            else
            {
                break;
            }
        }
    }
    // =============================================================

    // =============================================================
    // ����

    // ������
    void polygon_unit(int unit_num)
    {
        unit_position(unit_num);

        // polygon ����
        glBegin(GL_POLYGON);
        float rx = 0.0f;
        float ry = 0.0f;
        for (int i = 0; i < 360; i++)
        {
            rx = unit[unit_num].x + unit[unit_num].rad * (float)(cos(i * M_PI / 180) / 4); // 4 ���� �� �׷��� ǥ�� ����ġ
            ry = unit[unit_num].y + unit[unit_num].rad * (float)(sin(i * M_PI / 180) / 4); // 4 ���� �� �׷��� ǥ�� ����ġ
            glVertex2f(rx, ry);
        }

        glEnd();
    }

    // ��
    void point_unit(int unit_num)
    {
        unit_position(unit_num);

        // point ����
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

            // cout << i << " : " << unit[i].x << " " << unit[i].y << endl; // ������
        }

        //Cnd::square_boundary(b_length); // �ٿ����
        Cnd::rect_boundary(w_length, h_length); // �ٿ����

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