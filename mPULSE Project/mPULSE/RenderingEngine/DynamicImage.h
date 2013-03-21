#pragma once
#include "NxVec3.h"


class DynamicImage {
public:
	DynamicImage(float x, float y, float z, float width, float height, int textureIndex, int mode);

    void update();
    void setTargetLocation(float newX, float newY, float newZ);
    float getX();
    float getY();
    float getZ();

    NxVec3 getCurPos();

private:
    NxVec3 curPos;
    NxVec3 tarPos;


    float width;
    float height;
    
    int tIndex;

    int mode;

    bool sleep;
};
