#include "controls.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Cube.h"

using namespace Tri;
using namespace Rect;
using namespace Cb;

int main(int argc, char** argv)
{
	glutInit(&argc, argv); // GLUT 초기화

	//Rect::Rectangles r;
	//r.draw();

	//Triangles t;
	//t.draw();

	Cubes cube1;
	cube1.draw();

	glutKeyboardFunc(Cb::keyboard); // 키보드 콜백 함수 등록
	glutSpecialFunc(special);
	glutReshapeFunc(reshape); // reshape 콜백 함수 등록
	glutTimerFunc(0, timer, 0); // 타이머 콜백 함수 등록, 처음에는 바로 호출
	glutMainLoop(); //GLUT event processing loop에 진입

	return 0;
}