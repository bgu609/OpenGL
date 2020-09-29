#include "graphics.h"

using namespace controls;

// ������
extern int win_width;
extern int win_height;
extern int win_x;
extern int win_y;

// ��ǥ
extern float viewX;
extern float viewY;
extern float viewZ;

// ȸ��
extern float pitch;
extern float yaw;
extern float roll;

namespace graphics
{
    float scale_area = 5.0f; // scale_map�� �׸� ����
	double scale_conver = 20; // scale_map ���� ����, �������� ����ȭ, 1.0f == 0~20
    int scale_count = (int)scale_area * (int)scale_conver; // scale_map ������ ���� ����

    double surface = 3.0 / scale_conver;

	float xs[] = { 0, 1, -2, 3, -4, -5, 6, -7, 8, 19 };
	float ys[] = { 0, 15, 8, 5, -10, 10, -5, 2, 10, 19 };

	void path()
	{
		glColor3f(0.0f, 0.0f, 1.0f);

		for (int i = 1; i < 10; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f((float)xs[i-1] / (float)scale_conver, (float)ys[i-1] / (float)scale_conver);
			glVertex2f((float)xs[i] / (float)scale_conver, (float)ys[i] / (float)scale_conver);
			glEnd();
		}
	}

	void nodes() // polygon ����
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		float rx = 0.0f;
		float ry = 0.0f;

		for (int j = 0; j < 10; j++)
		{
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++)
			{
				rx = xs[j] / (float)scale_conver + 0.05f * (float)(cos(i * M_PI / 180) / 4); // 4 ���� �� �׷��� ǥ�� ����ġ
				ry = ys[j] / (float)scale_conver + 0.05f * (float)(sin(i * M_PI / 180) / 4); // 4 ���� �� �׷��� ǥ�� ����ġ
				glVertex2f(rx, ry);
			}
			glEnd();
		}
	}

	void object_marking(double x, double y) // ��ü ��ǥ ��ŷ
	{
		glDepthFunc(GL_ALWAYS);

		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		glBegin(GL_LINE_STRIP);
		glVertex3d((x - 1.0) / scale_conver, y / scale_conver, 0);
		glVertex3d((x + 1.0) / scale_conver, y / scale_conver, 0);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3d(x / scale_conver, (y - 1.0) / scale_conver, 0);
		glVertex3d(x / scale_conver, (y + 1.0) / scale_conver, 0);
		glEnd();

		glDepthFunc(GL_LESS);
	}

    void sq_object(double x, double y, double size, double deep)
    {
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_QUADS);
        glVertex3d((x - size / 2.0) / scale_conver, (y - size / 2.0) / scale_conver, deep);
        glVertex3d((x - size / 2.0) / scale_conver, (y + size / 2.0) / scale_conver, deep);
        glVertex3d((x + size / 2.0) / scale_conver, (y + size / 2.0) / scale_conver, deep);
        glVertex3d((x + size / 2.0) / scale_conver, (y - size / 2.0) / scale_conver, deep);
        glEnd();

		object_marking(x, y);
    }

	void polygon(double x, double y, double z, double deep)
	{
		double rx = 0.0;
		double ry = 0.0;
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			rx = (double)(x + 1.0 * cos(i * M_PI / 180));
			ry = (double)(y + 1.0 * sin(i * M_PI / 180));
			glVertex3d(rx / scale_conver, ry / scale_conver, deep / scale_conver);
		}
		glEnd();

		for (int i = 0; i < 360; i++)
		{
			if (i % 2 == 0)
			{
				glBegin(GL_POLYGON);
				rx = (double)(x + 1.0 * cos(i * M_PI / 180));
				ry = (double)(y + 1.0 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, deep / scale_conver);
				rx = (double)(x + 0.8 * cos(i * M_PI / 180));
				ry = (double)(y + 0.8 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, (z * 0.3 + deep) / scale_conver);
				rx = (double)(x + 0.6 * cos(i * M_PI / 180));
				ry = (double)(y + 0.6 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, (z * 0.7 + deep) / scale_conver);
				rx = (double)(x + 0.5 * cos(i * M_PI / 180));
				ry = (double)(y + 0.5 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, (z + deep) / scale_conver);
			}
			else if (i % 2 == 1)
			{
				rx = (double)(x + 0.5 * cos(i * M_PI / 180));
				ry = (double)(y + 0.5 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, (z + deep) / scale_conver);
				rx = (double)(x + 0.6 * cos(i * M_PI / 180));
				ry = (double)(y + 0.6 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, (z * 0.7 + deep) / scale_conver);
				rx = (double)(x + 0.8 * cos(i * M_PI / 180));
				ry = (double)(y + 0.8 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, (z * 0.3 + deep) / scale_conver);
				rx = (double)(x + 1.0 * cos(i * M_PI / 180));
				ry = (double)(y + 1.0 * sin(i * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, deep / scale_conver);
				rx = (double)(x + 1.0 * cos((i - 1.0) * M_PI / 180));
				ry = (double)(y + 1.0 * sin((i - 1.0) * M_PI / 180));
				glVertex3d(rx / scale_conver, ry / scale_conver, deep / scale_conver);
				glEnd();
			}
		}

		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			rx = (double)(x + 0.5 * cos(i * M_PI / 180));
			ry = (double)(y + 0.5 * sin(i * M_PI / 180));
			glVertex3d(rx / scale_conver, ry / scale_conver, (z + deep) / scale_conver);
		}
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
        // ���� ����
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ȭ���� �����. (�÷����ۿ� ���̹���)
        glEnable(GL_DEPTH_TEST); // ���� �׽�Ʈ ��� ����
        glMatrixMode(GL_MODELVIEW); // ���� ������ ModelView Matirx�� ������ �ش�. ��ü ����
        glLoadIdentity();
        // �̵��� ȸ���� ����
        glTranslatef(viewX, viewY, viewZ);
        glRotatef(pitch, 1.0, 0.0, 0.0); //x�࿡ ���� ȸ��
        glRotatef(yaw, 0.0, 1.0, 0.0); //y�࿡ ���� ȸ��
        glRotatef(roll, 0.0, 0.0, 1.0); //z�࿡ ���� ȸ��

		glEnable(GL_BLEND); // ���� ����
        // ������Ʈ - ��ǥ - water ������ ����� �ǵ���� ǥ����(����)....
        
		nodes();
		path();
        sq_object(19.0, 19.0, 4.0, surface + 0.01);
		sq_object(0.0, 0.0, 4.0, -1.0);
		polygon(-10.0, 0.0, 7.0, -2.0);

        scale_map(); // scale map ǥ��
		water_box(surface); // water ǥ��
		
		glDisable(GL_BLEND); // ���� ����
        
        glutSwapBuffers();
    }

	void draw()
	{
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //���� ���ۿ� ���� ���۸� ����ϵ��� ����, GLUT_RGB=0x00�� (3d �ɼ�)
		glutInitWindowSize(win_width, win_height);
		glutInitWindowPosition(win_x, win_y);
		glutCreateWindow("OpenGL EL");

		glutDisplayFunc(display);
	}
}