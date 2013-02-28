//Find angle between two vectors
/*
float xz = x*x + z*z, y11 = y1*y1, y12 = y1*y2, y22 = y2*y2;

float cosangle = (xz + y12) / sqrt((xz + y11) * (xz + y22));
float angle = acos(cosangle);
*/

#include "AI.h"

AI::AI(void)
{}

    AI::~AI(void)
    {}

    XboxController* AI::getControl()
    {
        return new XboxController(0);
    }

    void AI::update()
    {}