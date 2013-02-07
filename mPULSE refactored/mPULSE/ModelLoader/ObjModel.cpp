#include "ObjModel.h"


ObjModel::ObjModel(int ind)
{
    index = ind;
}

void ObjModel::addVertexV(std::vector<double> geometricVertex)
{    
    vertex3d vert;
    vert.x = geometricVertex[0];
    vert.y = geometricVertex[1];
    vert.z = geometricVertex[2];
    v.push_back(vert);
}

void ObjModel::addVertexVT(std::vector<double> textureVertex)
{
    vertex2d vert;
    vert.x = textureVertex[0];
    vert.y = textureVertex[1];
    vt.push_back(vert);
}    

void ObjModel::addVertexVN(std::vector<double> vertexNormal)
{
    vertex3d vert;
    vert.x = vertexNormal[0];
    vert.y = vertexNormal[1];
    vert.z = vertexNormal[2];
    vn.push_back(vert);
}    

void ObjModel::addPointP(std::vector<double> point)
{

}

void ObjModel::addLineL(std::vector<double> line)
{

}

void ObjModel::addFaceF(std::vector<std::vector<int>> face)
{    
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
                vertexE.vertIndex = face[i][j];
            else if(j==1)
                vertexE.vertNormalIndex = face[i][j];
            else if(j==2)
                vertexE.vertTextureIndex = face[i][j];
        }
        vertexElements.push_back(vertexE);        
    }
    f.push_back(vertexElements);        
}

void ObjModel::finalize()
{    
    v.shrink_to_fit();
    vt.shrink_to_fit();
    vn.shrink_to_fit();
    p.shrink_to_fit();
    l.shrink_to_fit();
    f.shrink_to_fit();
}