#ifndef CPOINT_H
#define CPOINT_H

/** @brief Class for manipulating with point data. */

class CPoint {
public:
    /** @brief Constructor.

        Create point at 0;0 position.
    */
    CPoint();
    
    /** @brief Constructor.
        @param x X coordinate of the point.
        @param y Y coordinate of the point.
		@param z Z coordinate of the point
        
        Create point at the given x, y position.
    */    
    CPoint(float x, float y, float z);
    
    /** @brief Set x value of the point.
        @param x New x value.
    */
    void setX(float x);
    
    /** @brief Set y value of the point.
        @param y New y value.
    */        
    void setY(float y);
    
	void setZ(float z);

    /** @brief Move point to the specified x, y position.
        @param x New x value.
        @param y New y value.
        
        This is equivalent to calling setX(); setY();.
    */
    void moveTo(float x, float y, float z);
    
    /** @brief Move the point.
        @param direction Direction in radians.
        @param distance Distance to move.
    */
    void move(float direction, float distance);

    /** @brief Get current x value.
        @return X coordinate of the point.
    */
    float x() const;
    
    /** @brief Get current y value.
        @return Y coordinate of the point.
    */
    float y() const;

	float z() const;
    
    /** @brief Distance from one point to another.
        @param other Point to measure distance to.
        @return Distance to the point.
    */
    float distanceTo(const CPoint & other) const;

	float angleTo(const CPoint & other) const;
	
private:
	float m_x;
	float m_y;
	float m_z;
};

#endif //CPOINT_H
