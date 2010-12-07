#include "CDrawable.h"
#include "CWorld.h"
#include "CDebug.h"

CDrawable::CDrawable(const CPoint & center, float radius) {
    m_center = center;
    m_radius = radius;
}

CPoint CDrawable::center() const {
    return m_center;
}

float CDrawable::radius() const {
    return m_radius;
}

void CDrawable::paint() {

}

void CDrawable::move(float direction, float distance) {
    m_center.move(direction, distance);
}

void CDrawable::loadTilePos(int & x, int & y) const {
	static float tileSize = 2.0 / CWorld::TILE_COUNT;
	x = (int)((center().x() + 1.0) / tileSize);
	y = (int)((center().y() + 1.0) / tileSize);
}

bool CDrawable::intersect(const CDrawable & other) const {
	int x1, x2, y1, y2;
	loadTilePos(x1, y1);
	other.loadTilePos(x2, y2);
	return (x1 == x2 && y1 == y2);
}
