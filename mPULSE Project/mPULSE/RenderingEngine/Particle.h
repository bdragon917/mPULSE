#pragma once
#include "NxVec3.h"

class Particle {
public:
	Particle(float x, float y, float z);
    ~Particle();

    NxVec3 getLocation();
    void setVelocity(NxVec3 newVel);
    bool isDead();
    void Age();
    void Move();

    int timeTilDeath;

private:
    NxVec3 location;
    NxVec3 velocity;
    int texture;
    int size;
};
