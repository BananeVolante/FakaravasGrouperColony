#ifndef _Scoreable_H
#define _Scoreable_H
#include <string>


class Scoreable
{
    public:
    virtual float getScore() const = 0;
    virtual const std::string& getName() const = 0; 
};


#endif