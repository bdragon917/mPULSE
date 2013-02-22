#include "ObjModel.h"


ObjModel::ObjModel(int ind, std::string tmpName)
{
    name = tmpName;
    index = ind;
    textureCoordsEnabled = true;
    normalsEnabled = true;
}

void ObjModel::addVertexV(std::vector<double> geometricVertex)
{    
    vertex3d vert;
    vert.x = static_cast<float>(geometricVertex[0]);
    vert.y = static_cast<float>(geometricVertex[1]);
    vert.z = static_cast<float>(geometricVertex[2]);
    verticies.push_back(vert);
}

void ObjModel::addVertexVT(std::vector<double> textureVertex)
{
    vertex2d vert;
    vert.x = textureVertex[0];
    vert.y = textureVertex[1];
    vertexTextureCoords.push_back(vert);
}    

void ObjModel::addVertexVN(std::vector<double> vertexNormal)
{
    vertex3d vert;
    vert.x = static_cast<float>(vertexNormal[0]);
    vert.y = static_cast<float>(vertexNormal[1]);
    vert.z = static_cast<float>(vertexNormal[2]);
    vertexNormals.push_back(vert);
}    

void ObjModel::addPointP(std::vector<double> point)
{

}

void ObjModel::addLineL(std::vector<double> line)
{

}

void ObjModel::addFaceF(std::vector<std::vector<int>> face)
{   
    if(face[0].size() < 2)
    {
        textureCoordsEnabled = false;
        normalsEnabled = false;
    }
    else if(face[0].size() < 3)
    {
        normalsEnabled = false;
    }

    std::vector<vertElements> vertexElements;
    vertElements vertexE;

    vertexE.vertIndex = -1;
    vertexE.vertNormalIndex = -1;
    vertexE.vertTextureIndex = -1;

    for(unsigned int i=0;i<face.size();i++)
    {   
        for(unsigned int j=0;j<face[i].size();j++)
        {
            if(j==0)
                vertexE.vertIndex = face[i][j]-1;
            else if(j==1)
                vertexE.vertTextureIndex = face[i][j]-1;
            else if(j==2)
                vertexE.vertNormalIndex = face[i][j]-1;
        }
        vertexElements.push_back(vertexE);        
    }
    faces.push_back(vertexElements);        
}

std::vector<ObjModel::vertex3d>* ObjModel::getVerticies()
{
    return &verticies;
}
std::vector<ObjModel::vertex2d>* ObjModel::getVertexTextureCoords()
{
    return &vertexTextureCoords;
}
std::vector<ObjModel::vertex3d>* ObjModel::getVertexNormals()
{
    return &vertexNormals;
}

std::vector<ObjModel::vertex3d>* ObjModel::getPoints()
{
    return &points;
}

std::vector<ObjModel::vertex3d>* ObjModel::getLines()
{
    return &lines;
}

std::vector<std::vector<ObjModel::vertElements>>* ObjModel::getFaces()
{
    return &faces;
}

bool ObjModel::getTextureCoordsEnabled()
{

    return textureCoordsEnabled;
}

bool ObjModel::getNormalsEnabled()
{
    return normalsEnabled;
}

std::string ObjModel::getName()
{
    return name;
}

void ObjModel::finalize()
{    
    verticies.shrink_to_fit();
    vertexTextureCoords.shrink_to_fit();
    vertexNormals.shrink_to_fit();
    points.shrink_to_fit();
    lines.shrink_to_fit();
    faces.shrink_to_fit();
}