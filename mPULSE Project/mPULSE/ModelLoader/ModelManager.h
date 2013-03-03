#pragma once
#include <vector>
#include "ObjModel.h"
#include <iostream>
#include <fstream>

class ModelManager
{

public:
    ModelManager();

    void loadModelsFromList(std::string modelListFilename);
    int LoadModel(std::string fileName);
    void parseLine(std::string line,ObjModel* model);

    ObjModel* getModel(int index); 
    ObjModel* getModel(std::string fileName); //FIXME: return a const reference?   
    std::string getErrorMessage();

    std::vector<double> parseFloats(std::string line, int startIndex);
    std::vector<std::vector<int>> parseFaceElements(std::string line, int startIndex);
    
    std::string removeFilePath(std::string line);        
    std::string MODEL_LIST_FILENAME;    

private:
    bool DebugMode;

    std::string errorMsg;
    std::vector<int> handles;
    std::vector<ObjModel*> models;        

    int lineNum;
    int currentModelNum;
    int numOfModels;
};
