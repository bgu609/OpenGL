#include "Cube.h"

using namespace std;

namespace Cb
{
	//큐브 위치
	float cubeX = 0.0;
	float cubeY = 0.0;
	float cubeZ = -4.0;

	//회전
	float pitch = 0.0;
	float yaw = 0.0;
	float roll = 0.0;

    //큐브의 한 면, 화면 안쪽 방향인 -Z축방향으로 0.5이동하여 정사각형을 그린다.
	static void cubebase(void)
	{
		glBegin(GL_POLYGON);
		glVertex3d(-0.5, -0.5, -0.5);
		glVertex3d(-0.5, 0.5, -0.5);
		glVertex3d(0.5, 0.5, -0.5);
		glVertex3d(0.5, -0.5, -0.5);
		glEnd();
	}

    //cubebase함수에서 그린 사각형을 회전 및 이동시켜 큐브를 완성시킨다.
    void draw_cube()
    {
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);     // Green, -Z축 방향
        cubebase();

        glPushMatrix();
        /*construct side on +x axis*/
        glTranslated(1.0, 0.0, 0.0);
        glRotated(90.0, 0.0, 1.0, 0.0);
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue, +X축 방향
        cubebase();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.0, 0.0, 0.0);
        glRotated(-90.0, 0.0, 1.0, 0.0);
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange, -X축 방향
        cubebase();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.0, 1.0, 0.0);
        glRotated(-90.0, 1.0, 0.0, 0.0);
        glColor3f(1.0f, 0.0f, 0.0f);     // Red, +Y축 방향
        cubebase();
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.0, -1.0, 0.0);
        glRotated(90.0, 1.0, 0.0, 0.0);
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow, -Y축 방향
        cubebase();
        glPopMatrix();

        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta, +Z축 방향
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

        glPushMatrix(); //X축 붉은색
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(5.0, 0.0, 0.0);
        glVertex3f(-5.0, 0.0, 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix(); //Y축 녹색
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 5.0, 0.0);
        glVertex3f(0.0, -5.0, 0.0);
        glEnd();
        glPopMatrix();

        glPushMatrix(); //Z축 파란색
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
        //화면을 지운다. (컬러버퍼와 깊이버퍼)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //이후 연산은 ModelView Matirx에 영향을 준다. 객체 조작
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // 이동과 회전을 적용
        glTranslatef(cubeX, cubeY, cubeZ);
        glRotatef(pitch, 1.0, 0.0, 0.0); //x축에 대해 회전
        glRotatef(yaw, 0.0, 1.0, 0.0); //y축에 대해 회전
        glRotatef(roll, 0.0, 0.0, 1.0); //z축에 대해 회전

        //큐브를 그림
        draw_cube();

        //좌표축을 그림
        draw_line();

        glutSwapBuffers();
    }

	void Cubes::draw()
	{
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //더블 버퍼와 깊이 버퍼를 사용하도록 설정, GLUT_RGB=0x00임
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
        //ESC 키가 눌러졌다면 프로그램 종료
        if (key == 27)
        {
            exit(0);
        }
        else if (key == '+')
        {
            cubeZ += 0.1f; // 확대
        }
        else if (key == '-')
        {
            cubeZ -= 0.1f; // 축소
        }
        else if (key == 'q')
        {
            roll += 1.0f; // z+회전 (좌회전)
        }
        else if (key == 'e')
        {
            roll -= 1.0f; // z-회전 (우회전)
        }
        else if (key == 'w')
        {
            cubeY += 0.01f; // 상
        }
        else if (key == 's')
        {
            cubeY -= 0.01f; // 하
        }
        else if (key == 'd')
        {
            cubeX += 0.01f; // 우
        }
        else if (key == 'a')
        {
            cubeX -= 0.01f; // 좌
        }
    }
}