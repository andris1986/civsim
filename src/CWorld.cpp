#include "CWorld.h"
#include "CCreature.h"
#include "CResource.h"
#include "CPoint.h"
#include "CDebug.h"
#include <math.h>
#include <GL/glut.h>
#include <time.h>

CWorld * CWorld::m_instance = NULL;

float genCoord(){
    return ((float)(rand() % 200)) / 100.0 - 1.0;
}

CWorld::CWorld() {
	if(!m_instance) {
		m_zoom = 1.1;
		m_xRotate = 0.0;
	}
	else {
		throw 0;
	}
}

void CWorld::init(int argc, char ** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Civsim");
    glutDisplayFunc(CWorld::paint);
	glutKeyboardFunc(CWorld::keyPress);
	glutReshapeFunc(CWorld::reshape);
    //glutTimerFunc(50, CWorld::update, 0);	    
    glutIdleFunc(CWorld::update);
    glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
    srand(time(NULL));

    for(int i=0;i<10;i++){
    	new CCreature(CCreature::GENDER_MALE, CPoint(genCoord(),genCoord(), 0.0), NULL, NULL);
    }

    for(int i=0;i<100; i++){
	    new CResource(CResource::RES_TYPE_WATER, CPoint(genCoord(), genCoord(), 0.0), 1.0f);
        new CResource(CResource::RES_TYPE_FOOD, CPoint(genCoord(), genCoord(), 0.0), 1.0f);
    }
}

void CWorld::paint() {
	glClear(GL_COLOR_BUFFER_BIT);

	CWorld * w = instance();
	
	int x, y;

	glLoadIdentity();
	gluLookAt(0.0, 0.0, w->m_zoom, 0.0, 0.0, -100, 0.0, 1.0, -2.0);	
	glRotatef(w->m_xRotate, 1.0, 0.0, 0.0);

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

void CWorld::update() {
	CWorld * w = instance();
	std::list<CCreature *>::iterator creatureIt;
	for(creatureIt = w->m_creatures.begin(); creatureIt != w->m_creatures.end(); creatureIt++) {
		(*creatureIt)->live(TIME_PER_UPDATE);
	}
    //glutTimerFunc(50, CWorld::update, 0);
	glutPostRedisplay();
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
	creature.loadTilePos(centerX, centerY);

	int minX = centerX - creature.vision();
	int maxX = centerX + creature.vision();
	int minY = centerY - creature.vision();
	int maxY = centerY + creature.vision();

	if(minX < 0) {
		minX = 0;
	}
	if(minY < 0) {
		minY = 0;
	}
	if(maxX >= TILE_COUNT) {
		maxX = TILE_COUNT - 1;
	}
	if(maxY >= TILE_COUNT) {
		maxY = TILE_COUNT - 1;
	}

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

std::list<CCreature*> CWorld::visibleCreatures(const CCreature & creature) const {
	std::list<CCreature*> res;
	int centerX;
	int centerY;
	creature.loadTilePos(centerX, centerY);

	int minX = centerX - creature.vision();
	int maxX = centerX + creature.vision();
	int minY = centerY - creature.vision();
	int maxY = centerY + creature.vision();

	if(minX < 0) {
		minX = 0;
	}
	if(minY < 0) {
		minY = 0;
	}
	if(maxX >= TILE_COUNT) {
		maxX = TILE_COUNT - 1;
	}
	if(maxY >= TILE_COUNT) {
		maxY = TILE_COUNT - 1;
	}

	int i, j;
	for(i = minX; i < maxX; ++i) {
		for(j = minY; j < maxY; ++j) {
			if(!m_creaturePosIndex[i][j].empty()){
				res.insert(res.begin(),m_creaturePosIndex[i][j].begin(), m_creaturePosIndex[i][j].end());
			}
		}
	}


	return res;

}

void CWorld::keyPress(unsigned char key, int x, int y) {
	CWorld * w = CWorld::instance();
	switch(key) {
		case '+': w->m_zoom -= 0.1; break;
		case '-': w->m_zoom += 0.1; break;
		case 's': w->m_xRotate += 1.0; break;
		case 'w': w->m_xRotate -= 1.0; break;
	}
	glutPostRedisplay();
}

void CWorld::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	
}

void CWorld::updateCreaturePosition(CCreature * c, int oldX, int oldY) {
	m_creaturePosIndex[oldX][oldY].remove(c);
	int newX, newY;
	c->loadTilePos(newX, newY);
	m_creaturePosIndex[oldX][oldY].push_back(c);

}
