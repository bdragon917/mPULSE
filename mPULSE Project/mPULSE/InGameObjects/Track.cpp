#include "Track.h"

    Track::Track(std::string infoFilename, Entity* trackEntity)
    {
        loadTrackInfo(infoFilename);
        entity = trackEntity;
    }

    Track::Track()
    {

    }

    void Track::loadTrackInfo(std::string filename)
    {
        
        char charArray[1024];
        std::string tmpLine = "";
        std::ifstream file;

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
                    return;

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

                    bool startSeen = true;
                    startFlag = i;
                    while((parsing && i < tmpLine.size()) && j < 3)
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
                        if (j == 0)
                            wp->pos.x = static_cast<float>(atof(tmpLine.substr(startFlag).data()));
                        else if(j == 1)
                            wp->pos.y = static_cast<float>(atof(tmpLine.substr(startFlag).data()));
                        else if(j == 2)
                            wp->pos.z = static_cast<float>(atof(tmpLine.substr(startFlag).data()));
                    }

                    addWaypoint(wp);
                }
            }
	        file.close();                
        }
        else
        {printf("Track checkpoints didn't open, can't find maybe??\n"); }
        waypoints.shrink_to_fit();
    }

    NxActor* Track::getActor()
    {
        return entity->getActor();
    }

    Entity* Track::getEntity()
    {
        return entity;
    }

    void Track::addWaypoint(Waypoint* wp)
    {
        waypoints.push_back(wp);
    }

    void Track::addWaypoint(float x,float y,float z,Waypoint::TYPE type)
    {
        Waypoint* w = new Waypoint();
        w->pos.x = x;
        w->pos.y = y;
        w->pos.z = z;
        w->type = type;

        waypoints.push_back(w);
    }

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
        else if(typeString.compare("ITEM_SPAWN") == 0)
            return Waypoint::ITEM_SPAWN;
        else
            return Waypoint::INVALID_TYPE;
    }