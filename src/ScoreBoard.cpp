#include "ScoreBoard.h"
#include "Renderer.h"

ScoreBoard::ScoreBoard(Vector2<float> drawPoint) : drawPoint(drawPoint)
{}

void ScoreBoard::addElement(Scoreable* elem)
{
    elements.push_back(elem);
}

bool ScoreBoard::removeElement(Scoreable* elem)
{
    std::vector<Scoreable*>::iterator it = std::find(elements.begin(), elements.end(), elem);
    if(it == elements.end())
        return false;
    elements.erase(it);
    return true;
}

void ScoreBoard::draw()
{
    std::sort(elements.begin(), elements.end(), [](const Scoreable* a, const Scoreable* b) {return a->getScore()>b->getScore();});

    Vector2<float> currentPos = drawPoint;
    for(Scoreable* scoreable : elements)
    {
        Renderer::getInstance()->drawString(currentPos, scoreable->getName() + " : " + std::to_string(scoreable->getScore()));
        currentPos = currentPos + Vector2<float>(0,10);
    }
    
}