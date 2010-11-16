#ifndef CDRAWABLE_H
#define CDRAWABLE_H

class CDrawable {
public:
	CDrawable(const CPoint & center, float radius);

	CPoint center() const;
	float radius() const;
	virtual void paint();

private:
	CPoint m_center;
	float m_radius;
};

#endif //CDRAWABLE_H
