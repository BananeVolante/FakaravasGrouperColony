#ifndef _ObjParser_H
#define _ObjParser_H
#include "ThreeDObj.h"
#include "Mesh.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;

    ///\brief Class that contains different functions to read .obj files and return a Mesh 
    class ObjParser
    {
    private:
    public:
        ///\brief read a .pbj file and return the points of the model stored in this file
        ///\param fileName path of the file to read
        ///\remark can only read triangular faces. Use the blender triangulation feature to make it compatible
        static Mesh readObject(std::string fileName);
        ///\brief read an array of triangles and turn them into lines
        ///\param triangles the triangles to convert 
        static std::set<std::pair<size_t, size_t>> trianglesToLines(const std::set<std::tuple<size_t, size_t, size_t>>& triangles);
        ///\brief read an array of triangles and put them into lines
        ///\param triangles the triangles to convert 
        ///\param lines vector where the lines should be put
        static void trianglesToLines(const std::set<std::tuple<size_t, size_t, size_t>>& triangles, std::set<std::pair<size_t, size_t>>& lines);
    
    
    };
}

#endif