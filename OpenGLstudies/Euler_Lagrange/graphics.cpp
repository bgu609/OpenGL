#include "graphics.h"

using namespace controls;

// 윈도우
extern int win_width;
extern int win_height;

// 좌표
extern float viewX;
extern float viewY;
extern float viewZ;

// 회전
extern float pitch;
extern float yaw;
extern float roll;

namespace graphics
{
    float scale_area = 5.0f; // scale_map을 그릴 범위
	int scale_conver = 20; // scale_map 분할 단위, 높을수록 세분화, 1.0f == 0~20
    int scale_count = (int)scale_area * scale_conver; // scale_map 범위에 따른 보정

    double surface = 3.0 / (double)scale_conver;

	float xs[] = { 0, 1, -2, 3, -4, -5, 6, -7, 8, 19 };
	float ys[] = { 0, 15, 8, 5, -10, 10, -5, 2, 10, 19 };

	//void path()
	//{
	//	glColor3f(0.0f, 0.0f, 1.0f);

	//	for (int i = 1; i < 10; i++)
	//	{
	//		glBegin(GL_LINE_STRIP);
	//		glVertex2f((float)xs[i-1] / (float)scale_conver, (float)ys[i-1] / (float)scale_conver);
	//		glVertex2f((float)xs[i] / (float)scale_conver, (float)ys[i] / (float)scale_conver);
	//		glEnd();
	//	}
	//}

	//void nodes() // polygon 생성
	//{
	//	glColor3f(1.0f, 0.0f, 0.0f);

	//	float rx = 0.0f;
	//	float ry = 0.0f;

	//	for (int j = 0; j < 10; j++)
	//	{
	//		glBegin(GL_POLYGON);
	//		for (int i = 0; i < 360; i++)
	//		{
	//			rx = xs[j] / (float)scale_conver + 0.05f * (float)(cos(i * M_PI / 180) / 4); // 4 나눈 건 그래픽 표현 보정치
	//			ry = ys[j] / (float)scale_conver + 0.05f * (float)(sin(i * M_PI / 180) / 4); // 4 나눈 건 그래픽 표현 보정치
	//			glVertex2f(rx, ry);
	//		}
	//		glEnd();
	//	}
	//}

	void object_marking(double x, double y) // 물체 좌표 마킹
	{
		glDepthFunc(GL_ALWAYS);

		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINE_STRIP);
		glVertex3d((x - 1.0) / (double)scale_conver, y / (double)scale_conver, 0);
		glVertex3d((x + 1.0) / (double)scale_conver, y / (double)scale_conver, 0);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3d(x / (double)scale_conver, (y - 1.0) / (double)scale_conver, 0);
		glVertex3d(x / (double)scale_conver, (y + 1.0) / (double)scale_conver, 0);
		glEnd();

		glDepthFunc(GL_LESS);
	}

    void sq_object(double x, double y, double size, double deep)
    {
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_QUADS);
        glVertex3d((x - size / 2.0) / (double)scale_conver, (y - size / 2.0) / (double)scale_conver, deep);
        glVertex3d((x - size / 2.0) / (double)scale_conver, (y + size / 2.0) / (double)scale_conver, deep);
        glVertex3d((x + size / 2.0) / (double)scale_conver, (y + size / 2.0) / (double)scale_conver, deep);
        glVertex3d((x + size / 2.0) / (double)scale_conver, (y - size / 2.0) / (double)scale_conver, deep);
        glEnd();

		object_marking(x, y);
    }

	void polygon(double x, double y, double z, double deep)
	{
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glBegin(GL_POLYGON);
		glVertex3d((x - 1.0) / (double)scale_conver, y / (double)scale_conver, deep / (double)scale_conver);
		glVertex3d((x + 1.0) / (double)scale_conver, y / (double)scale_conver, deep / (double)scale_conver);
		glVertex3d((x + 0.5) / (double)scale_conver, y / (double)scale_conver, (z + deep) / (double)scale_conver);
		glVertex3d((x - 0.5) / (double)scale_conver, y / (double)scale_conver, (z + deep) / (double)scale_conver);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3d(x / (double)scale_conver, (y - 1.0) / (double)scale_conver, deep / (double)scale_conver);
		glVertex3d(x / (double)scale_conver, (y + 1.0) / (double)scale_conver, deep / (double)scale_conver);
		glVertex3d(x / (double)scale_conver, (y + 0.5) / (double)scale_conver, (z + deep) / (double)scale_conver);
		glVertex3d(x / (double)scale_conver, (y - 0.5) / (double)scale_conver, (z + deep) / (double)scale_conver);
		glEnd();

		object_marking(x, y);
	}

    void water_layer(double surface)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 1.0f, 0.4f);

        glBegin(GL_QUADS);
        glVertex3d(-scale_area, -scale_area, surface);
        glVertex3d(-scale_area, scale_area, surface);
        glVertex3d(scale_area, scale_area, surface);
        glVertex3d(scale_area, -scale_area, surface);
        glEnd();
    }

    void water_box(double surface)
    {
		water_layer(-scale_area);
		water_layer(surface);
    }

	void scale_map()
	{
        // 세부 눈금
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.0f, 0.0f, 0.1f);
		for (int i = -scale_count; i <= scale_count; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex3f(-scale_area, (float)i / (float)scale_conver, 0);
			glVertex3f(scale_area, (float)i / (float)scale_conver, 0);
			glEnd();

			glBegin(GL_LINE_STRIP);
			glVertex3f((float)i / (float)scale_conver, -scale_area, 0);
			glVertex3f((float)i / (float)scale_conver, scale_area, 0);
			glEnd();
		}
	}

    void display()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 화면을 지운다. (컬러버퍼와 깊이버퍼)
        glEnable(GL_DEPTH_TEST); // 깊이 테스트 기능 동작
        glMatrixMode(GL_MODELVIEW); // 이후 연산은 ModelView Matirx에 영향을 준다. 객체 조작
        glLoadIdentity();
        // 이동과 회전을 적용
        glTranslatef(viewX, viewY, viewZ);
        glRotatef(pitch, 1.0, 0.0, 0.0); //x축에 대해 회전
        glRotatef(yaw, 0.0, 1.0, 0.0); //y축에 대해 회전
        glRotatef(roll, 0.0, 0.0, 1.0); //z축에 대해 회전

		glEnable(GL_BLEND); // 블렌딩 적용
        // 오브젝트 - 좌표 - water 순서로 맞춰야 의도대로 표현됨(블렌딩)....
        
        sq_object(2.0, 5.0, 4.0, surface + 0.01);
		sq_object(0.0, 0.0, 4.0, -1.0);
		polygon(-10.0, 0.0, 7.0, -2.0);

        scale_map(); // scale map 표시
		water_box(surface); // water 표현
		
		glDisable(GL_BLEND); // 블렌딩 해제
        
        glutSwapBuffers();
    }

	void draw()
	{
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //더블 버퍼와 깊이 버퍼를 사용하도록 설정, GLUT_RGB=0x00임 (3d 옵션)
		glutInitWindowSize(win_width, win_height);
		glutInitWindowPosition(300, 300);
		glutCreateWindow("OpenGL EL");

		glutDisplayFunc(display);
	}
}