#include "CWorld.h"
#include "CCreature.h"
#include "CResource.h"
#include "CPoint.h"
#include "CDebug.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

CWorld * CWorld::m_instance = NULL;

CWorld::CWorld() {
	if(!m_instance) {
		addCreature(new CCreature(CCreature::GENDER_MALE, CPoint(-0.3,-0.21), NULL, NULL));
		CPoint p(-0.5, -0.5);
		addResource(new CResource(CResource::RES_TYPE_WATER, p, 1.0f));
	}
	else {
		throw 0;
	}
}

void CWorld::init(int argc, char ** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Civsim");
    glutDisplayFunc(CWorld::paint);
    glutTimerFunc(100, CWorld::update, 0);	    
    glClearColor(0.0,0.0,0.0,0.0);
}

void CWorld::paint() {
	glClear(GL_COLOR_BUFFER_BIT);

	CWorld * w = instance();
	
	int x, y;

	std::list<CCreature*>::iterator creatureIt;
	for(creatureIt = w->m_creatures.begin(); creatureIt != w->m_creatures.end(); creatureIt++) {
		(*creatureIt)->loadTilePos(x, y);
		(*creatureIt)->paint();
	}

	std::list<CResource*>::iterator resourceIt;
	for(resourceIt = w->m_resources.begin(); resourceIt != w->m_resources.end(); resourceIt++) {
		(*resourceIt)->loadTilePos(x, y);
		(*resourceIt)->paint();
	}

	glutSwapBuffers();
}

void CWorld::update(int v) {
	CWorld * w = instance();
	std::list<CCreature *>::iterator creatureIt;
	for(creatureIt = w->m_creatures.begin(); creatureIt != w->m_creatures.end(); creatureIt++) {
		(*creatureIt)->live(TIME_PER_UPDATE);
	}
    glutTimerFunc(100, CWorld::update, 0);
}

CWorld * CWorld::instance() {
	if(!m_instance) {
		m_instance = new CWorld();
	}
	return m_instance;
}


void CWorld::addCreature(CCreature * c) {
    /// @todo Need to exclude double insertion of creatures
    m_creatures.push_back(c);
	int x, y;
	c->loadTilePos(x, y);
	m_creaturePosIndex[x][y].push_back(c);
}

void CWorld::removeCreature(CCreature * c) {
    m_creatures.remove(c);
	int x, y;
	c->loadTilePos(x, y);
	m_creaturePosIndex[x][y].remove(c);
}

void CWorld::addResource(CResource * r) {
    /// @todo Need to exclude double insertion of resources
    m_resources.push_back(r);
	int x, y;
	r->loadTilePos(x, y);
	m_resourcePosTypeIndex[x][y][r->type()].push_back(r);
}

void CWorld::removeResource(CResource * r) {
    m_resources.remove(r);
	int x, y;
	r->loadTilePos(x, y);
	m_resourcePosTypeIndex[x][y][r->type()].remove(r);
}

void CWorld::run() {
    glutMainLoop();
}

std::list<CResource*> CWorld::visibleResources(const CCreature & creature, CResource::ResourceType resourceType) const{
	std::list<CResource*> res;
	int centerX;
	int centerY;
	int halfVision = creature.vision() / 2;
	creature.loadTilePos(centerX, centerY);

	int minX = centerX - halfVision;
	int maxX = centerX + halfVision;
	int minY = centerY - halfVision;
	int maxY = centerY + halfVision;

	int i, j;
	for(i = minX; i < maxX; ++i) {
		for(j = minY; j < maxY; ++j) {
			if(!m_resourcePosTypeIndex[i][j][resourceType].empty()){				
				res.insert(res.begin(),m_resourcePosTypeIndex[i][j][resourceType].begin(), m_resourcePosTypeIndex[i][j][resourceType].end());
			}
		}
	}
	return res;
}

