#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Player.hpp"
#include "Wall.hpp"
#include "Bomberman.hpp"

class GameState {
    public:
        GameState();
        ~GameState();
        void cleanUpSave();
        int loadPlayerState(Player *p);
        int savePlayerState(Player &p);
        int loadWallState(Wall *w);
        int saveWallState(Wall &w);
        void operator=(const GameState &rhs);
        bool isEmpty(std::ifstream &ifs);

    private:
};

#endif
