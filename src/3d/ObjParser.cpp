#include "ObjParser.h"
#include "iostream"
#include "fstream"

using namespace Fakarava3d;

Mesh ObjParser::readObject(std::string fileName)
{
    Mesh mesh;
    try
    {
        std::ifstream file;
        file.exceptions(std::ifstream::badbit );

        file.open(fileName); // no need to close becuase of RAII??
        if(!file.is_open())
            throw std::ifstream::failure("file was not opened ");
        std::string line;
        Eigen::Vector3f vertex;

        while (std::getline(file, line))
        {

            std::istringstream lineStream(line);
            std::string lineType;
            lineStream >> lineType;
            if (lineType == "v")
            {
                lineStream >> vertex[0] >> vertex[1] >> vertex[2];
                mesh.getLocalPoints().push_back(vertex);
            }
        }
}  catch(const std::ifstream::failure& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Continuing with empty mesh" << std::endl;
    }

    return mesh;
}