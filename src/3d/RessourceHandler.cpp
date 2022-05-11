#include "RessourceHandler.h"
#include <assert.h>
#include "ObjParser.h"
using namespace Fakarava3d;

RessourceHandler* RessourceHandler::instance = nullptr;


void RessourceHandler::load()
{
    models.insert(std::pair<std::string,Mesh>("lowPolyGrouper",ObjParser::readObject("ressources/lowPolyGrouper.obj")));
}

RessourceHandler* RessourceHandler::getInstance()
{
    assert(instance!= nullptr);
    return instance;
}

void RessourceHandler::createInstance()
{
    assert(instance == nullptr);
    instance = new RessourceHandler();
    instance->load();
}

void RessourceHandler::destroyInstance()
{
    assert(instance!= nullptr);
    delete instance;
}

Mesh* RessourceHandler::get(const std::string& name)
{
    return &(models.at(name));
}
