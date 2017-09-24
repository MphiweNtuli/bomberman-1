#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Player.hpp"
#include "Bomberman.hpp"

class GameState {
    public:
        GameState();
        ~GameState();
        void cleanUpSave();
        int loadPlayerState(Player *p);
        int savePlayerState(Player &p);
        void operator=(GameState *rhs);
        bool isEmpty(std::ifstream &ifs);

    private:
};

namespace boost
{
    namespace serialization
    {
        template <class archive>
        void serialize(archive &ar, Player &p, const unsigned int version)
        {
            ar & p.xPos;
            ar & p.yPos;
            ar & p.pVAO;
            ar & p.pVBO;
            ar & p.pEBO;
            ar & p.programID;
            ar & p.pTextureId;
        }
    }
}

#endif