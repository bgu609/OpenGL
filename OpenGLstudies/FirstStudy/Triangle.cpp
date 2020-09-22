#include "Triangle.h"

using namespace std;

namespace Tri
{
    GLfloat current_angle = 0.0f; //�ﰢ���� ���� ȸ�� ����

	void display()
	{
        glClear(GL_COLOR_BUFFER_BIT); //�÷� ���۸� �����.

        glMatrixMode(GL_MODELVIEW); //���� ����� modelview matrix�� ������ �ְԵ�
        glLoadIdentity(); //modleview matrix�� �ʱ�ȭ

        //z���� �߽����� ������ current_angle�� ȸ���Ѵ�.
        glRotatef(current_angle, 0.0f, 0.0f, 1.0f);

        //�߾��� ������ ������ �ﰢ���� �׸���. 
        glBegin(GL_TRIANGLES); //3���� �ϳ��� �ﰢ���� �����Ѵ�. �ݽð� �������� 3���� vertex�� ��������� �Ѵ�.
        glColor3f(1.0f, 0.0f, 0.0f); //������ ����
        glVertex3f(-0.5f, -0.5f, 0.0f);    // ���� �Ʒ� vertex
        glColor3f(0.0f, 1.0f, 0.0f); //��� ����
        glVertex3f(0.5f, -0.5f, 0.0f);    // ������ �Ʒ� vertex
        glColor3f(0.0f, 0.0f, 1.0f); //�Ķ��� ����
        glVertex3f(0.0f, 0.5f, 0.0f);    // ���� vertex
        glEnd();

        // display �Լ� ȣ��ɶ����� ȸ������ ������Ŵ
        //current_angle += 10;

		//glFlush();
        glutSwapBuffers(); // �̱� ���۶�� ���ۿ� �ִ� ���� ȭ�鿡 ���
	}

	void Triangles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Rectanlge Example");

		glutDisplayFunc(display);
	}
}