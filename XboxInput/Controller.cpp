#include "Controller.h"

Controller::Controller(int index)
{
	controllerIndex = index;
}

XINPUT_STATE Controller::getState()
{
    memset(&state,0,sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, &state);
	return state;
}

int Controller::getIndex()
{
	return controllerIndex;
}

bool Controller::isConnected()
{
	memset(&state,0,sizeof(XINPUT_STATE));
	DWORD status = XInputGetState(controllerIndex, &state);
	
	if(status == ERROR_SUCCESS)
		return true;
	else
		return false;
}

void Controller::vibrate(int leftMagnitutde,int rightMagnitude)
{
    //Create a Vibraton State
    XINPUT_VIBRATION vib;
    memset(&vib,0,sizeof(XINPUT_VIBRATION));
    
	//Set vibration values
    if (leftMagnitutde > MAX_VIB)
        vib.wLeftMotorSpeed = MAX_VIB;
    else if(leftMagnitutde < 0)
        vib.wLeftMotorSpeed = 0;
    else
        vib.wLeftMotorSpeed = leftMagnitutde;

    if(rightMagnitude > MAX_VIB)
        vib.wRightMotorSpeed = MAX_VIB;
    else if(rightMagnitude < 0)
        vib.wRightMotorSpeed = 0;
    else
        vib.wRightMotorSpeed = rightMagnitude;
    
	//Vibrate
    XInputSetState(controllerIndex, &vib);
}

Controller::analogInfo Controller::calculateAnalogInfo(XINPUT_STATE const &state, analogType stick)
{
    float deadZoneRadius = 8000;
    analogInfo info;
    float x = 0;
    float y = 0;

    if(stick == RIGHT_STICK)
    {
        x = state.Gamepad.sThumbRX;
        y = state.Gamepad.sThumbRY;
    }
    else if(stick == LEFT_STICK)
    {
        x = state.Gamepad.sThumbLX;
        y = state.Gamepad.sThumbLY;        
    }

    //determine how far the controller is pushed
    info.magnitude = sqrt(x*x + y*y);

    //determine the direction the controller is pushed
    info.x = x / info.magnitude;
    info.y = y / info.magnitude;
       
    //If controller is not in the deadzone
    if (info.magnitude > deadZoneRadius)         
    {
        info.magnitude -= deadZoneRadius; //Adjust magnitude to start at 0 when at edge of the dead zone

        if(info.magnitude > MAX_STICK_MAG) //Clamp magnitude to account for unsymmetric hardware feedback
            info.magnitude = MAX_STICK_MAG;
    }
    else
        info.magnitude = 0.0;
    
    return info;
}