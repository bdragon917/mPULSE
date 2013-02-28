#include "MissileLauncher.h"


MissileLauncher::MissileLauncher(void)
{
}


MissileLauncher::~MissileLauncher(void)
{
}

Entity* MissileLauncher::use()
{
    printf("Missile Launcher Used \n");
    return new Entity();
}