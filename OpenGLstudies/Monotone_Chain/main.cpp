#include "controls.h"
#include "convex.h"

using namespace Ctrls;

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT �ʱ�ȭ

	Convex::draw();

	glutKeyboardFunc(keyboard); // Ű���� �ݹ� �Լ� ���
	glutSpecialFunc(special); // Ű���� �ݹ� �Լ� ���
	glutReshapeFunc(reshape2d); // reshape �ݹ� �Լ� ���
	glutTimerFunc(0, timer, 0); // Ÿ�̸� �ݹ� �Լ� ���, ó������ �ٷ� ȣ��
	glutMainLoop(); //GLUT event processing loop�� ����

	return 0;
}