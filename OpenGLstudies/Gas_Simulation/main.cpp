#include "controls.h"
#include "ideal.h"

using namespace Ctrls;

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT 초기화

	Ideal::Particles idp;
	idp.draw();

	glutKeyboardFunc(keyboard); // 키보드 콜백 함수 등록
	glutSpecialFunc(special); // 키보드 콜백 함수 등록
	glutReshapeFunc(reshape2d); // reshape 콜백 함수 등록
	glutTimerFunc(0, timer, 0); // 타이머 콜백 함수 등록, 처음에는 바로 호출
	glutMainLoop(); //GLUT event processing loop에 진입

	return 0;
}