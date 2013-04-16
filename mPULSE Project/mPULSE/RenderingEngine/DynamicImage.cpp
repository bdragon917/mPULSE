#include <RenderingEngine/DynamicImage.h>


	DynamicImage::DynamicImage(float inx, float iny, float inz, float inWidth, float inHeight, int textureIndex, int inMode)
    {
        curPos.x = inx;
        curPos.y = iny;
        curPos.z = inz;

        tarPos.x = inx;
        tarPos.y = iny;
        tarPos.z = inz;

        width = inWidth;
        height = inHeight;
    
        tIndex = textureIndex;

        LINEAR_VELOCITY = 1.00f;
        THRESHOLD = 0.01f;

        mode = inMode;

        sleep = true;       //Sleep is true if curPos == tarPos
    }

    void DynamicImage::update()
    {
        


        if (!sleep)
        {
            NxVec3 towardsVector = tarPos - curPos;

            switch (mode)
            {
            case 0:     //Linear
                if (towardsVector.magnitude() < LINEAR_VELOCITY)
                {
                    curPos = tarPos;
                    sleep = true;
                }
                else
                {
                    towardsVector.normalize();
                    curPos = curPos + (towardsVector * LINEAR_VELOCITY);
                }
                break;


            case 1:     //Halfling
                if (towardsVector.magnitude() < THRESHOLD)
                {
                    curPos = tarPos;
                    sleep = true;
                }
                else
                {
                    curPos = curPos + (towardsVector * 0.033f);
                }
                break;

            }
        }
    }

    int DynamicImage::getTextureIndex()
    {
        return tIndex;
    }

    void DynamicImage::setMode(int inMode)
    {
        mode = inMode;
    }

    void DynamicImage::setLocation(float newX, float newY, float newZ)
    {
        curPos.x = newX;
        curPos.y = newY;
        curPos.z = newZ;
    }

    void DynamicImage::setTargetLocation(float newX, float newY, float newZ)
    {
        tarPos.x = newX;
        tarPos.y = newY;
        tarPos.z = newZ;
        sleep = false;
    }
    float DynamicImage::getX()
    {
        return curPos.x;
    }
    float DynamicImage::getY()
    {
        return curPos.y;
    }
    float DynamicImage::getZ()
    {
        return curPos.z;
    }

    NxVec3 DynamicImage::getCurPos()
    {
        return curPos;
    }

    float DynamicImage::getHeight()
    {
        return height;
    }

    float DynamicImage::getWidth()
    {
        return width;
    }