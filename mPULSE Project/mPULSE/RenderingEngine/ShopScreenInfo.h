#pragma once
#include <string>
#include <vector>
#include <RenderingEngine\DynamicImage.h>

class ShopScreenInfo {
public:
	bool isActive;

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


    int selectedMenuIndex;
    int selectedSelectorIndex;


};
