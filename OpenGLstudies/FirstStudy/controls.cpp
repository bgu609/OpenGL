#include "controls.h"

void keyboard(unsigned char key, int x, int y) // esc�� ����
{
	if (key == 27)
	{
		exit(0);
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

    //�ڿ� ���� ������ Modelview Matrix�� ������ �ֵ��� �����Ѵ�. 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Modelview matrix �ʱ�ȭ
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

    //�ڿ� ���� ������ Modelview Matrix�� ������ �ֵ��� �����Ѵ�. 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Modelview matrix �ʱ�ȭ
}


void timer(int value) {
    glutPostRedisplay();      //�����츦 �ٽ� �׸����� ��û
    glutTimerFunc(10, timer, 0); //���� Ÿ�̸� �̺�Ʈ�� %d�и�����Ʈ ��  ȣ���.
}