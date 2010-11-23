#include <GL/gl.h>
#include <GL/glut.h>
#include "CResource.h"

CResource::CResource(CPoint & center, float amount) : CDrawable(center, CResource::DEFAULT_RESOURCE_RADIUS) {
    m_amount = amount;
}

float CResource::amount() const {
    return m_amount;
}

float CResource::take(float amount) {
    float res = amount > m_amount ? m_amount : amount;
    m_amount -= res;
    return res;
}

void CResource::paint() {
#ifndef C_NO_GL
    float x = center().x();
    float y = center().y();
    float r = radius();
    glBegin(GL_QUADS);        
        glVertex2f(x - r, y - r);
        glVertex2f(x - r, y + r);
        glVertex2f(x + r, y + r);
        glVertex2f(x + r, y - r);
    glEnd();
#endif //C_NO_GL
}
