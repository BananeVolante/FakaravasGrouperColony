#ifndef _StaticRules_H
#define _StaticRules_H

#include <vector>
#include <initializer_list>

///\brief rule class that requires a pointer to determine the target of a condition or an action
///, which allows the class to be static to save memory
template <class T>
class AbstractStaticRule
{
public:
    ///\brief condition of the rule
    ///\param target concerned by the rule
    virtual bool condition(T* target) const = 0;
    ///\brief action of the rule
    ///\param target concerned by the rule
    virtual void action(T* target) const = 0;
};


///\brief static rule that uses function pointers passed as parameters as conditions and action
template <class T>
class PersonalisableStaticRule : public AbstractStaticRule<T>
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
    PersonalisableStaticRule(conditionFunction cond, actionFunction act) : condFunctPtr(cond), actionFuncPtr(act)
    {}

    ///\copydoc AbstractStaticRule::condition
    virtual bool condition(T* target) const
    {return condFunctPtr(target);}
    ///\copydoc AbstractStaticRule::action
    virtual void action(T* target) const
    {actionFuncPtr(target);}
};


///\brief class taht stores multiple rules, and act based on a OR
template <class T>
class StaticOrRule : public AbstractStaticRule<T>
{
private: 
    ///\brief vector that stores all the rules
    const std::vector<AbstractStaticRule<T>*> rules;

public:
    ///\param rules bracket list of all the rules that the class wil act on
    StaticOrRule(std::initializer_list<AbstractStaticRule<T>*> rules) : rules(rules)
    {}
    ///\copydoc AbstractStaticRule::condition
    ///\brief return true if one of the rules have condition = true
    virtual bool condition(T* target) const
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
    ///\copydoc AbstractStaticRule::action
    ///\brief do the action of the first rule that is true
    virtual void action(T* target) const
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