#include "controls.h"

namespace controls
{
    // ��ǥ
    float viewX = 0.0f;
    float viewY = 0.0f;
    float viewZ = 0.0f;

    // ȸ��
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;

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
            roll += 1.0f; // z+ȸ�� (��ȸ��)
        }
        else if (key == 'e')
        {
            roll -= 1.0f; // z-ȸ�� (��ȸ��)
        }
        else if (key == 'w')
        {
            viewY += 0.01f; // ��
        }
        else if (key == 's')
        {
            viewY -= 0.01f; // ��
        }
        else if (key == 'd')
        {
            viewX += 0.01f; // ��
        }
        else if (key == 'a')
        {
            viewX -= 0.01f; // ��
        }
    }

    void special(int key, int x, int y)
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
        else if (key == GLUT_KEY_HOME) // ȸ�� �ʱ�ȭ
        {
            pitch = 0.0f;
            yaw = 0.0f;
            roll = 0.0f;
        }
    }

    void reshape2d(GLsizei width, GLsizei height) // ������ ũ�⿡ ������� ��� ���� (ũ��� �ٲ�)
    {
        if (height == 0) height = 1;                // 0���� ������ �� ����
        GLfloat aspect = (GLfloat)width / (GLfloat)height;

        //����� ������ũ��� viewport�� �����Ѵ�.
        glViewport(0, 0, width, height);

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