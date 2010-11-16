#ifndef CCREATURE_H
#define CCREATURE_H

class CCreature : public CDrawable {
public:
	CCreature(CTribe & tribe, CCreature & parent, const CPoint & pos);
	~CCreature();

	void attack(CCreature & other);
	void breed(CCreature & other);

	void paint();

	void live(int time);
	void move(float direction, float distance);
}

#endif //CCREATURE_H
