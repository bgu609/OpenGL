#include "controls.h"

// ������
int win_width = 500;
int win_height = 500;

// ��ǥ
float viewX = 0.0f;
float viewY = 0.0f;
float viewZ = -6.0f;

// ȸ��
float pitch = 0.0f;
float yaw = 0.0f;
float roll = 0.0f;

int clicked = 0;
int mouse_x = 0;
int mouse_y = 0;
int x_move = 0;
int y_move = 0;

namespace controls
{
    void keyboard(unsigned char key, int x, int y)
    {
        if (key == 27)  // esc�� ����
        {
            exit(0);
        }
        else if (key == '+')
        {
            viewZ += 0.1f; // Ȯ��
        }
        else if (key == '-')
        {
            viewZ -= 0.1f; // ���
        }
        else if (key == 'q')
        {
            roll -= 1.0f; // z+ȸ�� (��ȸ��)
        }
        else if (key == 'e')
        {
            roll += 1.0f; // z-ȸ�� (��ȸ��)
        }
        else if (key == 'w')
        {
            viewY -= 0.01f; // ��
        }
        else if (key == 's')
        {
            viewY += 0.01f; // ��
        }
        else if (key == 'd')
        {
            viewX -= 0.01f; // ��
        }
        else if (key == 'a')
        {
            viewX += 0.01f; // ��
        }
    }

    void special_key(int key, int x, int y)
    {
        if (key == GLUT_KEY_DOWN)
        {
            pitch += 1.0f; // ȸ��
        }
        else if (key == GLUT_KEY_UP)
        {
            pitch -= 1.0f; // ȸ��
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            yaw += 1.0f; // ȸ��
        }
        else if (key == GLUT_KEY_LEFT)
        {
            yaw -= 1.0f; // ȸ��
        }
        else if (key == GLUT_KEY_HOME) // �� �ʱ�ȭ
        {
            viewX = 0.0f;
            viewY = 0.0f;
            viewZ = -6.0f;
            pitch = 0.0f;
            yaw = 0.0f;
            roll = 0.0f;
        }
    }

    void mouse_button(int button, int state, int x, int y)
    {
        if (clicked == 0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // Ŭ�� �� ���콺 ��ġ ����
        {
            clicked = 1;
            mouse_x = x;
            mouse_y = y;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            clicked = 0;
        }
        else if (clicked == 0 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            clicked = 2;
            mouse_x = x;
            mouse_y = y;
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        {
            clicked = 0;
        }
    }

    void mouse_drag(int x, int y)
    {
        if (clicked == 1)
        {
            // ���� ��ġ������ ���̸�ŭ �� �̵�
            viewX += (float)(x - mouse_x) / 100.0f;
            viewY -= (float)(y - mouse_y) / 100.0f;
            // ���� ��ġ ����
            mouse_x = x;
            mouse_y = y;
        }
        else if (clicked == 2)
        {
            double scalar_product = physics::scalar_product((double)(win_width / 2), (double)(win_height / 2), mouse_x, mouse_y, x, y); // ����
            double cross_product = physics::cross_product((double)(win_width / 2), (double)(win_height / 2), mouse_x, mouse_y, x, y); // ����
            double rotate_angle = physics::scalar_angle((double)(win_width / 2), (double)(win_height / 2), mouse_x, mouse_y, x, y); // �������κ��� ��ȭ�� ���

            // ���� ���⿡ ���� ��ȭ����ŭ ȸ��
            if ((cross_product) > 0)
            {
                roll -= (float)rotate_angle * 50.0f;
            }
            else if ((cross_product) < 0)
            {
                roll += (float)rotate_angle * 50.0f;
            }
            // ���� ��ġ ����
            mouse_x = x;
            mouse_y = y;
        }
    }

    void mouse_wheel(int button, int dir, int x, int y) // ���콺 ��
    {
        if (dir > 0)
        {
            viewZ += 0.5f; // Ȯ��
        }
        else if (dir < 0)
        {
            viewZ -= 0.5f; // ���
        }
    }

    void reshape2d(GLsizei width, GLsizei height) // ������ ũ�⿡ ������� ��� ���� (ũ��� �ٲ�)
    {
        if (height == 0) height = 1;                // 0���� ������ �� ����
        GLfloat aspect = (GLfloat)width / (GLfloat)height;

        //����� ������ũ��� viewport�� �����Ѵ�.
        glViewport(0, 0, width, height);

        win_width = width;
        win_height = height;

        glMatrixMode(GL_PROJECTION);  //�ڿ� ���� ������ Projection matrix�� ������ �ֵ��� ����
        glLoadIdentity();             //projection matrix �ʱ�ȭ

        // 2d �ɼ�
        if (width >= height) {
            // aspect >= 1 �̸�, height�� [-1,1]�� �����ϰ� width�� [-1*aspect, 1*aspect]�� �����Ѵ�.
            // left, right, top, bottom
            gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
        }
        else {
            // aspect < 1�̸�, width�� [-1,1]�� �����ϰ� height��  [-1/aspect, 1/aspect]�� �����Ѵ�.
            gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
        }
    }

    void reshape3d(GLsizei width, GLsizei height) // ������ ũ�⿡ ������� ��� ���� (ũ��� �ٲ�)
    {
        if (height == 0) height = 1;                // 0���� ������ �� ����
        GLfloat aspect = (GLfloat)width / (GLfloat)height;

        //����� ������ũ��� viewport�� �����Ѵ�.
        glViewport(0, 0, width, height);

        win_width = width;
        win_height = height;

        glMatrixMode(GL_PROJECTION);  //�ڿ� ���� ������ Projection matrix�� ������ �ֵ��� ����
        glLoadIdentity();             //projection matrix �ʱ�ȭ

        //Field of view angle(���� degrees), �������� aspect ratio, Near�� Far Plane����, 3d �ɼ�
        gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    }

    void timer(int value) {
        glutPostRedisplay();      //�����츦 �ٽ� �׸����� ��û
        glutTimerFunc(10, timer, 0); //���� Ÿ�̸� �̺�Ʈ�� 10�и�����Ʈ �� ȣ���.
    }
}