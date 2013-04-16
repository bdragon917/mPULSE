#pragma once
#include <string>
#include <vector>
#include <RenderingEngine\DynamicImage.h>

class ShopScreenInfo {
public:

    std::vector <DynamicImage*> di;

    typedef enum {
        MAIN,
        SHIP,
        SHIP_CONFIRM,
        PAINT,
        PAINT_CONFIRM,
        UPGRADES,
        UPGRADES_CONFIRM,
    } StateType;

    std::string playerName;
    int playerObs;

    bool inSubmenu;

    int selectedMenuIndex;
    int selectedItemIndex;

    float obsCost;

    int newShipTexture;     //Need to tell which texture to use for new models;


};
