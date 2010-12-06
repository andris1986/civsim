#include <GL/gl.h>
#include <GL/glut.h>
#include "CResource.h"

CResource::CResource(CResource::ResourceType type, CPoint & center, float amount) : CDrawable(center, CResource::DEFAULT_RESOURCE_RADIUS) {
    m_amount = amount;
	m_type = type;
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
    float x = center().x();
    float y = center().y();
	float z = center().z();
    float r = radius();

	glTranslatef(x, y, z);
	glutSolidSphere(r, 5, 5);
	glTranslatef(-x, -y, -z);
}

CResource::ResourceType CResource::type() {
	return m_type;
}
