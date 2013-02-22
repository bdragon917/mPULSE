#pragma once
#include "NxVec3.h"

class Particle {
public:
	Particle(float x, float y, float z);
    ~Particle();

    NxVec3 getLocation();
    bool isDead();

private:
    NxVec3 location;
	int timeTilDeath;
    int texture;
    int size;
};
