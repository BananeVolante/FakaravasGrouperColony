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

void Agent::simulate()
{
    int totalAgents = agentList.size();
    int nbrAgentUpdated = 0;
    int nbrAgentErased = 0;

    for (std::set<Agent *>::iterator it = agentList.begin(); it != agentList.end();)
    {
        //first update it if it's running
        if ((*it)->getStatus() == running)
        {
            nbrAgentUpdated++;
            (*it)->update();
        }

        //then clean it if it died during the update
        if ((*it)->getStatus() == destroy)
        {
            it = agentList.erase(it);
            nbrAgentErased++;
        }else // and draw it and go to next it if it's still running
        {
            (*it)->draw();
            ++it;
        }
    }
SDL_Log("Simulate called, %d agent updated and %d agents erased, on a total of %d agents", nbrAgentUpdated, nbrAgentErased, totalAgents);
}



Agent::Status Agent::getStatus() { return status; }

void Agent::setStatus(Status s) { status = s; }
