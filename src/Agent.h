#ifndef _Agent_H
#define _Agent_H

#include "Environment.h"

///\brief agent that evolve in an environment
class Agent : public Environment::LocalizedEntity
{

private: 
///\brief set that containes all the agents currently instanciated
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

    ///\brief cleans everything linked to Agent
    static void finalize();

protected:
    ///\brief current status of the agent
    Status status;
public:

        // Constructor, Destructor

    /**
     *\brief Normal constructor
     * \param environment the environment where the agent is
     * \param pos base agent position
     * \param radius entity radius
     */
    Agent(Environment *environment, Vector2<float> pos, float radius = Environment::LocalizedEntity::defaultRadius());
    
    ~Agent();

    /**
     *
     *\brief method that execute the actions that the agent should do every tick
     *
     */
    virtual void update() = 0;


    ///\brief draw the agent
    virtual void draw() = 0;




    // Getters, setters

    ///\brief statusGetter
    Status getStatus();

    ///\brief statusSetter
    void setStatus(Status s);

    ///\Brief Excpetion called when an agent needs to be near another 
    /// one to call a certain function, but this function is called when this 
    ///requirement is not fulfilled
    class badPositionException : public std::logic_error
    {
        public: 
            badPositionException(const std::string & message) : logic_error(message) {}
    };

};

#endif
