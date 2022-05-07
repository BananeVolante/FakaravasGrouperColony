#ifndef _FpsCounter_H
#define _FpsCounter_H
#include <stdlib.h>
#include <vector>
#include "SDL2/SDL2_framerate.h"

class FpsCounter
{
private: 
    unsigned int counter;
    ///\brief determine how many 
    unsigned int nbrForAvg;
    ///\brief used to store timings between startCounter and endCounter call
    Uint64 timings;

    ///\brief contains the list of fps
    std::vector<float> fpsList;

    ///\brief the last fps processed
    float cachedFps;

public: 
    ///\param nbrForAvg number of frames used to process the fps average
    FpsCounter(unsigned int nbrForAvg);
    
    ///\brief start counting the time elapsed
    void startCounter();
    ///\brief stop counting the time elapsed and save it
    void endCounter();

    ///\brief indicates if nbrForAvgFrames happenned since the last time this function returned true
    ///\remark does not return true on the first frame
    bool nbrIterationHappened() const;

    ///\return return the average fps 
    float getAverageFps() const;

};


#endif