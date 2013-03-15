#include <InGameObjects/Track.h>

Track::Track(std::string infoFilename, Entity* trackEntity)
{
    loadTrackInfo(infoFilename);
    entity = trackEntity;
}

std::string Track::removeFilePath(std::string line)
{
    unsigned int i = 0;
    int j = 0;

    char ch = '\0';
        
    while(i < line.size())
    {
        ch = line.at(i++);
        if(ch == '\\')
            j=i;
    }

    return line.substr(j);
}

void Track::loadTrackInfo(std::string filename)
{
        
    char charArray[1024];
    std::string tmpLine = "";
    std::ifstream file;
    trackName = removeFilePath(filename);
	file.open(filename);	
    if(file.is_open())
    {
	    while(!file.eof())
	    {
            //Read a line
            file.getline(charArray,1024);
            tmpLine = charArray;	    		

            //*************PARSE OUT THE HEADING************//
            std::string heading = "";
	        unsigned int i = 0;
            unsigned int j = 0;
	        int startFlag = 0;
            char ch = '\0';
	        bool parsing = true;
            bool headingSeen = false;

            //Check if the line is empty or a comment
            if(tmpLine.size() <= 0 || tmpLine.at(0) == '#')
                continue;

            //Parse out the heading from the current line.
            while((!headingSeen && parsing) && i < tmpLine.size())
            {
                ch = tmpLine.at(i);
                if(ch == ' ' || ch == '\t')
                {
                    headingSeen = true;                
                    heading = tmpLine.substr(0,i);
                    startFlag = i;
                }

                if(ch == '\n' || ch == '\0')
                    parsing = false;

                i++;
            }
            Waypoint::TYPE type = stringToType(heading);
                
            //********PARSE OUT THE DATA********//  
            if (type != Waypoint::INVALID_TYPE)
            {
    
                Waypoint* wp = new Waypoint();
                wp->type = type;

				NxVec3 col0 = NxVec3(0,0,0);
				NxVec3 col1 = NxVec3(0,0,0);
				NxVec3 col2 = NxVec3(0,0,0);

                bool startSeen = true;
                startFlag = i;
				/*
                while((parsing && i < tmpLine.size()) && j < 8)
	            {
                    ch = tmpLine.at(i);
                    if((ch == ' ' || ch == '\t') && startSeen)
                    {
                        if (j == 0)
                            wp->pos.x = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 1)
                            wp->pos.y = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 2)
                            wp->pos.z = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 3)
                            wp->ori.x = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 4)
                            wp->ori.y = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 5)
                            wp->ori.z = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 6)
                            wp->id = static_cast<int>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 7)
                            wp->nextId = static_cast<int>(atof(tmpLine.substr(startFlag,i).data()));

                        j++;
                        startSeen = false;
                    }
                    else if ((ch != ' ' && ch != '\t') && !startSeen)
                    {
                        startSeen = true;
                        startFlag = i;
                    }

                    i++;
	            }
				*/
				while((parsing && i < tmpLine.size()) && j < 14)
	            {
                    ch = tmpLine.at(i);
                    if((ch == ' ' || ch == '\t') && startSeen)
                    {
                        if (j == 0)
                            wp->pos.x = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 1)
                            wp->pos.y = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 2)
                            wp->pos.z = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 3)
                            col0.x = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 4)
                            col0.y = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 5)
                            col0.z = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
						else if(j == 6)
                            col1.x = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 7)
                            col1.y = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 8)
                            col1.z = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
						else if(j == 9)
                            col2.x = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 10)
                            col2.y = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 11)
                            col2.z = static_cast<float>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 12)
                            wp->id = static_cast<int>(atof(tmpLine.substr(startFlag,i).data()));
                        else if(j == 13)
                            wp->nextId = static_cast<int>(atof(tmpLine.substr(startFlag,i).data()));

                        j++;
                        startSeen = false;
                    }
                    else if ((ch != ' ' && ch != '\t') && !startSeen)
                    {
                        startSeen = true;
                        startFlag = i;
                    }

                    i++;
	            }
                if(startSeen)
                {
                    if(j == 13)
                        wp->nextId = static_cast<int>(atof(tmpLine.substr(startFlag,i).data()));
                }

				wp->ori.setColumn(0, col0);
				wp->ori.setColumn(1, col1);
				wp->ori.setColumn(2, col2);

                addWaypoint(wp);
            }
        }
	    file.close();                
    }
    else
    {printf("Track checkpoints didn't open, can't find maybe??\n"); }
    finalizeWaypoints();        
}

NxActor* Track::getActor()
{
    return entity->getActor();
}

Entity* Track::getEntity()
{
    return entity;
}

std::string Track::getName()
{
    return trackName;
}

void Track::addWaypoint(Waypoint* wp)
{
    waypoints.push_back(wp);
}
/*
void Track::addWaypoint(float xPos, float yPos, float zPos,float xOri, float yOri,float zOri,int tmpId,int tmpNext,Waypoint::TYPE type)
{
    Waypoint* w = new Waypoint();
    w->pos.x = xPos;
    w->pos.y = yPos;
    w->pos.z = zPos;
    w->ori.x = xOri;
    w->ori.y = yOri;
    w->ori.z = zOri;
    w->id = tmpId;
    w->nextId = tmpNext;
    w->type = type;

    waypoints.push_back(w);
}
*/
std::vector<Waypoint*>* Track::getWaypoints()
{
    return &waypoints;
}

std::vector<Waypoint*>* Track::getWaypointsOfType(Waypoint::TYPE type)
{
    return NULL;
}

Waypoint::TYPE Track::stringToType(std::string typeString)
{
    if(typeString.compare("START") == 0)
        return Waypoint::START;
    else if(typeString.compare("FINISH") == 0)
        return Waypoint::FINISH;
    else if(typeString.compare("WAYPOINT") == 0)
        return Waypoint::WAYPOINT;
    else if(typeString.compare("CAR_SPAWN") == 0)
        return Waypoint::CAR_SPAWN;
    else if(typeString.compare("PICKUP_SPAWN") == 0)
        return Waypoint::PICKUP_SPAWN;
    else
        return Waypoint::INVALID_TYPE;
}

void Track::finalizeWaypoints()
{
    waypoints.shrink_to_fit();
    if(waypoints.size()>0)
    {
		Waypoint* lastWaypoint = waypoints[0];
        for(unsigned i=1;i<waypoints.size();i++)
        {
			if(waypoints[i]->type == Waypoint::WAYPOINT)
			{
				lastWaypoint = waypoints[i];
				waypoints[i-1]->nextWaypoint = lastWaypoint;
			}
        }
        lastWaypoint->nextWaypoint = waypoints[0];
		lastWaypoint->nextId = waypoints[0]->id;
    }
}

Waypoint* Track::getFirst()
{
    return waypoints[0];
}
Waypoint* Track::getWaypoint(int index)
{
    return waypoints[index];
}
