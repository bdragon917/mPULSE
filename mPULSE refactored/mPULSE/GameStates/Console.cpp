#include "Console.h"


Console::Console()
{
    
}

void Console::propragateMsg()
{
  
        consoleOut[4] = consoleOut[3];
        consoleOut[3] = consoleOut[2];
        consoleOut[2] = consoleOut[1];
        consoleOut[1] = consoleOut[0];
        consoleOut[0] = consoleString;

    consoleString = "";
}

void Console::goUp()
{
        consoleString = consoleOut[0];
}
