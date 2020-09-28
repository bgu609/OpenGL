#include "controls.h"
#include "graphics.h"

using namespace controls;
using namespace graphics;

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT �ʱ�ȭ

	draw();

	glutKeyboardFunc(keyboard); // Ű���� �ݹ� �Լ� ���
	glutSpecialFunc(special_key); // Ű���� �ݹ� �Լ� ���
	glutReshapeFunc(reshape3d); // reshape �ݹ� �Լ� ���
	glutTimerFunc(0, timer, 0); // Ÿ�̸� �ݹ� �Լ� ���, ó������ �ٷ� ȣ��
	glutMainLoop(); //GLUT event processing loop�� ����

	return 0;
}