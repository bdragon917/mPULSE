#pragma once
#include "../Input/XboxController.h"

class AI
{
public:
    AI(void);
    ~AI(void);

    XboxController getControl();
    void update();
};

