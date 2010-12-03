#include <GL/gl.h>

#include "CCreature.h"
#include "CTribe.h"
#include "CWorld.h"
#include "CDebug.h"

CCreature::CCreature(Gender gender, const CPoint & center, CTribe * tribe, CCreature * parent)
				     : CDrawable(center, CCreature::DEFAULT_RADIUS) {	
	m_tribe = tribe;
	m_parent = parent;
	m_gender = gender;
	/// @todo Some constant would be useful.
	m_vision = 14;

	if(parent) {
		parent->addChild(*this);
	}

	if(tribe) {
		tribe->addCreature(*this);
	}

	m_age = 0;
	m_health = MAX_HEALTH;

	ResourceNeed need = {
		0.5,
		0.1,
		1.0,
		0.7,
		CResource::RES_TYPE_WATER,
		0.001,
	};

	m_needs.insert(m_needs.begin(), need);
}

CCreature::~CCreature() {
	if(m_tribe) {
		m_tribe->removeCreature(*this);
	}
	if(m_parent) {
		m_parent->removeChild(*this);
	}
}

void CCreature::attack(CCreature & other) {
	if(m_health > other.m_health) {
		other.die();
	}
	else if(m_health < other.m_health) {
		die();
	}
	else {
		die();
		other.die();
	}
}

void CCreature::breed(CCreature & other) {
	getPregnant();
}

void CCreature::paint() {
	float x = center().x();
	float y = center().y();
	float r = radius();

#ifdef CIVSIM_DBG
	// Change color to see dead creatures
	glColor3f(1.0, m_alive ? 1.0 : 0.0,m_alive ? 1.0 : 0.0);
#endif
	glBegin(GL_QUADS);
		glVertex2f(x - r, y - r);
		glVertex2f(x - r, y + r);
		glVertex2f(x + r, y + r);
		glVertex2f(x + r, y - r);
	glEnd();

#ifdef CIVSIM_DBG
	// Draw border around the creature to see it's visible area
	float visionDistance = m_vision * (2.0 / CWorld::TILE_COUNT);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x - visionDistance, y - visionDistance);
		glVertex2f(x - visionDistance, y + visionDistance);
		glVertex2f(x + visionDistance, y + visionDistance);
		glVertex2f(x + visionDistance, y - visionDistance);
	glEnd();
#endif

}

void CCreature::live(int time) {
	if(m_alive) {
		m_age += time;
		std::vector<ResourceNeed>::iterator it;
		for(it = m_needs.begin(); it != m_needs.end(); ++it) {
			ResourceNeed & need = *it;
			need.curAmount -= (need.needPerTime * time);			
			checkDeath();
		}
	}
}

void CCreature::move(float direction, float distance) {
	m_center.move(direction, distance);
}

bool CCreature::getPregnant() {
	return (m_gender == GENDER_FEMALE);
}

void CCreature::die() {
	m_alive = false;
}

void CCreature::addChild(CCreature & c) {
	m_children.push_back(&c);

	if(c.m_parent){
		c.m_parent->m_children.remove(&c);
	}
	c.m_parent = this;
}

void CCreature::removeChild(CCreature & c) {
	m_children.remove(&c);
	c.m_parent = NULL;
}

int CCreature::vision() const {
	return m_vision;
}

void CCreature::checkDeath() {
	bool dead = false;
	if(m_health <= 0) {
		dead = true;
	}
	else {
		std::vector<ResourceNeed>::iterator it;
		for(it = m_needs.begin(); it != m_needs.end(); ++it) {
			ResourceNeed & need = *it;
			if(need.curAmount < need.minAmount) {
				dead = true;
				break;
			}
		}
	}
	
	m_alive = !dead;
}

