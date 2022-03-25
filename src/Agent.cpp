#include "Agent.h"

Agent::Agent(Environment *environment, Vector2<float> pos, float radius ) : LocalizedEntity(environment, pos, radius)
{
    agentList.insert(this);
}

Agent::~Agent()
{

}


void Agent::update()
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

void Agent::simulate()
{

}



Agent::Status Agent::getStatus() { return status; }

void Agent::setStatus(Status s) { status = s; }
