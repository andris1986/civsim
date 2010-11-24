#include <stdlib.h>
#include "CWorld.h"

int main(int argc, char ** argv) {
    CWorld::init(argc, argv);
    CWorld::instance()->run();
    return EXIT_SUCCESS;
}

