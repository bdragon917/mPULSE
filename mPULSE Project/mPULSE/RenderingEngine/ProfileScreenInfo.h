#pragma once
#include <string>

class ProfileScreenInfo {
public:
	bool isActive;
    std::string title;
    std::string profilesOnScreen[8];
    int selectedItem;
	int numProfiles;

    int selectedTextTexture;
    int selectedButtonTexture;
    int buttonTexture;

	bool canScrollUp;
	bool canScrollDown;

};
