#include "Triangle.h"

using namespace std;

namespace Tri
{
    GLfloat current_angle = 0.0f; //삼각형의 현재 회전 각도

	void display()
	{
        glClear(GL_COLOR_BUFFER_BIT); //컬러 버퍼를 지운다.

        glMatrixMode(GL_MODELVIEW); //이후 계산은 modelview matrix에 영향을 주게됨
        glLoadIdentity(); //modleview matrix를 초기화

        //z축을 중심으로 설정된 current_angle로 회전한다.
        glRotatef(current_angle, 0.0f, 0.0f, 1.0f);

        //중앙이 원점에 오도록 삼각형을 그린다. 
        glBegin(GL_TRIANGLES); //3점이 하나의 삼각형을 구성한다. 반시계 방향으로 3점의 vertex를 지정해줘야 한다.
        glColor3f(1.0f, 0.0f, 0.0f); //빨간색 지정
        glVertex3f(-0.5f, -0.5f, 0.0f);    // 왼쪽 아래 vertex
        glColor3f(0.0f, 1.0f, 0.0f); //녹색 지정
        glVertex3f(0.5f, -0.5f, 0.0f);    // 오른쪽 아래 vertex
        glColor3f(0.0f, 0.0f, 1.0f); //파란색 지정
        glVertex3f(0.0f, 0.5f, 0.0f);    // 위쪽 vertex
        glEnd();

        // display 함수 호출될때마다 회전각도 증가시킴
        //current_angle += 10;

		//glFlush();
        glutSwapBuffers(); // 싱글 버퍼라면 버퍼에 있는 것을 화면에 출력
	}

	void Triangles::draw()
	{
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow("OpenGL Rectanlge Example");

		glutDisplayFunc(display);
	}
}