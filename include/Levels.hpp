#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "Bomberman.hpp"
#include "Player.hpp"
#include "Destructible.hpp"
#include "Portal.hpp"
#include "StaticWall.hpp"

class Levels
{
public:
    Levels(Destructible destruct, Player *player, Portal portal, StaticWall staticwall/*, Enemy enemy*/);
    ~Levels();
    Levels(Levels const &target);
    Levels &operator=(Levels const &target);
    void advanceToLevelTwo();
    void advanceToLevelThree();
    void advanceToLevelWin();
    void levelOneInit();
    void levelTwoInit();
    void levelThreeInit();
    void setLevel(int level);
    int getLevel(void);
    void setStart(int start);
    int getStart(void);
    Destructible getDestructible();
    Player * getPlayer();
    Portal getPortal();
    StaticWall getStaticWall();
    std::vector<GLfloat> & getListOfWalls();
     //void loadLevel();
    //void chooseDestructibles();
    //Destructible getLevelDestructible();

private:
	int _level;
	int _start;
	Destructible _destructible;
	Player *_player;
	Portal _portal;
	StaticWall _wall;
	std::vector <GLfloat> _listOfWalls;
	std::vector <GLfloat> _listOfWalls1;

};
#endif