
/* Elizabeth Kenny: Final Project for EC327
 * Prof. Carruthers
 * 08/04/2015
 *
 * The original goal for this app was to be an adapted version of Snake to satire
 * the poor conditions of the greenline and it's constant need for repair (i.e. growth).
 * Issues with my computer resulting in segmentation core dump errors complicated this.
 * Although the train/snake never grows, and the snowball sprite still moves and can crush it,
 * so not all excitement was lost.
 *
 *
 * T logo copyright of the MBTA.
 */

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>

#include <sstream>
#include "Train.hpp"

using namespace std;

/*
 *define hieght and width of window as constant int values.
 *set wait to false, game starts unpaused
*/
const int WIDTH = 600;
const int HEIGHT = 600;
bool wait = true;
static const float PI = 3.14159f;

int snowindex = 0;

enum Direction
{
    Down, Left, Right, Up
};

int tlength = 0;

sf::Vector2f randxy()
{
    float x = rand()%550+22;
    float y = rand()%398+22;


    sf::Vector2f out(x, y);
    return out;
}

//defines radial motion of snowball
void deltaSnow(unsigned int index, sf::Sprite& snowSprite)
{
    //generate random sign for motion when position is regenerated
    int is_sign = rand()%20;
    bool is_neg = false;
    if (is_sign%2==0)
    {
        is_neg = true;
    }
    else
    {
        is_neg = false;
    }
    sf::Vector2f radius(3.0, 20.0);
    index=1;
    float angle = index*PI/75 - PI/2;
    float spritex = cos(angle)*radius.x;
    float spritey = sin(angle)*radius.y;
    snowSprite.move(radius.x+spritex, radius.y+spritey);
    if (snowSprite.getPosition().x > 580 || snowSprite.getPosition().x < 0)
    {
        snowSprite.setPosition(randxy());
        if (is_neg)
        {
            snowSprite.move(-radius.x-spritex, -radius.y-spritey);
        }
    }
    else if (snowSprite.getPosition().y > 450 || snowSprite.getPosition().y < 0)
    {
        snowSprite.setPosition(randxy());
        if (is_neg)
        {
            snowSprite.move(-radius.x-spritex, -radius.y-spritey);
        }

    }

}




//test for collision with snowbanks and walls (if the snowbanks would form
int isCollision(Train& mytrain, sf::Sprite& snowSprite, int collisiontracker) //sf::FloatRect& snowbox
{
    sf::FloatRect tempBox(mytrain.getBox());
    sf::FloatRect tempsnowBox(snowSprite.getGlobalBounds());
    if (tempBox.intersects(tempsnowBox))
    {
        collisiontracker++;
        cout<< "collision" << endl;
        wait = true;
    }

    return collisiontracker;
}




int main()
{
    cout << "Press ARROW KEYS to move, press SPACEBAR to pause/unpause" <<endl;
    cout << "try to hit the T as many times as possible as speed increases" << endl << endl << endl;
/*     Create the main window at constant size as set abo. Set up Framerate limit and clock */
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Green Line, The Game :: Eternal Zen Mode", sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(10+3*tlength);
    sf::Time t1=sf::seconds(1.0/60.0);
    sf::Clock myclock;

//track collisions and score
    int collisiontracker = 0;
    int score =0;

/*      Load font and text
 */
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf"))
    {
        return EXIT_FAILURE;
    }
    sf::Text text("GAME OVER", font, 75);
    text.setColor(sf::Color::Black);



    sf::Text scoretext;
    scoretext.setFont(font);
    scoretext.setCharacterSize(25);
    scoretext.setStyle(sf::Text::Bold);
    scoretext.setColor(sf::Color::Black);
    scoretext.setPosition(50, 250);


/*     Initiate lead train block.
 *     Call function Fuel to initiate first shape.
 *     Draw game screen borders.
 *     Draw game screen borders.
*/
    Train mytrain(window);
    sf::FloatRect trainbox(mytrain.getTShape().getGlobalBounds());

    sf::RectangleShape playscreen(sf::Vector2f(560, 450));
    playscreen.setPosition(sf::Vector2f(22, 20));
    playscreen.setFillColor(sf::Color::White);
/*
 *     Initiate:
 *              boolean statements to declare if new fuel block needs to be generated (needNew).
 *              vector to track the Train blocks as they are called and drawn.
 *              sprite (theTarget) w/ texture of mbta logo (downloaded from https://commons.wikimedia.org/wiki/File:MBTA.svg)
 *              random position (randpos) of new logo (theTarget)
 *
 */

    sf::Texture logoTex;
    if (!logoTex.loadFromFile("MBTA.png"));
        cout << " " << endl;
    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTex);
    logoSprite.setScale(1.55f, 1.55f);
    logoTex.setSmooth(true);
    sf::FloatRect boxSprite(logoSprite.getGlobalBounds());
    sf::Vector2f randpos;
    randpos = randxy();
    logoSprite.setPosition(randpos);

    sf::Texture snowTex;
    if (!snowTex.loadFromFile("Snow.png"));
        cout << " " << endl;
    sf::Sprite snowSprite;
    snowSprite.setTexture(snowTex);
    snowSprite.setScale(.3f, .3f);
    snowTex.setSmooth(true);
    sf::FloatRect snowBox(snowSprite.getGlobalBounds());
    sf::Vector2f randpos2;
    randpos2 = randxy();
    snowSprite.setPosition(randpos2);



    sf::Vector2f newtrainpos;
    //initiate direction as paused
    int dir = -1;

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // Clear screen
        window.clear(sf::Color(0, 100, 0));

        ostringstream ss;
        ss << "SCORE : " << score;
        scoretext.setString(ss.str());
        window.draw(playscreen);
        window.draw(scoretext);



        // Draw the train
        mytrain.drawIt();
        window.draw(logoSprite);
        window.draw(snowSprite);



        if(sf::Event::KeyPressed)
        {
            wait = false;
        /*
         * Press the space bar to pause the game and display
         * instructions. Press again to resume play.
         */
            if (event.key.code == sf::Keyboard::Space)
            {
                wait = true;
                dir = -1;
                mytrain.moveT(dir);


                if (sf::Event::KeyPressed)
                {
                    wait = false;
                }
            }
            if(event.key.code == sf::Keyboard::Up)
            {
                dir = Up;
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                dir = Down;
            }
            if(event.key.code == sf::Keyboard::Right)
            {
                dir = Right;
            }
            if(event.key.code == sf::Keyboard::Left)
            {
                dir = Left;
            }
        }
        unsigned int ind =0;
        deltaSnow(ind, snowSprite);
        ind+=50;

        mytrain.moveT(dir);
//        collisiontracker += mytrain.collision;
//        collisiontracker+=isCollision(trainbox, snowBox, collisiontracker);
        if (mytrain.collision)
        {
            cout << "hit wall, game over" << endl;
            wait = true;
            dir = -1;
            window.draw(text);
        }

    //call the x and y coordinates of the head of the train.
    //test for collisions between these points and the bounding box of the
    // target logo. If there is a collision, generate a new set of random
    //coordinates for the logo and draw another square on the train
    sf::Vector2f curPos(mytrain.getX(), mytrain.getY());
    //compare coordinates of green block with logo
    if ((mytrain.getX() >= randpos.x && mytrain.getX() < randpos.x+20) && (mytrain.getY() >= randpos.y && mytrain.getY() < randpos.y+20))
    {
        randpos.x = randxy().x;
        randpos.y = randxy().y;
        logoSprite.setPosition(randpos);

        tlength++;
        score+=10;
        cout << "SCORE IS " << score << endl;

    }


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;


}

