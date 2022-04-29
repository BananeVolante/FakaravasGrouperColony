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

        file.open(fileName); // no need to close because of RAII??
        if(!file.is_open())
            throw std::ifstream::failure("file was not opened ");
        //init the temporary variables
        std::string line;
        Eigen::Vector3f vertex;
        std::tuple<size_t, size_t, size_t> triangle;
        std::string lineTrashCan;
        while (std::getline(file, line))
        {

            std::istringstream lineStream(line);
            std::string lineType;
            //read the 1st word to detect the char type
            lineStream >> lineType;
            //vertex
            if (lineType == "v")
            {
                lineStream >> vertex[0] >> vertex[1] >> vertex[2];
                mesh.getLocalPoints().push_back(vertex);
            }
            //face
            if(lineType == "f")
            {
                //form is index1/useless/useless index2/useless/useless index3/useless/useless ...
                //we ignore polygons with more than 3 vertexes, and just keep the first 3
                //read the first index
                lineStream >> std::get<0>(triangle);
                //and go to the next word
                lineStream>>lineTrashCan;
                lineStream >> std::get<1>(triangle);
                lineStream>>lineTrashCan;
                lineStream >> std::get<2>(triangle);
                //go from index that starts at 1 to index that starts at 0
                std::get<0>(triangle)--;
                std::get<1>(triangle)--;
                std::get<2>(triangle)--;

                mesh.getTriangles().push_back(triangle);
            }
        }
}  catch(const std::ifstream::failure& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Continuing with empty mesh" << std::endl;
    }

    trianglesToLines(mesh.getTriangles(), mesh.getLines());
    return mesh;
}


std::vector<std::pair<size_t, size_t>> ObjParser::trianglesToLines(const std::vector<std::tuple<size_t, size_t, size_t>>& triangles)
{
    std::vector<std::pair<size_t, size_t>> lines;
    trianglesToLines(triangles, lines);
    return lines;

}

void ObjParser::trianglesToLines(const std::vector<std::tuple<size_t, size_t, size_t>>& triangles, std::vector<std::pair<size_t, size_t>>& lines)
{
    for(auto& triangle : triangles)
    {
        lines.push_back({std::get<0>(triangle), std::get<1>(triangle)});
        lines.push_back({std::get<0>(triangle), std::get<2>(triangle)});
        lines.push_back({std::get<1>(triangle), std::get<2>(triangle)});
    }

}
