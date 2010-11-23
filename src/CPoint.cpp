#include <math.h>
#include "CPoint.h"

CPoint::CPoint() {
	m_x = 0.0;
	m_y = 0.0;
}

CPoint::CPoint(float x, float y) {
	m_x = x;
	m_y = y;
}

void CPoint::setX(float x) {
	m_x = x;
}

void CPoint::setY(float y) {
	m_y = y;
}

void CPoint::moveTo(float x, float y) {
	m_x = x;
	m_y = y;
}

void CPoint::move(float direction, float distance) {
	float dx = cos(direction) * distance;
	float dy = sin(direction) * distance;
	m_x += dx;
	m_y += dy;
}

float CPoint::x() const {
	return m_x;
}

float CPoint::y() const {
	return m_y;
}

float CPoint::distanceTo(const CPoint & other) const{
	float dx = fabs(m_x - other.m_x);
	float dy = fabs(m_y - other.m_y);
	return sqrt(dx * dx + dy * dy);
}

