#include <RenderingEngine/Particle.h>

Particle::Particle(float x, float y, float z)
{
    location.x = x;
    location.y = y;
    location.z = z;
    velocity.x = 0;
    velocity.y = 0;
    velocity.z = 0;
    timeTilDeath = 20;
}
Particle::~Particle()
{

}

void Particle::setVelocity(NxVec3 newVel)
{
    velocity = newVel;
}
NxVec3 Particle::getLocation()
{
    return location;
    //timeTilDeath = timeTilDeath - 1;
}

void Particle::Move()
{
    location = location + velocity;
}

bool Particle::isDead()
{
    if (timeTilDeath < 0)
    {return true;}
    else
    {return false;}
}

void Particle::Age()
{
    timeTilDeath  = timeTilDeath - 1;
}
