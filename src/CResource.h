#ifndef CRESOURCE_H
#define CRESOURCE_H

#include "CDrawable.h"

/** @brief Any resource that can bee needed by the creatures. */

class CResource : public CDrawable {
private:
    static const float DEFAULT_RESOURCE_RADIUS = 0.02;
    float m_amount;
public:
    /** @brief Constructor. Create new resource at the given center.
        @param center Center of the resource.
        @param amount Amount of the resources available
        @todo Implement.
    */
    CResource(CPoint & center, float amount);

    /** @brief Get amount of resources available in the given object.
        @return Amount of the resources.
        @todo Implement.
    */
    float amount() const;

    /** @brief Take amount of resources.    
        @return amount of the resources that was taken. 
        This will also remove this amount from the resource.
        @todo Implement.
        
        If resource has less amount than requested it will return only as 
        much resources as it has.
        */
    float take(float amount);

    /** @brief Painting function of the resource. */
    virtual void paint();
};

#endif //CRESOURCE_H
