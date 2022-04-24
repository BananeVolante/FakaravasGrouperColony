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
        static Mesh readObject(std::string fileName);
    };
}

#endif