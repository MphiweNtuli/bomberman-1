/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Maze.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tditshwe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 15:35:30 by tditshwe          #+#    #+#             */
/*   Updated: 2017/08/14 15:35:36 by tditshwe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Maze.hpp"

Maze::Maze() { }

Maze::Maze(Player *p)
{
	player = p;
}

Maze::~Maze()
{
	//delete player;
}

void Maze::addWall(GLfloat x, GLfloat y, bool isDest)
{
	Wall wall(x, y, isDest);
	walls.push_back(wall);
}

std::list<Wall> Maze::getWalls()
{
	return walls;
}

bool Maze::canPlayerMoveRight()
{
	std::list<Wall>::iterator it;

	std::cout << "Player: " << player->getXPos() << "," << player->getYPos() << " Wall: ";
	it = walls.begin();
	for (int i = 0; i < 1; i++)
	{
		++it;
	}
	std::cout << it->getXPos() - 0.1 << "," << it->getYPos() + 1.1 << std::endl;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		bool towardsWall = player->getYPos() - PLAYER < it->getYPos() + 1.1 &&
			player->getYPos() > it->getYPos() + 1.1;
		//bool oppWall = player->getYPos() < it->getYPos() - 0.9
			//&&  player->getYPos() - PLAYER > it->getYPos() - 0.9 - WALL;
		bool pastWall = player->getYPos() - PLAYER < it->getYPos() + 1.1 - WALL
			&& player->getYPos() > it->getYPos() + 1.1 - WALL;
		bool isWallRight = it->getXPos() - 0.1 > player->getXPos() + PLAYER
			&& (towardsWall || pastWall);

		/*if (towardsWall)
			std::cout << "Towards true ";
		if (oppWall)
			std::cout << "opposite true ";
		if (pastWall)
			std::cout << "Past true ";
		if (isWallRight)
			std::cout << "Wallright true";
		std::cout << std::endl;*/
		if ((towardsWall || pastWall) && isWallRight)
			return false;
	}

	return true;
}

//make collision when player moves to the left of the wall
bool Maze::canPlayerMoveLeft()
{
	std::list<Wall>::iterator it;

	std::cout << "Player: " << player->getXPos() << "," << player->getYPos() << " Wall: ";
	it = walls.begin();
	for (int i = 0; i < 64; i++)
	{
		++it;
	}
	std::cout << it->getXPos() - 0.1 << "," << it->getYPos() + 1.1 << std::endl;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		bool towardsWall = player->getYPos() - PLAYER < it->getYPos() + 1.1 &&
			player->getYPos() >= it->getYPos() + 1.1;
		bool pastWall = player->getYPos() - PLAYER <= it->getYPos() + 1.1 - WALL
			&& player->getYPos() > it->getYPos() + 1.1 - WALL;
		bool isWallLeft = it->getXPos() - 0.1 < player->getXPos()
			&& (towardsWall || pastWall);

		if ((towardsWall || pastWall) && isWallLeft)
			return false;
	}

	return true;
}

//check if player can move up
bool Maze::canPlayerMoveUp()
{
	std::list<Wall>::iterator it;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		bool towardsWall = player->getXPos() + PLAYER > it->getXPos() - 0.1 &&
			player->getXPos() <= it->getXPos() - 0.1;
		bool pastWall = player->getXPos() + PLAYER >= it->getXPos() - 0.1 + WALL
			&& player->getXPos() < it->getXPos() - 0.1 + WALL;
		bool isWallUp = it->getYPos() + 1.1 > player->getYPos()
			&& (towardsWall || pastWall);

		if ((towardsWall || pastWall) && isWallUp)
			return false;
	}

	return true;
}

//check if player collides with bottom wall
bool Maze::canPlayerMoveDown()
{
	std::list<Wall>::iterator it;

	std::cout << player->getXPos() << "," << player->getYPos() << " ";
	it = walls.begin();
	std::cout << it->getXPos() + 0.9 << "," << it->getYPos() - 0.9 << std::endl;

	for (it = walls.begin(); it != walls.end(); ++it)
	{
		bool towardsWall = player->getXPos() + PLAYER > it->getXPos() - 0.1 &&
			player->getXPos() <= it->getXPos() - 0.1;
		bool pastWall = player->getXPos() + PLAYER >= it->getXPos() - 0.1 + WALL
			&& player->getXPos() < it->getXPos() - 0.1 + WALL;
		bool isWallDown = it->getYPos() + 1.1 < player->getYPos() - PLAYER;

		/*if (towardsWall)
		std::cout << "Towards true ";
		if (pastWall)
		std::cout << "Past true ";
		if (isWallUp)
		std::cout << "Wallright true";
		std::cout << std::endl;*/

		if ((towardsWall || pastWall) && isWallDown)
			return false;
	}

	return true;
}

void Maze::setWalls(std::list<Wall> walls)
{
	this->walls = walls;
}

void Maze::addDestructibles(std::list<Wall> dest)
{
	std::list<Wall>::iterator it;

	for (it = dest.begin(); it != dest.end(); ++it)
		walls.push_back(*it);
}
