#pragma once
#include <vector>
#include "ObjModel.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

class ModelManager
{

public:
    ModelManager();
    void loadModelsFromList(std::string modelListFilename);
    int LoadModel(std::string fileName);
    void parseLine(std::string line,ObjModel* model);
    ObjModel* getModel(int handle); //FIXME: return a const reference?
    std::vector<double> parseFloats(std::string line, int startIndex);
    std::vector<std::vector<int>> parseFaceElements(std::string line, int startIndex);

private:
    std::vector<int> handles;
    std::vector<ObjModel*> models;
    std::string MODEL_LIST_FILENAME;

    int lineNum;
    int currentModelNum;   
};
