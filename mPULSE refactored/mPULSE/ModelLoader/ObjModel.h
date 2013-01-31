#pragma once
#include <vector>

class ObjModel
{

public:
    
    typedef struct
    {
        float x;
        float y;
        float z;
    } vertex3d;

    typedef struct
    {
        float x;
        float y;        
    } vertex2d;

    typedef struct
    {
        int vertIndex;
        int vertNormalIndex;        
        int vertTextureIndex;
    } vertElements;

    ObjModel(int ind);
    void addVertexV(std::vector<float> textureVertex);
    void addVertexVT(std::vector<float> textureVertex);
    void addVertexVN(std::vector<float> vertexNormal);
    void addPointP(std::vector<float> point);
    void addLineL(std::vector<float> line);
    void addFaceF(std::vector<std::vector<int>> face);
    void finalize();

private:
    std::vector<vertex3d> v;
    std::vector<vertex2d> vt;
    std::vector<vertex3d> vn;
    std::vector<vertex3d> p;
    std::vector<vertex3d> l;
    std::vector<std::vector<vertElements>> f;
    int index;
};

/*  geometric vertices (v)
    texture vertices (vt)
    vertex normals (vn)
    point (p)
    line (l)
    face (f)*/