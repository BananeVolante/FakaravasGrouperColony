#ifndef _GrouperBase_H
#define _GrouperBase_H
#include "Agent.h"
#include "GrouperHQ.h"
#include "Food.h"

///\brief Base grouper class that can move, take food, die, and is employed by a HQ
class GrouperBase : public Agent
{
protected: 
///\brief minimum value for lifeLeft
static constexpr float lifeLeft_LOWER_BOUND = 1000;
///\brief maximum value for lifeLeft
static constexpr float lifeLeft_UPPER_BOUND = 2500;
///\brief default value for speed
static constexpr float speed_DEFAULT = 1;//cm/2

private:

///\brief  value for maxFoodAmountTransported
static constexpr float maxFoodAmountTransported = 5;
///\brief vision angle of the Grouper
static const float viewAngle; // pi/2
///\brief maximum distance at which the grouper can detect food
static constexpr float viewDistance = 3; //cm


///\brief the hq that employs this grouper
GrouperHQ* const HQ;
///\brief the move speed of this grouper
float speed; 
///\brief normalized vecyor indicating the direction of the grouper's movement
Vector2<float> mvDirection;
///\brief amount of food currently transported
float foodAmountTransported;

///\brief timer indicating the time left to live , can be betweeen LIFE_LEFT_LOWER_BOUND and LIFE_LEFT_UPPER_BOUND
float lifeLeft;


public:
    /**
     * \brief normal constructor for GrouperBase
     * \remark it might be a good idea to add a constructor that takes a struct
     * \param environment the environment where the agent is
     * \param pos base agent position
     * \param hq The headquarters of this grouper
     * \param baseMvDirection The default orientation of the Grouper
     * \param speed the speed of the grouper, default : speed_DEFAULT
     * \param radius entity radius
     * \param startLife the lifetime of the Grouper
     */

    GrouperBase(Environment* environment, Vector2<float> pos, 
        GrouperHQ* hq, Vector2<float> baseMvDirection, 
        float speed = GrouperBase::speed_DEFAULT, float radius = LocalizedEntity::defaultRadius(), 
        float startLife = MathUtils::random(GrouperBase::lifeLeft_LOWER_BOUND, GrouperBase::lifeLeft_UPPER_BOUND) );

    ///\copydoc Agent::update()
    virtual void update();
    ///\copydoc Agent::draw()
    virtual void draw();

private: 

    ///\brief move the unit
    void move();
    
protected:
    ///\brief applies a rotation to the moving direction
    ///\param angle rotation angle in radiant
    void rotate(float angle);

    ///\brief invert the move direction
    void uTurn();
    
    ///\brief change the move direction to point toward a point
    void pointTo(Vector2<float> point);

    ///\brief change the move direction to point toward an unit
    void pointTo(const LocalizedEntity& entity );

    ///\brief place food in a HQ, if possible
    void depositFood();

    ///\brief take food from a pile of food
    ///\param foodPile foodPile to collect from
    void collectFood(Food& foodPile);

    ///\copybrief LocalizedEntity::perceive()
    template<class T>
    std::vector<T*> perceive() const
    {
        return LocalizedEntity::perceive<T>(mvDirection, viewAngle, viewDistance);
    }


};

#endif