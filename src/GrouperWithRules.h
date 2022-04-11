#ifndef _GrouperWithRules_H
#define _GrouperWithRules_H
#include "GrouperBasePheromones.h"
#include "Rules.h"

///\brief class similar to Grouper, but that uses rule class to determine its actions
class GrouperWithRules : public GrouperBasePheromones
{
private:
OrRule rules;

    class rule1 : public AbstractGrouperRule
    {   
        public:
        rule1(GrouperBasePheromones* grouper);
        bool virtual condition() const;
        void virtual action() const;
    };

    class rule2 : public AbstractGrouperRule
    {
        public: 
        rule2(GrouperBasePheromones* grouper);
        bool virtual condition() const;
        void virtual action() const;
    };
    class rule3 : public AbstractGrouperRule
    {
        public: 
        rule3(GrouperBasePheromones* grouper);
        bool virtual condition() const;
        void virtual action() const;
    };
    class rule4 : public AbstractGrouperRule
    {
        public: 
        rule4(GrouperBasePheromones* grouper);
        bool virtual condition() const;
        void virtual action() const;
    };
    class rule5 : public AbstractGrouperRule
    {
        public: 
        rule5(GrouperBasePheromones* grouper);
        bool virtual condition() const;
        void virtual action() const;
    };
    class rule6 : public AbstractGrouperRule
    {
        public: 
        rule6(GrouperBasePheromones* grouper);
        bool virtual condition() const;
        void virtual action() const;
    };

public:
///\copydoc GrouperBasePheromones::GrouperBasePheromones()
    GrouperWithRules(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );
///\copydoc Agent::update()
    virtual void update();
    

};  

#endif