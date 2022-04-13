#ifndef _ScoreBoard_H
#define _ScoreBoard_H
#include <vector>
#include "Rectangle.h"
#include "Scoreable.h"

///\brief score board that is supposed to diplay the scores at the top of the screen
class ScoreBoard
{
private:
    ///\brief height of a char, experimental
    static constexpr float CHAR_HEIGHT = 10;


    ///\brief point where the top left of the scores are drawn
    const Vector2<float> drawPoint;
    ///\brief list of all scorables that are drawn on the score screen
    std::vector<Scoreable*> elements;

public:
    ///\param drawBox point where the scoreboard is drawn
    ScoreBoard(Vector2<float> drawPoint);
    ///\brief add an element to the scoreboard
    ///\param elem element to add
    void addElement(Scoreable* elem);

    ///\brief remove the first instance of an element from the scoreboard
    ///\param elem element to remove
    bool removeElement(Scoreable* elem);

    /// \brief draw the scoreboard
    void draw();
};



#endif