#include <AI/Waypoints.h>

Waypoints::Waypoints()
{

}

void Waypoints::loadWaypoints(std::string filename)
{
    	//char charArray[1024];
	    std::ifstream file;
        std::vector<std::string> modelFileNames;
        std::string tmpName;

	    file.open(filename);	

        if(file.is_open())
        {
	        while(!file.eof())
	        {
                //file.getline(charArray,1024);
                //tmpName = charArray;
                //modelFileNames.push_back(tmpName);
	        }
	        file.close();
        }
}

//to be worked
/**
void Waypoints::parseLine(std::string lineString, ObjModel* model)
    {	
        std::string heading = "";
	    unsigned int i = 0;
        unsigned int j = 0;
	    int startFlag = 0;
        char ch = '\0';
	    bool parsing = true;
        bool headingSeen = false;

        //Check if the line is empty or a comment
        if(lineString.size() <= 0 || lineString.at(0) == '#')
            return;

        //Parse out the heading from the current line.
        while((!headingSeen && parsing) && i < lineString.size())
        {
            ch = lineString.at(i);
            if(ch == ' ' || ch == '\t')
            {
                headingSeen = true;                
                heading = lineString.substr(0,i);
                startFlag = i;
            }

            if(ch == '\n' || ch == '\0')
                parsing = false;

            i++;
        }

        //Parse out the values associated with the headings and apply them to the model
        // geometric vertices
        
        if(heading.compare("v") == 0) 
        {
            std::vector<double> vertex = parseFloats(lineString,i);
            model->addVertexV(vertex);            
        }
        // texture vertices 
        else if(heading.compare("vt") == 0)
        {
            std::vector<double> vertex = parseFloats(lineString,i);
            model->addVertexVT(vertex);
        }
        // vertex normals
        else if(heading.compare("vn") == 0) 
        {
            std::vector<double> vertex = parseFloats(lineString,i);
            model->addVertexVN(vertex);
        }
        // parameter space vertices
       /* else if(heading.compare("vp") == 0) 
        { 

            
    }
    */
