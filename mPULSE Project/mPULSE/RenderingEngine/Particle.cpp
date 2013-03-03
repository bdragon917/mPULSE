#include <RenderingEngine/Particle.h>

Particle::Particle(float x, float y, float z)
{
    location.x = x;
    location.y = y;
    location.z = z;
    timeTilDeath = 20;
}
Particle::~Particle()
{

}

NxVec3 Particle::getLocation()
{
    return location;
    timeTilDeath = timeTilDeath - 1;
}

bool Particle::isDead()
{
    if (timeTilDeath < 0)
    {return true;}
    else
    {return false;}
}
