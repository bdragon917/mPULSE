#include "ModelManager.h"
        
    ModelManager::ModelManager()
    {
        lineNum = 0;
        currentModelNum = 0;
        MODEL_LIST_FILENAME = "ModelList.txt";
    }

    void ModelManager::loadModelsFromList(std::string modelListFilename)
    {
	    char charArray[1024];
	    std::ifstream file;
        std::vector<std::string> modelFileNames;
        std::string tmpName;

	    file.open(modelListFilename);	
	    while(!file.eof())
	    {
            file.getline(charArray,1024);
            tmpName = charArray;
            modelFileNames.push_back(tmpName);
	    }
	    file.close();

        for(int i=0;i<modelFileNames.size();i++)
            LoadModel(modelFileNames[i]);
    }

    int ModelManager::LoadModel(std::string fileName)
    {
        char charArray[1024];
        std::string tmpLine = "";
        std::ifstream file;
        lineNum = 0;

        models.push_back(new ObjModel(currentModelNum));

	    file.open(fileName);	
	    while(!file.eof())
	    {
            file.getline(charArray,1024);
            lineNum++;
            tmpLine = charArray;
		    parseLine(tmpLine,models[currentModelNum]);		    		
	    }
	    file.close();                
        models[currentModelNum]->finalize();
        return currentModelNum++;
    }

    ObjModel* ModelManager::getModel(int index)
    {
        return models[index];
    }

    void ModelManager::parseLine(std::string lineString, ObjModel* model)
    {	
        std::string heading = "";
	    int i = 0;
        int j = 0;
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

            if(ch == '\n' | ch == '\0')
                parsing = false;

            i++;
        }

        //Parse out the values associated with the headings and apply them to the model
        // geometric vertices
        
        if(heading.compare("v") == 0) 
        {
            std::vector<float> vertex = parseFloats(lineString,i);
            model->addVertexV(vertex);            
        }
        // texture vertices 
        else if(heading.compare("vt") == 0)
        {
            std::vector<float> vertex = parseFloats(lineString,i);
            model->addVertexVT(vertex);
        }
        // vertex normals
        else if(heading.compare("vn") == 0) 
        {
            std::vector<float> vertex = parseFloats(lineString,i);
            model->addVertexVN(vertex);
        }
        // parameter space vertices
       /* else if(heading.compare("vp") == 0) 
        { 

        }
        //********************* Free-form curve/surface attributes************************

        // rational or non-rational forms of curve or surface type:
        // basis matrix, Bezier, B-spline, Cardinal, Taylor
        else if(heading.compare("cstype") == 0) 
        {
        
        }
        // degree
        else if(heading.compare("deg") == 0) 
        { 
        
        }
        // basis matrix
        else if(heading.compare("bmat") == 0) 
        { 
        
        }
        // step size
        else if(heading.compare("step") == 0) 
        { 
        
        }

        //************************Elements***************************
        // point
        else if(heading.compare("p") == 0) 
        { 
        
        }
        // line
        else if(heading.compare("l") == 0)
        { 
        
        }*/
        // face
        else if(heading.compare("f") == 0) 
        { 
            model->addFaceF(parseFaceElements(lineString,i));
        }/*
        // curve 
        else if(heading.compare("curv") == 0)
        {
        
        }
        // 2D curve
        else if(heading.compare("curv2") == 0) 
        { 
        
        }
        // surface
        else if(heading.compare("surf") == 0) 
        { 
        
        }

        //**********************Free-form curve/surface body statements*********************
        // parameter values
        else if(heading.compare("parm") == 0) 
        { 
        
        }
        // outer trimming loop 
        else if(heading.compare("trim") == 0) 
        { 
        
        }
        // inner trimming loop 
        else if(heading.compare("hole") == 0) 
        { 
        
        }
        // special curve
        else if(heading.compare("scrv") == 0) 
        { 
        
        }
        // special point
        else if(heading.compare("sp") == 0) 
        {
        
        }
        // end statement
        else if(heading.compare("end") == 0) 
        { 
        
        }

        //Connectivity between free-form surfaces
        // connect
        else if(heading.compare("con") == 0) 
        { 
        
        }

        //**************Grouping******************
        // group name
        else if(heading.compare("g") == 0)
        { 
        
        }
        // smoothing group
        else if(heading.compare("s") == 0) 
        {
        
        }
        // merging group
        else if(heading.compare("mg") == 0) 
        { 
        
        }
        // object name
        else if(heading.compare("o") == 0) 
        { 
        
        }

        //*****************Display/render attributes*************
        // bevel interpolation
        else if(heading.compare("bevel") == 0) 
        { 
        
        }
        // color interpolation
        else if(heading.compare("c_interp") == 0) 
        {
        
        }
        // dissolve interpolation
        else if(heading.compare("d_interp") == 0) 
        { 
        
        }
        // level of detail
        else if(heading.compare("lod") == 0) 
        {
        
        }
        // material name
        else if(heading.compare("usemtl") == 0) 
        { 
        
        }
        // material library
        else if(heading.compare("mtllib") == 0) 
        {
        
        }
        // shadow casting
        else if(heading.compare("shadow_obj") == 0) 
        { 
        
        }
        // ray tracing
        else if(heading.compare("trace_obj") == 0) 
        { 
        
        }
        // curve approximation technique
        else if(heading.compare("ctech") == 0) 
        { 
        
        }
        // surface approximation technique
        else if(heading.compare("stech") == 0) 
        { 
        
        }*/
        else 
            printf("%s not defined. Unsupported or bad format. Line:   %d\n",lineString.data(),lineNum);
            
    }

    std::vector<float> ModelManager::parseFloats(std::string line, int startIndex)
    {
        int i = startIndex;
        int j = 0;
        int startFlag = startIndex;
        char ch = '\0';
        bool parsing = true;
        bool startSeen = false;
        bool exponentSeen = false;         

        std::vector<float> vertex(3);
        while((parsing || j < 4) && i < line.size())
	    {
            ch = line.at(i);
		    if((ch == ' ' || ch == '\t') || ch == 'e')
            {
                if(startSeen && ch != 'e' && !exponentSeen)                    
                    vertex[j++] = atof(line.substr(startFlag,i-startFlag).data());
                else if((startSeen && ch == 'e') && !exponentSeen)
                {
                    vertex[j] = atof(line.substr(startFlag,i-startFlag).data());
                    exponentSeen = true;
                }
                else if(startSeen && exponentSeen)
                {
                    vertex[j] = vertex[j] * pow(10,atof(line.substr(startFlag,i-startFlag).data()));  
                    j++;
                    exponentSeen = false;
                }

                startFlag = i+1;
            }            
            else if(!startSeen)
                startSeen = true;
		        
            if(ch == '\n' || ch == '\0')                  
                parsing = false;

            i++;
	    }
        if(startSeen && !exponentSeen)
            vertex[j] = atof(line.substr(startFlag,i-startFlag).data());
        else if(startSeen && exponentSeen)
            vertex[j] = vertex[j] * pow(10,atof(line.substr(startFlag,i-startFlag).data())); 

        return vertex; 
    }

    std::vector<std::vector<int>> ModelManager::parseFaceElements(std::string line, int startIndex)
    {
        int i = startIndex;
        int j = 0;
        int startFlag = startIndex;
        char ch = '\0';
        bool parsing = true;
        bool startSeen = false;

        std::vector<std::vector<int>> faceElements;
        std::vector<int> elements;
        while(parsing && i < line.size())
	    {
            ch = line.at(i);
		    if(ch == ' ' || ch == '\t' || ch == '/')
            {
                if(startSeen && ch == '/')                    
                {
                   elements.push_back(atoi(line.substr(startFlag,i-startFlag).data()));
                }
                else if(startSeen)
                {
                    elements.push_back(atoi(line.substr(startFlag,i-startFlag).data()));
                    faceElements.push_back(elements);
                    elements.clear();
                    startSeen = false;
                }
                
                startFlag = i+1;
               
            }            
            else if(!startSeen)
                startSeen = true;
		        
            if(ch == '\n' || ch == '\0')                  
                parsing = false;

            i++;
	    }

        if(startSeen)
        {
            elements.push_back(atoi(line.substr(startFlag,i-startFlag).data()));
            faceElements.push_back(elements);
        }

        return faceElements; 
    }