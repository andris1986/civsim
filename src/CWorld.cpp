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
		m_creatures.push_back(new CCreature(CCreature::GENDER_MALE, CPoint(0,0), NULL, NULL));
		CPoint p(-0.5, -0.5);
		m_resources.push_back(new CResource(p, 1.0f));
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
	
	std::list<CCreature*>::iterator creatureIt;
	for(creatureIt = w->m_creatures.begin(); creatureIt != w->m_creatures.end(); creatureIt++) {
		(*creatureIt)->paint();
	}

	std::list<CResource*>::iterator resourceIt;
	for(resourceIt = w->m_resources.begin(); resourceIt != w->m_resources.end(); resourceIt++) {
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
}

void CWorld::removeCreature(CCreature * c) {
    m_creatures.remove(c);
}

void CWorld::addResource(CResource * r) {
    /// @todo Need to exclude double insertion of resources
    m_resources.push_back(r);
}

void CWorld::removeResource(CResource * r) {
    m_resources.remove(r);
}

void CWorld::run() {
    glutMainLoop();
}

