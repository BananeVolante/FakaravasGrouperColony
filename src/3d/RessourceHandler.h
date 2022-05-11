#ifndef _RessourceHandler_H
#define _RessourceHandler_H
#include <map>
#include "Mesh.h"

namespace Fakarava3d
{
///\brief class to handle 3d ressources
class RessourceHandler
{
    private: 
    ///\brief pointer to the instance
    static RessourceHandler* instance;

    ///\brief map containing the models
    std::map<std::string, Mesh> models;

    ///\brief load the models
    void load();

    public:
    ///\brief return the instance of the ressource handler
    static RessourceHandler* getInstance();
    ///\brief creates the RessourceHandler instance and load the models
    static void createInstance();
    ///\brief destroys the instance of the handler to free ressources
    static void destroyInstance();
    ///\brief returns the mesh specified by name
    ///\param name name of the mesh
    ///\returns pointer to a mesh
    Mesh* get(const std::string& name);

};

}


#endif