#pragma once

#define NOMINMAX
#include <vector>
#include <map>
#include <Util/Clock.h>

#include <GameStates/GameState.h>
#include <RenderingEngine/RenderingEngine.h>
#include <PhysicsEngine/PhysicsEngine.h>
#include <SoundEngine/SoundEngine.h>
#include <InGameObjects/Entities/Entity.h>
#include <InGameObjects/Entities/RenderableComponent.h>
#include <GameStates/GameVariables.h>
#include <RenderingEngine\ShopScreenInfo.h>

class ShopState : public GameState
{

    struct shopItem
	{
		int itemIndex;
		int price;
        std::string name;
	};


public:
    static ShopState* getInstance();
	void initialize();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);


private:
    ShopState();

    void initializeInventory();
    void initializePaintJob(int shipModel);

    std::vector<shopItem*> availableShips;
    std::vector<shopItem*> availablePaints;
    std::vector<shopItem*> availableUpgrades;

    ShopScreenInfo ssi;
    DynamicImage* mechanicGirl;
    DynamicImage* painterGirl;
    DynamicImage* subMenu;

    bool lockControls;
    bool goBack;

    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    SoundEngine* soundEngine;
    GameVariables* gameVariables;

    Clock clock;

    void rightPressed();
    void leftPressed();
    void upPressed();
    void downPressed();
    void selectPressed();


    void backPressed();

    void enterMechanic();
    void enterPainter();

    float myDt; //hack for update

    int currentSelectedCategory;
    int currentSelectedItem;
    int MAX_CATEGORY_SELECTED;
    int MAX_ITEM_SELECTED;

	bool inSubmenu;

    //xbox controller variables
    int WAIT_TIME;
    bool buttonPressed;
    unsigned prevTime;

	//Base Prices
	int BASE_PICKUP_UPGRADE;
};