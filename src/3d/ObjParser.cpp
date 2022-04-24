#include "ObjParser.h"
#include "iostream"
#include "fstream"


using namespace Fakarava3d;


Mesh ObjParser::readObject(std::string fileName)
{
    std::ifstream file;
    file.open(fileName);
    std::string line;
    Eigen::Vector3f vertex;


    Mesh mesh;
    while(std::getline(file, line))
    {

        std::istringstream lineStream(line);
        std::string lineType;
        lineStream >> lineType;
        if(lineType == "v" )
        {
            lineStream >> vertex[0] >> vertex[1] >> vertex[2] ;
            mesh.points.push_back(vertex);
        }
    }

    return mesh;
}