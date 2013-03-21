#pragma once
#include <string>

class ProfileScreenInfo {
public:
	bool isActive;
    std::string title;
    std::string profilesOnScreen[6];
    int selectedItem;

    int selectedTextTexture;
    int selectedButtonTexture;
    int buttonTexture;

};
