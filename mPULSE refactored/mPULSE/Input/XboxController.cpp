#include "XboxController.h"

XboxController::XboxController(int index)
{
	controllerIndex = index;
}

bool XboxController::getState(XINPUT_STATE* tmpState)
{    
    memset(tmpState,0,sizeof(XINPUT_STATE));
	XInputGetState(controllerIndex, tmpState);

    if(packetNum != tmpState->dwPacketNumber)
    {
        packetNum = tmpState->dwPacketNumber;
	    return true;
    }
    else
        return false;
}

int XboxController::getIndex()
{
	return controllerIndex;
}

bool XboxController::isConnected()
{
	memset(&state,0,sizeof(XINPUT_STATE));
	DWORD status = XInputGetState(controllerIndex, &state);
	
	if(status == ERROR_SUCCESS)
		return true;
	else
		return false;
}

void XboxController::vibrate(int leftMagnitutde,int rightMagnitude)
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

XboxController::analogInfo XboxController::calculateAnalogInfo(XINPUT_STATE const &state, analogType stick)
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

void XboxController::update()
{    
    if(getState(&state))
    {                
        //D-PAD Button checks
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
            dpadUp = true;
        else
            dpadUp = false;

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
            dpadDown = true;
        else
            dpadDown = false;
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
            dpadLeft = true;
        else
            dpadLeft = false;
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
            dpadRight = true;
        else
            dpadRight = false;
                             
        //A,B,X,Y Button Checks
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
            a = true;
        else
            a = false;                 
                
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
            b = true;
        else
            b = false;                 
				
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
            x = true;
        else
            x = false;                 

        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
            y = true;
        else
            y = false;                 

        //Shoulder Button Checks
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
            lb = true;
        else
            lb = false;                 
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
            rb = true;
        else
            rb = false;                 

        //Misc button checks
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
            start = true;
        else
            start = false;                 
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
            back = true;
        else
            back = false;                 
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
            ls = true;
        else
            ls = false;                 
        if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
            rs = true;
        else
            rs = false;                 
                
        rightStick = calculateAnalogInfo(state, LEFT_STICK);
        leftStick = calculateAnalogInfo(state, RIGHT_STICK);

        if(leftStick.magnitude > 0)
            printf("Left Thumb x %f y %f mag %f\n",leftStick.x,leftStick.y,leftStick.magnitude);

        if(rightStick.magnitude > 0)
            printf("right Thumb x %f y %f mag %f\n",rightStick.x,rightStick.y,rightStick.magnitude);

        lTrigger = state.Gamepad.bLeftTrigger;
        rTrigger = state.Gamepad.bRightTrigger;                    
    }
}