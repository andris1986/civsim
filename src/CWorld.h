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
    /** @brief Painting function */
    static void paint();
    
    /** @brief Update the world.
        @todo comment on v parameter
    
        This function should controls all processing of the world's elements
    */
    static void update(int v);
    
    /** @brief Get instance of the world.
        @return Instance of the world.
        
        The world's object will be created on the first call of this function.
    */
    static CWorld * instance();

    /** @brief Initialize the world 
        @param argc Number or arguments
        @param argv List of the arguments
    */
    static void init(int argc, char ** argv);

    /** @brief Add new creature
        @param c Creature to add
    */
    void addCreature(CCreature * c);

    /** @brief Remove a creature
        @param c Creature to remove
    */
    void removeCreature(CCreature * c);

    /** @brief Add new resource
        @param r Resource to add
    */
    void addResource(CResource * r);

    /** @brief Remove a resource
        @param r Resource to remove
    */
    void removeResource(CResource * r);

    /** @brief Main loop of the application */
    void run();
};

#endif //CWORLD_H
