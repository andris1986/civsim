#ifndef CPOINT_H
#define CPOINT_H

class CPoint {
    CPoint();
    CPoint(float x, float y);
    
    float setX(float x);
    float setY(float y);
    
    float moveTo(float x, float y);
	float move(float direction, float distance);

    float x() const;
    float y() const;
    
    float distanceTo(const CPoint & other) const;
};

#endif //CPOINT_H
