#include "Controller.h"
#include <iostream>

int main(int argc, char **argv)
{
    const int MAX_PLAYERS = 4;
    int numPlayers = 0;
    int currentPackNum = 0;
    bool gameRunning = true;   

    Controller* players[MAX_PLAYERS];

	for(int i=0;i<MAX_PLAYERS;i++)
    {
        //Create controller objects.
        players[i] = new Controller(i);

        //Count the number of connected controllers.
        if(players[i]->isConnected())
            numPlayers++;
    }

    while (gameRunning) {

        for(int i=0;i<numPlayers;i++)
            if(players[i]->isConnected())
            {
                //Get the current controller state
                XINPUT_STATE state = players[i]->getState();

                if(players[i]->packetNum != state.dwPacketNumber)
                {                
                    players[i]->packetNum = state.dwPacketNumber;

                    //D-PAD Button checks
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
                        std::cout << "DPAD_UP" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
                        std::cout << "DPAD_DOWN" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
                        std::cout << "DPAD_LEFT" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
                        std::cout << "DPAD_RIGHT" << std::endl;
                             
                    //A,B,X,Y Button Checks
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
                        std::cout << "A" << std::endl;                    
                
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
                        std::cout << "B" << std::endl;
				
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
                        std::cout << "X" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
                        std::cout << "Y" << std::endl;

                    //Shoulder Button Checks
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
                        std::cout << "LEFT_SHOULDER" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
                        std::cout << "RIGHT_SHOULDER" << std::endl;

                    //Misc button checks
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
                        std::cout << "START" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
                        std::cout << "BACK" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
                        std::cout << "LEFT_THUMB" << std::endl;
                    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
                        std::cout << "RIGHT_THUMB" << std::endl;
                
				    Controller::analogInfo rightStick = players[i]->calculateAnalogInfo(state, Controller::LEFT_STICK);
                    Controller::analogInfo leftStick = players[i]->calculateAnalogInfo(state, Controller::RIGHT_STICK);

                    if(leftStick.magnitude > 0)
                        printf("Left Thumb x %f y %f mag %f\n",leftStick.x,leftStick.y,leftStick.magnitude);

                    if(rightStick.magnitude > 0)
                        printf("right Thumb x %f y %f mag %f\n",rightStick.x,rightStick.y,rightStick.magnitude);

                    if(state.Gamepad.bLeftTrigger > 0)
                        printf("left Trigger mag %d\n",state.Gamepad.bLeftTrigger);

                    if(state.Gamepad.bRightTrigger > 0)
                        printf("right Trigger mag %d\n",state.Gamepad.bRightTrigger);

                    //Vibrate the controller based on how much the triggers are pressed
                    players[i]->vibrate(
                        (int)(state.Gamepad.bLeftTrigger/255.0)*Controller::MAX_VIB,
                        (int)(state.Gamepad.bRightTrigger/255.0)*Controller::MAX_VIB);
                    
                }
            }
            else
                std::cout << "Player "<< i <<" disconnected. Please reconnect your controller" << std::endl;
        
    }
    return 0;
}