#include "CWorld.h"
#include "CCreature.h"
#include "CResource.h"

CWorld * CWorld::m_instance = NULL;

CWorld::CWorld() {
	
}

void CWorld::paint() {
	CWorld * w = instance();
	
	std::list<CCreature*>::iterator creatureIt;
	for(creatureIt = w->m_creatures.begin(); creatureIt != w->m_creatures.end(); creatureIt++) {
		(*creatureIt)->paint();
	}

	std::list<CResource*>::iterator resourceIt;
	for(resourceIt = w->m_resources.begin(); resourceIt != w->m_resources.end(); resourceIt++) {
		(*resourceIt)->paint();
	}
}

void CWorld::update() {
	CWorld * w = instance();
	std::list<CCreature *>::iterator creatureIt;
	for(creatureIt = w->m_creatures.begin(); creatureIt != w->m_creatures.end(); creatureIt++) {
		(*creatureIt)->live(TIME_PER_UPDATE);
	}
}

CWorld * CWorld::instance() {
	if(!m_instance) {
		m_instance = new CWorld();
	}
	return m_instance;
}
