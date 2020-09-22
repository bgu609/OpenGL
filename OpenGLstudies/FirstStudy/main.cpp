#include "controls.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cube.h"

using namespace Tri;
using namespace Rect;
using namespace Cb;

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT �ʱ�ȭ

	//Rect::Rectangles r;
	//r.draw();

	//Triangles t;
	//t.draw();

	Cubes cube1;
	cube1.draw();

	glutKeyboardFunc(Cb::keyboard); // Ű���� �ݹ� �Լ� ���
	glutSpecialFunc(special);
	glutReshapeFunc(reshape); // reshape �ݹ� �Լ� ���
	glutTimerFunc(0, timer, 0); // Ÿ�̸� �ݹ� �Լ� ���, ó������ �ٷ� ȣ��
	glutMainLoop(); //GLUT event processing loop�� ����

	return 0;
}