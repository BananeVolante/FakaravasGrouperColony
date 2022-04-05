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
    //int totalAgents = agentList.size();
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
            delete *it ;
            it = agentList.erase(it);
            nbrAgentErased++;
        }else // and draw it and go to next it if it's still running
        {
            (*it)->draw();
            ++it;
        }
    }
//SDL_Log("Simulate called, %d agent updated and %d agents erased, on a total of %d agents", nbrAgentUpdated, nbrAgentErased, totalAgents);
}


void Agent::finalize()
{
    //free every instance of agent
    for(auto agent : agentList)
            delete agent;
        //SDL_Log("trying to delete %f %f", agent->getPosition()[0], agent->getPosition()[1]);

    //no need to empty the agent list, it will be destroyed
}



Agent::Status Agent::getStatus() { return status; }

void Agent::setStatus(Status s) { status = s; }

