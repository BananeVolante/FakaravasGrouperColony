#include "Agent.h"

Agent::Agent(Environment * environment, Vector2<float> pos, float radius) : LocalizedEntity(environment, pos, radius), status(running)
{
    agentList.insert(this);
}
