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

class ProfileState : public GameState
{
public:
    static ProfileState* getInstance();
	void initialize();
    void update(float dt);
    void render();
    bool handleKeyboardMouseEvents(SDL_Event &KeyboardMouseEvents);
    void handleXboxEvents(int player,XboxController* state);

private:
    ProfileState();

    ProfileScreenInfo psi;

	unsigned PROFILE_FRAME_SIZE;
	int WAIT_TIME;

    bool lockControls;
    bool goBack;

    PhysicsEngine* physicsEngine;
    RenderingEngine* renderingEngine;
    SoundEngine* soundEngine;
    GameVariables* gameVariables;

    Clock clock;

    void upPressed();
    void downPressed();
    void selectPressed();
    void backPressed();

    float myDt; //hack for update

    int currentSelected;
    int maxSelected;
    int currentFrame; //Used to remember which range of profiles to display

    //xbox controller variables
    
    bool buttonPressed;
    unsigned prevTime;


};