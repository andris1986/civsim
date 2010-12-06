#include <math.h>
#include "CPoint.h"

CPoint::CPoint() {
	m_x = 0.0;
	m_y = 0.0;
	m_z = 0.0;
}

CPoint::CPoint(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

void CPoint::setX(float x) {
	m_x = x;
}

void CPoint::setY(float y) {
	m_y = y;
}

void CPoint::setZ(float z) {
	m_z = z;
}

void CPoint::moveTo(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
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

float CPoint::z() const {
	return m_z;
}

float CPoint::distanceTo(const CPoint & other) const{
	float dx = fabs(m_x - other.m_x);
	float dy = fabs(m_y - other.m_y);
	float dz = fabs(m_z - other.m_z);
	float xy = sqrt(dx * dx + dy * dy);
	return sqrt(xy * xy + dz * dz);
}

