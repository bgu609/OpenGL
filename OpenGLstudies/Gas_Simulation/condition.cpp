#include "condition.h"

namespace Cnd
{
    // 바운더리
    void square_boundary(float length)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);

        glVertex2f(length, length);
        glVertex2f(-length, length);
        glVertex2f(-length, -length);
        glVertex2f(length, -length);

        glEnd();
    }
}