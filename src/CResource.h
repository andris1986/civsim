#ifndef CRESOURCE_H
#define CRESOURCE_H

class CResource : public CDrawable {
	CResource(CPoint & center);

	float amount() const;

	/** @brief Take amount of resources */
	float take(float amount);

	void paint();
}

#endif CRESOURCE_H
