#include "Barrier.h"


Barrier::Barrier(void)
{

}
Barrier::~Barrier(void)
{

}
Entity* Barrier::use()
{
    printf("Barrier Used\n");
    return new Entity();    
}