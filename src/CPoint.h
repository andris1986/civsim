#ifndef CPOINT_H
#define CPOINT_H

/** @brief Class for manipulating with point data. */

class CPoint {
public:
    /** @brief Constructor.

        Create point at 0;0 position.
        @todo Implement.
    */
    CPoint();
    
    /** @brief Constructor.
        @param x X coordinate of the point.
        @param y Y coordinate of the point.
        
        Create point at the given x, y position.
        @todo Implement.
    */    
    CPoint(float x, float y);
    
    /** @brief Set x value of the point.
        @param x New x value.
        @todo Implement.
    */
    void setX(float x);
    
    /** @brief Set y value of the point.
        @param y New y value.
        @todo Implement.
    */        
    void setY(float y);
    
    /** @brief Move point to the specified x, y position.
        @param x New x value.
        @param y New y value.
        
        This is equivalent to calling setX(); setY();.
        @todo Implement.
    */
    void moveTo(float x, float y);
    
    /** @brief Move the point.
        @param direction Direction in radians.
        @param distance Distance to move.
        @todo Implement.
    */
    void move(float direction, float distance);

    /** @brief Get current x value.
        @return X coordinate of the point.
        @todo Implement.
    */
    float x() const;
    
    /** @brief Get current y value.
        @return Y coordinate of the point.
        @todo Implement.
    */
    float y() const;
    
    /** @brief Distance from one point to another.
        @param other Point to measure distance to.
        @return Distance to the point.
        @todo Implement.
    */
    float distanceTo(const CPoint & other) const;
};

#endif //CPOINT_H
