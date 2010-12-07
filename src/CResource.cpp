#include <GL/gl.h>
#include <GL/glut.h>
#include "CResource.h"
#include "CCreature.h"

CResource::CResource(CResource::ResourceType type, const CPoint & center, float amount) : CDrawable(center, CResource::DEFAULT_RESOURCE_RADIUS) {
    m_amount = amount;
	m_type = type;
}

CResource::~CResource() {
	std::list<CCreature *>::iterator it;
	for(it = m_followers.begin(); it != m_followers.end(); ++it) {
		(*it)->setFollowedResource(NULL);
	}
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

    switch(m_type){
        case CResource::RES_TYPE_FOOD: glColor3f(0.0, 1.0, 0.0); break;
        case CResource::RES_TYPE_WATER: glColor3f(0.0, 0.0, 1.0); break;
        default: break;
    }
	glTranslatef(x, y, z);
	glutSolidCube(r);
	glTranslatef(-x, -y, -z);
}

CResource::ResourceType CResource::type() {
	return m_type;
}

void CResource::follow(CCreature * c) {
	m_followers.push_back(c);
	c->setFollowedResource(this);
}

void CResource::unfollow(CCreature * c) {
	m_followers.remove(c);
	c->setFollowedResource(NULL);
}
