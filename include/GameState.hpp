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
        void operator=(const GameState &rhs);
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
            ar & p.get_xPos();
            ar & p.get_yPos();
            ar & p.getPVAO();
            ar & p.getPUVO();
            ar & p.getPEBO();
            ar & p.getProgramId();
            ar & p.getPTextureId();
        }
    }
}

#endif
