#include "Levels.hpp"

Levels::Levels(Destructible dest, Player *player, Portal portal, StaticWall staticwall) : _destructible(dest), _player(player), _portal(portal), _wall(staticwall)
{
	_start = 1;
	_level = 1;
}

Levels::Levels(Levels const &target)
{
	*this = target;
	return;
}

Levels & Levels::operator=(Levels const &target)
{
	if (this != &target)
		*this = target;
	return *this;
}

Levels::~Levels()
{
}

void	Levels::setLevel(int level)
{
	this->_level = level;
}

int  	Levels::getLevel(void)
{
	return this->_level;
}

void	Levels::setStart(int start)
{
	this->_start = start;
}

int  	Levels::getStart(void)
{
	return this->_start;
}

std::vector<GLfloat> & Levels::getListOfWalls()
{
	return _listOfWalls;
}

void	Levels::advanceToLevelTwo()
{
	if ((_player->get_yPos() < 0.726 && _player->get_yPos() > 0.6) 
		&& (_player->get_xPos() > -0.8844 && _player->get_xPos() < -0.8240))
		{
			_player->set_P_origin();
			_start++;
			_level = 2;
		}
}

void	Levels::advanceToLevelThree()
{
	if ((_player->get_yPos() < 0.726 && _player->get_yPos() > 0.6) 
		&& (_player->get_xPos() > -0.8844 && _player->get_xPos() < -0.8240))
		{
			_player->set_P_origin();
			_start++;
			_level = 3;
		}
}

void	Levels::advanceToLevelWin()
{
	if ((_player->get_yPos() < 0.726 && _player->get_yPos() > 0.6) 
		&& (_player->get_xPos() > -0.8844 && _player->get_xPos() < -0.8240))
		{
			_start++;
			_level = 4;
		}
}

void Levels::levelOneInit()
{
	_portal.init();
	_wall.init();
	_destructible.init1();
	_player->setWalls(_wall.getWalls());
	_player->setWalls(_destructible.getWalls());
	_player->setDestructible(_destructible);
    _listOfWalls = _player->getDestructible().getDestructibles();
}

void Levels::levelTwoInit()
{
	_listOfWalls.assign(_listOfWalls.size(), 10);
	_portal.init();
	_destructible.init2();
	//_player->set_P_origin();
	_player->refresh();
	_player->setWalls(_wall.getWalls());
	_player->setWalls(_destructible.getWalls());
	_player->setDestructible(_destructible);
    _listOfWalls = _player->getDestructible().getDestructibles();
}

void Levels::levelThreeInit()
{
	_listOfWalls.assign(_listOfWalls.size(), 10);
	_portal.init();
	_destructible.init3();
	_player->refresh();
	_player->setWalls(_wall.getWalls());
	_player->setWalls(_destructible.getWalls());
	_player->setDestructible(_destructible);
    _listOfWalls = _player->getDestructible().getDestructibles();
}

Destructible Levels::getDestructible(void)
{
	return _destructible;
}

Player * Levels::getPlayer()
{
	return _player;
}

Portal Levels::getPortal()
{
	return _portal;
}

StaticWall Levels::getStaticWall()
{
	return _wall;
}

/*void Levels::loadLevel()
{
	if(this->_level == 1)
		_destructibles.init1();
	else if (this->_level == 2)
		_destructibles.init2();
	else if (this->_level == 3)
		_destructibles.init3();
}*/

/*void Levels::level2Destructible()
{
	std::vector<GLfloat>::iterator it;
    std::vector<GLfloat>::iterator itEnd;
    int start;
    int end;
	int destNo[13] = {2, 3, 5, 10, 15, 20, 25, 30, 35, 41, 42, 43, 45};

    for (int loop = 0; loop < 13; loop++)
    {
    	start = 180 * (destNo[loop] - 1);
    	end = start + 180;

    	it = dest.begin() + start;
    	itEnd = dest.begin() + end;

    	while(it != itEnd)
    	{
	    	_destructibles.erase(it);
	    	_destructibles.insert(it, 10);
	    	++it;
    	}
    }
}*/

/*void Levels::level3Destructible()
{

}*/