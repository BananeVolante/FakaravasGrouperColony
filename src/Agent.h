#ifndef _Agent_H
#define _Agent_H

#include "Environment.h"

/**
 *
 * \brief agent that do things every tick
 */
class Agent : public Environment::LocalizedEntity
{
    // static things

private:
    ///\brief list of all agent currently instanciated
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
    static void simulate()
    {
        for (std::set<Agent *>::iterator it = agentList.begin(); it != agentList.end();)
        {
            if ((*it)->getStatus() == running)
            {
                (*it)->update();
                ++it;
            }
            else if ((*it)->getStatus() == destroy)
                it = agentList.erase(it);
        }
    }

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
    Status getStatus() { return status; }

    ///\brief statusSetter
    void setStatus(Status s) { status = s; }
};

#endif
