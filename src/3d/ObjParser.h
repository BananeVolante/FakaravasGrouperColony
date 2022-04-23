#ifndef _ObjParser_H
#define _ObjParser_H
#include "ThreeDObj.h"

namespace Fakarava3d
{
    using namespace Fakarava3d;
    class ObjParser
    {
    private:
    public:
        static ThreeDObj::MeshData readObject(std::string fileName);
    };
}

#endif