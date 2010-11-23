#ifndef CWORLD_H
#define CWORLD_H

#include <list>
class CCreature;
class CResource;

/** @brief World where civilization lives.

    This class can only be in one instance.
*/

class CWorld {
private:
    /** @brief Constructor. 
        @todo Implement.
    */
    CWorld();
	
	/** @brief Time to add on each update */
	static const int TIME_PER_UPDATE = 1;

	/** @brief Instance of the world */
	static CWorld * m_instance;

	/** @brief List of the creatures */
	std::list<CCreature*> m_creatures;

	/** @brief List of the resources */
	std::list<CResource*> m_resources;
public:
    /** @brief Painting function 
        @todo Implement.
    */
    static void paint();
    
    /** @brief Update the world.
        @todo Implement.
    
        This function should controls all processing of the world's elements
    */
    static void update();
    
    /** @brief Get instance of the world.
        @return Instance of the world.
        @todo Implement.
        
        The world's object will be created on the first call of this function.
    */
    static CWorld * instance();
};

#endif //CWORLD_H
