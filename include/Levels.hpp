#ifndef LEVELS_HPP
#define LEVELS_HPP

#include "Bomberman.hpp"
#include "Player.hpp"
#include "Destructible.hpp"
#include "Portal.hpp"
#include "StaticWall.hpp"
#include "enemy.hpp"

class Levels
{
public:
    Levels(Destructible destruct, Player *player, std::vector<Enemy> &enemies, Portal portal, StaticWall staticwall/*, Enemy enemy*/);
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
    std::vector<Enemy> & getEnemies();
     //void loadLevel();
    //void chooseDestructibles();
    //Destructible getLevelDestructible();

private:
	int _level;
	int _start;
    int _numEnemies;
	Destructible _destructible;
    std::vector<Enemy> _enemies;
    std::vector<Enemy>::iterator iter;
	Player *_player;
	Portal _portal;
	StaticWall _wall;
	std::vector <GLfloat> _listOfWalls;
	std::vector <GLfloat> _listOfWalls1;

};
#endif