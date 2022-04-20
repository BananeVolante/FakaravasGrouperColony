#ifndef _StaticRulesTemplated_H
#define _StaticRulesTemplated_H

#include <vector>
#include <initializer_list>
#include "iostream"
#include <set>

///\brief rule class that requires a pointer to determine the target of a condition or an action
///, which allows the class to be static to save memory
template <class T>
class AbstractStaticRuleTemplated
{
public:
    AbstractStaticRuleTemplated()
    {

    }

    ///\brief condition of the rule
    ///\param target concerned by the rule
    virtual bool condition(T* target) const = 0;
    ///\brief action of the rule
    ///\param target concerned by the rule
    virtual void action(T* target) const = 0;
};


///\brief static rule that uses function pointers passed as parameters as conditions and action
template <class T>
class PersonalisableStaticRuleTemplated : public AbstractStaticRuleTemplated<T>
{
public: 
    typedef bool (*conditionFunction)(T* target);
    typedef void (*actionFunction)(T* target);
private: 
    ///\brief pointer to the condition function
    const conditionFunction condFunctPtr;
    ///\brief pointer to the action function
    const actionFunction actionFuncPtr;

public:
    ///\param cond condition function
    ///\param act action function
    PersonalisableStaticRuleTemplated(conditionFunction cond, actionFunction act) : condFunctPtr(cond), actionFuncPtr(act)
    {}

    ///\copydoc AbstractStaticRuleTemplated::condition
    virtual bool condition(T* target) const
    {return condFunctPtr(target);}
    ///\copydoc AbstractStaticRuleTemplated::action
    virtual void action(T* target) const
    {actionFuncPtr(target);}
};


///\brief class taht stores multiple rules, and act based on a OR
template <class T>
class StaticOrRuleTemplated : public AbstractStaticRuleTemplated<T>
{
private: 
    ///\brief vector that stores all the rules
    const std::vector<const AbstractStaticRuleTemplated<T>*> rules;

public:
    ///\param rules bracket list of all the rules that the class wil act on
    StaticOrRuleTemplated(std::initializer_list<const AbstractStaticRuleTemplated<T>*> rules) : rules(rules)
    {}
    ///\copydoc AbstractStaticRuleTemplated::condition
    ///\brief return true if one of the rules have condition = true
    virtual bool condition(T* target) const
    {
        bool res = false;
        for(const AbstractStaticRuleTemplated<T>* rule : rules )
        {
            if(rule->condition(target))
            {
                res = true;
                break;
            }
        }
        return res;
    }
    ///\copydoc AbstractStaticRuleTemplated::action
    ///\brief do the action of the first rule that is true
    virtual void action(T* target) const
    {
        for(const AbstractStaticRuleTemplated<T>* rule : rules)
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