#include "controls.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cube.h"
#include "Particle.h"

using namespace Ptc;

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT �ʱ�ȭ

	//Rect::Rectangles r;
	//r.draw();

	//Triangles t;
	//t.draw();

	//Cubes cube1;
	//cube1.draw();

	Particles p1;
	p1.draw();

	glutKeyboardFunc(keyboard); // Ű���� �ݹ� �Լ� ���
	//glutSpecialFunc(Cb::special);
	glutReshapeFunc(reshape2d); // reshape �ݹ� �Լ� ���
	glutTimerFunc(0, timer, 0); // Ÿ�̸� �ݹ� �Լ� ���, ó������ �ٷ� ȣ��
	glutMainLoop(); //GLUT event processing loop�� ����

	return 0;
}