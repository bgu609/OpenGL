#include "Cube.h"

using namespace std;

namespace Cb
{
	//ť�� ��ġ
	float cubeX = 0.0;
	float cubeY = 0.0;
	float cubeZ = -4.0;

	//ȸ��
	float pitch = 0.0;
	float yaw = 0.0;
	float roll = 0.0;

    //ť���� �� ��, ȭ�� ���� ������ -Z��������� 0.5�̵��Ͽ� ���簢���� �׸���.
	static void cubebase(void)
	{
		glBegin(GL_POLYGON);
		glVertex3d(-0.5, -0.5, -0.5);
		glVertex3d(-0.5, 0.5, -0.5);
		glVertex3d(0.5, 0.5, -0.5);
		glVertex3d(0.5, -0.5, -0.5);
		glEnd();
	}

    //cubebase�Լ����� �׸� �簢���� ȸ�� �� �̵����� ť�긦 �ϼ���Ų��.
    void draw_cube()
    {
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);     // Green, -Z�� ����
        cubebase();

        glPushMatrix();
        /*construct side on +x axis*/
        glTranslated(1.0, 0.0, 0.0);
        glRotated(90.0, 0.0, 1.0, 0.0);
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue, +X�� ����
        cubebase();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.0, 0.0, 0.0);
        glRotated(-90.0, 0.0, 1.0, 0.0);
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange, -X�� ����
        cubebase();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.0, 1.0, 0.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        glColor3f(1.0f, 0.0f, 0.0f);     // Red, +Y�� ����
        cubebase();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.0, -1.0, 0.0);
        glRotated(90.0, 1.0, 0.0, 0.0);
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow, -Y�� ����
        cubebase();
        glPopMatrix();

        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta, +Z�� ����
        glBegin(GL_POLYGON);
        glVertex3d(-0.5, -0.5, 0.5);
        glVertex3d(0.5, -0.5, 0.5);
        glVertex3d(0.5, 0.5, 0.5);
        glVertex3d(-0.5, 0.5, 0.5);
        glEnd();

        glPopMatrix();

        glFlush();
    }

    void draw_line()
    {
        glPushMatrix();

        glPushMatrix(); //X�� ������
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(5.0, 0.0, 0.0);
        glVertex3f(-5.0, 0.0, 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix(); //Y�� ���
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 5.0, 0.0);
        glVertex3f(0.0, -5.0, 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix(); //Z�� �Ķ���
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 5.0);
        glVertex3f(0.0, 0.0, -5.0);
        glEnd();
        glPopMatrix();

        glPopMatrix();

        glFlush();
    }

    void display()
    {
        //ȭ���� �����. (�÷����ۿ� ���̹���)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //���� ������ ModelView Matirx�� ������ �ش�. ��ü ����
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // �̵��� ȸ���� ����
        glTranslatef(cubeX, cubeY, cubeZ);
        glRotatef(pitch, 1.0, 0.0, 0.0); //x�࿡ ���� ȸ��
        glRotatef(yaw, 0.0, 1.0, 0.0); //y�࿡ ���� ȸ��
        glRotatef(roll, 0.0, 0.0, 1.0); //z�࿡ ���� ȸ��

        //ť�긦 �׸�
        draw_cube();

        //��ǥ���� �׸�
        draw_line();

        glutSwapBuffers();
    }

	void Cubes::draw()
	{
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //���� ���ۿ� ���� ���۸� ����ϵ��� ����, GLUT_RGB=0x00��
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Rectanlge Example");

		glutDisplayFunc(display);
	}

    void special(int key, int x, int y)
    {
        if (key == GLUT_KEY_UP)
        {
            pitch += 1.0f;
        }
        else if (key == GLUT_KEY_DOWN)
        {
            pitch -= 1.0f;
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            yaw += 1.0f;
        }
        else if (key == GLUT_KEY_LEFT)
        {
            yaw -= 1.0f;
        }
        else if (key == GLUT_KEY_HOME)
        {
            pitch = 0.0f;
            yaw = 0.0f;
            roll = 0.0f;
        }
    }

    void keyboard(unsigned char key, int x, int y)
    {
        //ESC Ű�� �������ٸ� ���α׷� ����
        if (key == 27)
        {
            exit(0);
        }
        else if (key == '+')
        {
            cubeZ += 0.1f; // Ȯ��
        }
        else if (key == '-')
        {
            cubeZ -= 0.1f; // ���
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
            cubeY += 0.01f; // ��
        }
        else if (key == 's')
        {
            cubeY -= 0.01f; // ��
        }
        else if (key == 'd')
        {
            cubeX += 0.01f; // ��
        }
        else if (key == 'a')
        {
            cubeX -= 0.01f; // ��
        }
    }
}