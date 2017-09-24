#ifndef MAZE_HPP
#define MAZE_HPP

#include <list>
#include "Wall.hpp"
#include "Player.hpp"

#define MAZE_WIDTH 1024
#define MAZE_HEIGHT 768
#define WALL 0.075f
#define PLAYER 0.08f

class Maze
{
private:
	std::list<Wall> walls;
	Player *player;

public:
	Maze();
	Maze(Player *p);
	~Maze();

	void addWall(GLfloat x, GLfloat y, bool isDest);
	bool canPlayerMoveRight();
	bool canPlayerMoveLeft();
	bool canPlayerMoveUp();
	bool canPlayerMoveDown();
	//void drawWalls();
	void setWalls(std::list<Wall> walls);
	void addDestructibles(std::list<Wall> dest);
	std::list<Wall> getWalls();
};

#endif
