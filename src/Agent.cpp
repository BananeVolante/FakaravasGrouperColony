#include "Agent.h"

//Static var init
std::set<Agent*> Agent::agentList = std::set<Agent*>();


Agent::Agent(Environment *environment, Vector2<float> pos, float radius ) : LocalizedEntity(environment, pos, radius), status(running)
{
    agentList.insert(this);
}

Agent::~Agent()
{

}


void Agent::update()
{

}

void Agent::simulate()
{
    
    int nbrAgentUpdated = 0;
    int nbrAgentErased = 0;

    for (std::set<Agent *>::iterator it = agentList.begin(); it != agentList.end();)
    {
        if ((*it)->getStatus() == running)
        {
            nbrAgentUpdated++;
            (*it)->update();
            ++it;
        }
        else if ((*it)->getStatus() == destroy)
        {
            it = agentList.erase(it);
            nbrAgentErased++;
        }
    }
SDL_Log("Simulate called, %d agent updated and %d agents erased", nbrAgentUpdated, nbrAgentErased);
}



Agent::Status Agent::getStatus() { return status; }

void Agent::setStatus(Status s) { status = s; }
