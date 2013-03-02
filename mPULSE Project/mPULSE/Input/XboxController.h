#pragma once
#include <Windows.h>
#include <Xinput.h>
#include <math.h>

class XboxController
{
public:
    typedef struct analogInfo
    {
        float magnitude;
        float x;
        float y;
    };

    enum analogType { RIGHT_STICK, LEFT_STICK };

    /*
    * This constructor takes in an index from value 0 to 3 to
    * be used as the controllers index.
    */
	XboxController(int index);

    /*
    *getState: This method gets the current state of the controller.
    *param: state: A pointer to a state variable to fill out with the current controller state
    *return: bool: An bool signifying a change of the controllers state.
    */
	bool getState(XINPUT_STATE* state);

    /*
    *getIndex: This method returns the controllers index as an integer.
    *return: int: An integer representing the controllers number.
    */
	int getIndex();

    /*
    *isConnected: This method checks if the controller is connected or not.
    *return: bool: true if connected, false if not.
    */
	bool isConnected();

    /*
    *vibrate: This method is used to set the controllers vibration state with 
    * integers from 0 to 65535.
    *param: leftMagnitude: A value for how much the left rumble pack will vibrate
    *param: rightMagnitude: A value for how much the right rumble pack will vibrate
    */
	void vibrate(int leftMagnitutde,int rightMagnitude);
	
    /*
    *calculateAnalogInfo: This method takes in the controller state and the stick type
    *and returns the values of the stick info.
    *param: state: The controller state.
    *param: stick: An enumerated type indicating which stick to calculate for.
    */
    analogInfo calculateAnalogInfo(XINPUT_STATE const &state, analogType stick);
    void update();

    void initializeVariables();

    static const int MAX_VIB = 65535;
    static const int MAX_STICK_MAG = 24000; 
    static const int MAX_TRIGGER_MAG = 255;    
    bool a,b,x,y,rb,lb,rs,ls,start,back,dpadUp,dpadLeft,dpadRight,dpadDown;
    analogInfo leftStick, rightStick;
    int lTrigger, rTrigger;
private:    
    XINPUT_STATE state;
    int controllerIndex;
    int packetNum;
  
};