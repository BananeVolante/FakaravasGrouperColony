#include "FpsCounter.h"
FpsCounter::FpsCounter(unsigned int nbrForAvg) : counter(0), nbrForAvg(nbrForAvg), fpsList(nbrForAvg, 0), cachedFps(0)
{
}

void FpsCounter::startCounter()
{
    timings = SDL_GetPerformanceCounter();
}

void FpsCounter::endCounter()
{
    float elapsed = (float)SDL_GetPerformanceFrequency() / (SDL_GetPerformanceCounter() - timings);
    cachedFps-= fpsList[counter%nbrForAvg]/nbrForAvg;
    fpsList[counter%nbrForAvg]= elapsed;
    cachedFps += elapsed/nbrForAvg;
    counter++;
}

bool FpsCounter::nbrIterationHappened() const
{
    return (counter%nbrForAvg == 0 ) && counter!= 0;
}

float FpsCounter::getAverageFps() const
{
    return cachedFps;
}
