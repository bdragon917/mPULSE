#include "Console.h"


Console::Console()
{
    logPointer = 0;
}


//void Console::addCommand(std::string cmdStr, int(*)(int aFunc))
///{
//    commands[cmdStr] = int(*) aFunc;
//}

void Console::propragateMsg(std::string feedbackMsg)
{
  
        consoleOut[4] = consoleOut[3];
        consoleOut[3] = consoleOut[2];
        consoleOut[2] = consoleOut[1];
        consoleOut[1] = consoleOut[0];
        consoleOut[0] = feedbackMsg;

        if (consoleString != "")
            log.push_back(consoleString);

        log.push_back(feedbackMsg);

    consoleString = "";

    if (log.size() != 0)
    {logPointer = log.size() - 1;}
    //appendExcessLog();
}

void Console::propragateMsg()
{
  
        consoleOut[4] = consoleOut[3];
        consoleOut[3] = consoleOut[2];
        consoleOut[2] = consoleOut[1];
        consoleOut[1] = consoleOut[0];
        consoleOut[0] = consoleString;

        log.push_back(consoleString);

    consoleString = "";

    if (log.size() != 0)
    {logPointer = log.size() - 1;}
    //appendExcessLog();
}

void Console::goUp()
{
    printf ("logSize:%i pointer:%i", log.size(), logPointer);
    if (log.size() != 0)
    {
        if (!(log.at(logPointer).empty()))      //check to see if valid?
            consoleString = log.at(logPointer);
        
        if ( (logPointer - 1) >= 0 )
        {logPointer = logPointer - 1;}
        else
        {logPointer = log.size() - 1;}
    }
}


void Console::appendExcessLog()
{
    //if log is bigger than x, take half of it and dump to file

    const int AMT = 5;  //number of elements to dump/truncate

    if (log.size() > 20)
    {

        std::ofstream out;
        out.open( "log.txt", std::ios_base::app );
        if( !out )
        {
           printf( "Couldn't open file.\n");
        }
        else
        {
            for (int i=0; i < AMT; i++)
            {
                out << log.at(i) + char(10) + char(13);
            }

            
            log.erase(log.begin(), log.begin()+AMT );
        }
        out.close();
    }
}

void Console::appendLog()
{
    //if log is bigger than x, take half of it and dump to file

    const int AMT = 5;  //number of elements to dump/truncate

    if (log.size() > 20)
    {

        std::ofstream out;
        out.open( "log.txt", std::ios_base::app );
        if( !out )
        {
           printf( "Couldn't open file.\n");
        }
        else
        {
            if (log.size() != 0)
            {
                for (int i=0; i < log.size(); i++)              //Untested
                {
                    out << log.at(i) + char(10) + char(13);
                }
            }
        }
        out.close();
    }
}