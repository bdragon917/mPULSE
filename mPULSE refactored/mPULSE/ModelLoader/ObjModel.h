#pragma once
#include <vector>

class ObjModel
{

public:
    
    typedef struct
    {
        double x;
        double y;
        double z;
    } vertex3d;

    typedef struct
    {
        double x;
        double y;        
    } vertex2d;

    typedef struct
    {
        int vertIndex;
        int vertNormalIndex;        
        int vertTextureIndex;
    } vertElements;

    ObjModel(int ind);
    void addVertexV(std::vector<double> textureVertex);
    void addVertexVT(std::vector<double> textureVertex);
    void addVertexVN(std::vector<double> vertexNormal);
    void addPointP(std::vector<double> point);
    void addLineL(std::vector<double> line);
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