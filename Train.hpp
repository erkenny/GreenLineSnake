/* ELizabeth Kenny, EC327 Final Project
 * greenlinegame.cbp
 */

#ifndef _TRAIN_HPP_
#define _TRAIN_HPP_
#include <vector>


#include <SFML/Graphics.hpp>

using namespace std;
class Train{
public:
    enum Direction
    {
        Down, Left, Right, Up
    };

    Train(sf::RenderWindow&);
    sf::Vector2f pos;
    int currentDirection;
    int getDirection();
    void moveT(int);
    void changePos(sf::Vector2f);
    float getY();
    float getX();
    sf::FloatRect getBox();
    void drawIt();
    sf::RectangleShape m_shape;
    sf::RectangleShape getTShape();
    bool collision;




private:

    sf::RenderWindow *mywindow;

};

#endif
