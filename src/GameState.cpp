#include "GameState.hpp"

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::operator=(const GameState &rhs)
{
    if (this != &rhs)
        *this = rhs;
    return;
}

void GameState::cleanUpSave()
{
    std::ofstream ofs("gamestate/player.dat", std::ofstream::trunc);
    ofs.close();
}

bool GameState::isEmpty(std::ifstream &ifs)
{
    return (ifs.peek() == std::ifstream::traits_type::eof());
}

int GameState::savePlayerState(Player &p)
{
    mkdir("gamestate", 0777);
    std::ofstream ofs("gamestate/player.dat");
    if (ofs.is_open())
    {
        {
            boost::archive::text_oarchive oa(ofs);
            oa << p;
        }
    }
    return (0);
}

int GameState::loadPlayerState(Player *p)
{
    Player p2;

    std::ifstream ifs("gamestate/player.dat");
    if (!isEmpty(ifs))
    {
        if (ifs.is_open())
        {
            {
                boost::archive::text_iarchive ia(ifs);
                ia >> p2;
            }
            (*p) = p2;
        }
    //     std::cout << "" << std::endl;
    //     std::cout << "" << std::endl;
    //     std::cout << "**************************************" << std::endl;
    //     std::cout << "************* Debugging **************" << std::endl;
    //     std::cout << "p.xPos: " << p->get_xPos() << " p.yPos: " << p->get_yPos() << std::endl;
    //     std::cout << "**************************************" << std::endl;
    //     std::cout << "" << std::endl;
    //     std::cout << "" << std::endl;
    }
    else
        std::cout << "file doe not exit or is empty" << std::endl;
    return (0);
}

int GameState::saveWallState(Wall &w)
{
    mkdir("gamestate", 0777);
    std::ofstream ofs("gamestate/wall.dat");
    if (ofs.is_open())
    {
        {
            boost::archive::text_oarchive oa(ofs);
            oa << w;
        }
    }
    return (0);
}

int GameState::loadWallState(Wall *w)
{
    Wall w2;

    std::ifstream ifs("gamestate/wall.dat");
    if (!isEmpty(ifs))
    {
        if (ifs.is_open())
        {
            {
                boost::archive::text_iarchive ia(ifs);
                ia >> w2;
            }
            (*w) = w2;
        }
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "**************************************" << std::endl;
        std::cout << "************* Debugging **************" << std::endl;
        std::cout << "w.xPos: " << w->getXPos() << " w.yPos: " << w->getYPos() << std::endl;
        std::cout << "**************************************" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
    }
    return (0);
}