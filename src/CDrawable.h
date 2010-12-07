#ifndef CDRAWABLE_H
#define CDRAWABLE_H

#include "CPoint.h"

/** @brief Base class for all objects that can be drawn on the screen */

class CDrawable {
public:
    /** @brief Constructor.
        @param center Center of the object.
        @param radius Radius of the object.
        @todo Implement.
    */
    CDrawable(const CPoint & center, float radius);

    /** @brief Get center of the object.
        @return Center of the object.
        @todo Implement.
    */
    CPoint center() const;
    
    /** @brief Get radius of the object.
        @return radius of the object.
        @todo Implement.
    */
    float radius() const;
    
    /** @brief Method is called to paint the object using OpenGL.
    
        This method should be reimplemented to get custom look of the object.
        @todo Implement.
    */
    virtual void paint();

    /** @brief Move center of the object.
        @param direction Direction to move in radians.
        @param distance Distance to move object in the given direction.
        @todo Implement.
    */
    virtual void move(float direction, float distance);

	/** @brief Load position in the tile matrix to the passed parameters
		@param x X coordinate of the tile
		@param y Y coordinate of the tile
	*/
	void loadTilePos(int & x, int & y) const;

	bool intersect(const CDrawable & other) const;

protected:
    /// Center of the object.
    CPoint m_center;
    
    /// Radius of the object.
    float m_radius;
};

#endif //CDRAWABLE_H
