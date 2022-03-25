#ifndef _Agent_H
#define _Agent_H

#include "Environment.h"

class Agent : public Environment::LocalizedEntity
{

private: 
    static std::set<Agent *> agentList;

public:
    /**
     * \enum Status
     * \brief Status possibles pour un agent
     */
    typedef enum
    {
        running,
        destroy
    } Status;

    /**
     * \brief clean the agentList of all Agent with the status destroy and update() other Agent
     *
     */
    static void simulate();
private:
    ///\brief Status actuel de l'agent
    Status status;
public:

        // Constructor, Destructor

    /**
     *\brief Normal constructor
     * \param environment environnement dans lequel l'agent évoluera
     * \param pos position de départ de l'agent
     * \param radius rayon de l'entité
     */
    Agent(Environment *environment, Vector2<float> pos, float radius = Environment::LocalizedEntity::defaultRadius());
    
    ~Agent();

    /**
     *
     *\brief method that execute the actions that the agent should do every tick
     *
     */
    virtual void update();



    // Getters, setters

    ///\brief statusGetter
    Status getStatus();

    ///\brief statusSetter
    void setStatus(Status s);


};

std::set<Agent*> Agent::agentList = std::set<Agent*>();

#endif