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
        double x;
        double y;        
    } vertex2d;

    typedef struct
    {
        int vertIndex;             
        int vertTextureIndex;
        int vertNormalIndex;   
    } vertElements;

    ObjModel(int ind, std::string tmpName);

    void addVertexV(std::vector<double> textureVertex);
    void addVertexVT(std::vector<double> textureVertex);
    void addVertexVN(std::vector<double> vertexNormal);
    void addPointP(std::vector<double> point);
    void addLineL(std::vector<double> line);
    void addFaceF(std::vector<std::vector<int>> face);
    void finalize();

    std::vector<vertex3d>* getVerticies();
    std::vector<vertex2d>* getVertexTextureCoords();
    std::vector<vertex3d>* getVertexNormals();
    std::vector<vertex3d>* getPoints();
    std::vector<vertex3d>* getLines();
    std::vector<std::vector<vertElements>>* getFaces();
    std::string getName();

    bool getTextureCoordsEnabled();
    bool getNormalsEnabled();

private:

    int index;
    bool textureCoordsEnabled;
    bool normalsEnabled;
    std::string name;
    std::vector<vertex3d> verticies;
    std::vector<vertex2d> vertexTextureCoords;
    std::vector<vertex3d> vertexNormals;
    std::vector<vertex3d> points;
    std::vector<vertex3d> lines;
    std::vector<std::vector<vertElements>> faces;
};

/*  geometric vertices (v)
    texture vertices (vt)
    vertex normals (vn)
    point (p)
    line (l)
    face (f)*/