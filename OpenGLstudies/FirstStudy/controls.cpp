#include "controls.h"

void keyboard(unsigned char key, int x, int y) // esc로 종료
{
	if (key == 27)
	{
		exit(0);
	}
}

void reshape2d(GLsizei width, GLsizei height) // 윈도우 크기에 관계없이 모양 고정 (크기는 바뀜)
{
    if (height == 0) height = 1;                // 0으로 나누는 것 방지
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    //변경된 윈도우크기로 viewport를 설정한다.
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);  //뒤에 오는 계산들은 Projection matrix에 영향을 주도록 설정
    glLoadIdentity();             //projection matrix 초기화

    // 2d 옵션
    if (width >= height) {
        // aspect >= 1 이면, height를 [-1,1]로 설정하고 width는 [-1*aspect, 1*aspect]로 설정한다.
        // left, right, top, bottom
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else {
        // aspect < 1이면, width를 [-1,1]로 설정하고 height를  [-1/aspect, 1/aspect]로 설정한다.
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }

    //뒤에 오는 계산들은 Modelview Matrix에 영향을 주도록 설정한다. 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Modelview matrix 초기화
}

void reshape3d(GLsizei width, GLsizei height) // 윈도우 크기에 관계없이 모양 고정 (크기는 바뀜)
{
    if (height == 0) height = 1;                // 0으로 나누는 것 방지
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    //변경된 윈도우크기로 viewport를 설정한다.
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);  //뒤에 오는 계산들은 Projection matrix에 영향을 주도록 설정
    glLoadIdentity();             //projection matrix 초기화

    //Field of view angle(단위 degrees), 윈도우의 aspect ratio, Near와 Far Plane설정, 3d 옵션
    gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0);

    //뒤에 오는 계산들은 Modelview Matrix에 영향을 주도록 설정한다. 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //Modelview matrix 초기화
}


void timer(int value) {
    glutPostRedisplay();      //윈도우를 다시 그리도록 요청
    glutTimerFunc(30, timer, 0); //다음 타이머 이벤트는 30밀리세컨트 후  호출됨.
}