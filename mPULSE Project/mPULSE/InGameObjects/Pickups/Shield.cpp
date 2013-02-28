#include "Shield.h"


Shield::Shield(void)
{

}


Shield::~Shield(void)
{

}

Entity* Shield::use()
{
    printf("Shield Used \n");
    return new Entity;
}