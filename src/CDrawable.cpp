#include "CDrawable.h"

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
