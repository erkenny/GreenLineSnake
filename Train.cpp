/* ELizabeth Kenny, EC327 Final Project
 * part of greenlinegame.cbp
 */

#include <SFML/Graphics.hpp>
#include "Train.hpp"


using namespace std;


//store shape and position of train
Train::Train(sf::RenderWindow &window)
{
    mywindow = &window;
    pos.x = 280;
    pos.y = 220;
    currentDirection = -1;
    m_shape.setSize(sf::Vector2f(20, 20));
    m_shape.setFillColor(sf::Color(0, 100, 0));
    m_shape.setPosition(pos);

    //incremet collision each time a wall is hit
    collision = 0;

}


//change position of train externally
void Train::changePos(sf::Vector2f newPos)
{
    pos.x = newPos.x;
    pos.y = newPos.y;
    m_shape.setPosition(pos.x, pos.y);
}

float Train::getY()
{
    return m_shape.getPosition().y;
}
float Train::getX()
{
    return m_shape.getPosition().x;
}

sf::FloatRect Train::getBox()
{
    return m_shape.getGlobalBounds();
}

// store the dirrection that block is currently
// moving in currentDirection

int Train::getDirection()
{
    return currentDirection;
}

enum Direction
    {
        Down, Left, Right, Up
    };


//defines motion of train based on enum values corresponding to user input
void Train::moveT(int dir)
{

    if (currentDirection<0)
    {
        m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y);
        collision = false;
    }
    if (dir == Up)
    {
        if (m_shape.getPosition().y-20 > 0)
        {
            m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y-10);
            currentDirection = Up;
            collision = false;
        }
        else if (m_shape.getPosition().y-20 < 0)
        {
            collision = true;
        }
    }
    else if (dir == Down)
    {
        if (m_shape.getPosition().y+20 < 470)
        {
            m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y+10);
            currentDirection = Down;
            collision = false;
        }
        else if (m_shape.getPosition().x+20 > 470)
        {
            collision++;
            collision = true;
        }
    }
    else if (dir == Left)
    {
        if (m_shape.getPosition().x-20 > 0)
        {
            m_shape.setPosition(m_shape.getPosition().x-10, m_shape.getPosition().y);
            currentDirection = Left;
            collision = false;
        }
        else if (m_shape.getPosition().x-20 < 0)
        {
            collision++;
            collision = true;
        }
    }
    else if (dir == Right)
    {
        if (m_shape.getPosition().x+20 < 580)
        {
            m_shape.setPosition(m_shape.getPosition().x+10, m_shape.getPosition().y);
            currentDirection = Right;
            collision = false;
        }
        else if (m_shape.getPosition().x+20 > 580)
        {
            collision =true;
        }
    }
}


//returns shape & physical parameters of train block
sf::RectangleShape Train::getTShape()
{
    return m_shape;
}

//draw the train block
void Train::drawIt()
{

    mywindow->draw(m_shape);
}
