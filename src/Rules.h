#ifndef _AbstractRule_H
#define _AbstractRule_H
#include "initializer_list"
#include "vector"
#include "GrouperBasePheromones.h"

///\brief abstract rule, where a condition being true leads to an action
class AbstractRule
{
public:
    ///\return true if the condition is true, false otherwise
    virtual bool condition() const = 0;
    ///\brief do something
    virtual void action() const = 0;

};

///\brief set of multiple rules, with an or between them
class OrRule : public AbstractRule
{
private:
    std::vector<AbstractRule*> allRules;

public:     
    OrRule(std::initializer_list<AbstractRule*> rules);

    ///\brief return true if one of the condition of the rules passed at init is true
    virtual bool condition() const;

    ///\brief do the action of the first condition that is true
    virtual void action() const;

};

class AbstractGrouperRule : public AbstractRule
{
protected:
    GrouperBasePheromones* const target;
public: 
    AbstractGrouperRule(GrouperBasePheromones* grouper);

};
#endif