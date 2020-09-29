#include "controls.h"

// 윈도우
int win_width = 800;
int win_height = 800;
int win_x = 400;
int win_y = 100;

// 좌표
float viewX = 0.0f;
float viewY = 0.0f;
float viewZ = -6.0f;

// 회전
float pitch = 0.0f;
float yaw = 0.0f;
float roll = 0.0f;

int clicked = 0;
int mouse_x = 0;
int mouse_y = 0;
int x_move = 0;
int y_move = 0;

namespace controls
{
    void keyboard(unsigned char key, int x, int y)
    {
        if (key == 27)  // esc로 종료
        {
            exit(0);
        }
        else if (key == '+')
        {
            viewZ += 0.1f; // 확대
        }
        else if (key == '-')
        {
            viewZ -= 0.1f; // 축소
        }
        else if (key == 'q')
        {
            roll -= 1.0f; // z+회전 (좌회전)
        }
        else if (key == 'e')
        {
            roll += 1.0f; // z-회전 (우회전)
        }
        else if (key == 'w')
        {
            viewY -= 0.01f; // 상
        }
        else if (key == 's')
        {
            viewY += 0.01f; // 하
        }
        else if (key == 'd')
        {
            viewX -= 0.01f; // 우
        }
        else if (key == 'a')
        {
            viewX += 0.01f; // 좌
        }
    }

    void special_key(int key, int x, int y)
    {
        if (key == GLUT_KEY_DOWN)
        {
            pitch += 1.0f; // 회전
        }
        else if (key == GLUT_KEY_UP)
        {
            pitch -= 1.0f; // 회전
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            yaw += 1.0f; // 회전
        }
        else if (key == GLUT_KEY_LEFT)
        {
            yaw -= 1.0f; // 회전
        }
        else if (key == GLUT_KEY_HOME) // 뷰 원위치
        {
            viewX = 0.0f;
            viewY = 0.0f;
            viewZ = -6.0f;
        }
    }

    void mouse_button(int button, int state, int x, int y)
    {
        if (clicked == 0 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // 클릭 시 마우스 위치 저장
        {
            clicked = 1;
            mouse_x = x;
            mouse_y = y;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            clicked = 0;
        }
        else if (clicked == 0 && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            clicked = 2;
            mouse_x = x;
            mouse_y = y;
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        {
            clicked = 0;
        }
    }

    void mouse_drag(int x, int y)
    {
        if (clicked == 1)
        {
            // 이전 위치에서의 차이만큼 뷰 이동
            viewX += (float)(x - mouse_x) / 100.0f;
            viewY -= (float)(y - mouse_y) / 100.0f;
            // 현재 위치 저장
            mouse_x = x;
            mouse_y = y;
        }
        else if (clicked == 2)
        {
            double scalar_product = physics::scalar_product((double)(win_width / 2), (double)(win_height / 2), mouse_x, mouse_y, x, y); // 내적
            double cross_product = physics::cross_product((double)(win_width / 2), (double)(win_height / 2), mouse_x, mouse_y, x, y); // 외적
            double rotate_angle = physics::scalar_angle((double)(win_width / 2), (double)(win_height / 2), mouse_x, mouse_y, x, y); // 내적으로부터 변화각 계산

            // 외적 방향에 따라 변화각만큼 회전
            if ((cross_product) > 0)
            {
                roll -= (float)rotate_angle * 50.0f;
            }
            else if ((cross_product) < 0)
            {
                roll += (float)rotate_angle * 50.0f;
            }
            // 현재 위치 저장
            mouse_x = x;
            mouse_y = y;
        }
    }

    void mouse_wheel(int button, int dir, int x, int y) // 마우스 휠
    {
        if (dir > 0)
        {
            viewZ += 0.5f; // 확대
        }
        else if (dir < 0)
        {
            viewZ -= 0.5f; // 축소
        }
    }

    void reshape2d(GLsizei width, GLsizei height) // 윈도우 크기에 관계없이 모양 고정 (크기는 바뀜)
    {
        if (height == 0) height = 1;                // 0으로 나누는 것 방지
        GLfloat aspect = (GLfloat)width / (GLfloat)height;

        //변경된 윈도우크기로 viewport를 설정한다.
        glViewport(0, 0, width, height);

        win_width = width;
        win_height = height;

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
    }

    void reshape3d(GLsizei width, GLsizei height) // 윈도우 크기에 관계없이 모양 고정 (크기는 바뀜)
    {
        if (height == 0) height = 1;                // 0으로 나누는 것 방지
        GLfloat aspect = (GLfloat)width / (GLfloat)height;

        //변경된 윈도우크기로 viewport를 설정한다.
        glViewport(0, 0, width, height);

        win_width = width;
        win_height = height;

        glMatrixMode(GL_PROJECTION);  //뒤에 오는 계산들은 Projection matrix에 영향을 주도록 설정
        glLoadIdentity();             //projection matrix 초기화

        //Field of view angle(단위 degrees), 윈도우의 aspect ratio, Near와 Far Plane설정, 3d 옵션
        gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    }

    void timer(int value) {
        glutPostRedisplay();      //윈도우를 다시 그리도록 요청
        glutTimerFunc(10, timer, 0); //다음 타이머 이벤트는 10밀리세컨트 후 호출됨.
    }
}