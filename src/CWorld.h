#ifndef CWORLD_H
#define CWORLD_H

/** @brief World where civilization lives.

    This class can only be in one instance.
*/

class CWorld {
private:
    /** @brief Constructor. 
        @todo Implement.
    */
    CWorld();
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
    CWorld * instance();
}

#endif //CWORLD_H
