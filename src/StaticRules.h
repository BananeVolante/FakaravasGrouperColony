#ifndef _StaticRules_H
#define _StaticRules_H

#include <vector>
#include <initializer_list>

template <class T>
class AbstractStaticRule
{
public:
    virtual bool condition(T* target) = 0;
    virtual void action(T* target) = 0;
};


template <class T>
class PersonalisableStaticRule : public AbstractStaticRule<T>
{
public: 
    typedef bool (*conditionFunction)(T* target);
    typedef void (*actionFunction)(T* target);
private: 
    conditionFunction condFunctPtr;
    actionFunction actionFuncPtr;

public:
    PersonalisableStaticRule(conditionFunction cond, actionFunction act) : condFunctPtr(cond), actionFuncPtr(act)
    {}

    virtual bool condition(T* target)
    {return condFunctPtr(target);}
    virtual void action(T* target)
    {actionFuncPtr(target);}
};

template <class T>
class StaticOrRule : public AbstractStaticRule<T>
{
private: 
    std::vector<AbstractStaticRule<T>*> rules;

public:
    StaticOrRule(std::initializer_list<AbstractStaticRule<T>*> rules) : rules(rules)
    {}
    virtual bool condition(T* target)
    {
        bool res = false;
        for(AbstractStaticRule<T>* rule : rules )
        {
            if(rule->condition(target))
            {
                res = true;
                break;
            }
        }
        return res;
    }
    virtual void action(T* target)
    {
        for(AbstractStaticRule<T>* rule : rules)
        {
            if(rule->condition(target))
            {
                rule->action(target);
                break;
            }
        }
    }
};
#endif