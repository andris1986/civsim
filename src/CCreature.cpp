#include <GL/glut.h>
#include <algorithm>
#include <list>
#include "CCreature.h"
#include "CTribe.h"
#include "CWorld.h"
#include "CDebug.h"

CCreature::CCreature(Gender gender, const CPoint & center, CTribe * tribe, CCreature * parent)
				     : CDrawable(center, CCreature::DEFAULT_RADIUS) {	
	m_tribe = tribe;
	m_parent = parent;
	m_gender = gender;
	m_alive = true;
	m_followedResource = NULL;
    m_stepSize = (2.0 / CWorld::TILE_COUNT / 10.0);
	m_vision = 10;
    m_randomDirection = rand() % 360;

	if(parent) {
		parent->addChild(*this);
	}

	if(tribe) {
		tribe->addCreature(*this);
	}

	m_age = 0;
	m_health = MAX_HEALTH;

	ResourceNeed waterNeed = {
		0.9,
		0.1,
		1.0,
		0.7,
		CResource::RES_TYPE_WATER,
		0.002,
	};

	ResourceNeed foodNeed = {
		0.5,
		0.1,
		1.0,
		0.7,
		CResource::RES_TYPE_FOOD,
		0.001,
	};


	m_needs.insert(m_needs.begin(), waterNeed);
	m_needs.insert(m_needs.begin(), foodNeed);

	CWorld::instance()->addCreature(this);
}

CCreature::~CCreature() {
	if(m_tribe) {
		m_tribe->removeCreature(*this);
	}
	if(m_parent) {
		m_parent->removeChild(*this);
	}

	if(m_followedResource){
		m_followedResource->unfollow(this);
	}

	CWorld::instance()->removeCreature(this);
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
	float z = center().z();
	float r = radius();

#ifdef CIVSIM_DBG
	// Change color to see dead creatures
	glColor3f(1.0, m_alive ? 1.0 : 0.0,m_alive ? 1.0 : 0.0);
#endif

	glTranslatef(x, y, z);
	glutSolidCone(r, 2.0 * r, 10, 10);
	glTranslatef(-x, -y, -z);

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
		}
		checkDeath();
		if(m_alive){
			CWorld * w = CWorld::instance();
			std::sort(m_needs.begin(), m_needs.end(), CCreature::compareNeeds);
		
			if(!m_followedResource || m_followedResource->type() != (*m_needs.begin()).resType){				
				for(it = m_needs.begin(); it != m_needs.end(); ++it) {
					ResourceNeed & need = *it;
					
					std::list<CResource*> res = w->visibleResources(*this, need.resType);
					if(res.size() > 0){
                        std::list<CResource*>::iterator resIt;
                        CResource * closestResource = *res.begin();
                        for(resIt = res.begin(); resIt != res.end(); ++resIt) {
                            if((*resIt)->center().distanceTo(center()) < closestResource->center().distanceTo(center())){
                                closestResource = *resIt;
                            }
                        }
                        
						if(m_followedResource){
							m_followedResource->unfollow(this);
						}
						closestResource->follow(this);
						break;
					}
				}
			}

			if(m_followedResource){
				if(intersect(*m_followedResource)){
					ResourceNeed & need = *m_needs.begin();
					need.curAmount += m_followedResource->take(need.maxAmount - need.curAmount);

					if(m_followedResource->amount() <= 0){
						w->removeResource(m_followedResource);
						delete m_followedResource;
                        m_randomDirection = rand() % 360;
					}
				}
				else {
					move(center().angleTo(m_followedResource->center()), m_stepSize);
				}
			}
			else {
				move(m_randomDirection, m_stepSize);
                if(center().x() < -1.0 || center().x() > 1.0 || center().y() < -1.0 || center().y() > 1.0){
                    m_randomDirection += 180.0;
                }
			}
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

bool CCreature::compareNeeds(const ResourceNeed & n1, const ResourceNeed & n2) {
	return (n1.curAmount - n1.minAmount) / n1.needPerTime < (n2.curAmount - n2.minAmount) / n2.needPerTime;
}

void CCreature::setFollowedResource(CResource * res) {	
	m_followedResource = res;
}

