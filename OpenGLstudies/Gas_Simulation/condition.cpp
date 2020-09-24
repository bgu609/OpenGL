#include "condition.h"

namespace Cnd
{
    // 바운더리
    void square_boundary(float b_length)
    {
        float length = b_length / 2.0f;

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);

        glVertex2f(length, length);
        glVertex2f(-length, length);
        glVertex2f(-length, -length);
        glVertex2f(length, -length);

        glEnd();
    }

    void rect_boundary(float width, float height)
    {
        float x = width / 2.0f;
        float y = height / 2.0f;

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);

        glVertex2f(x, y);
        glVertex2f(-x, y);
        glVertex2f(-x, -y);
        glVertex2f(x, -y);

        glEnd();
    }
}