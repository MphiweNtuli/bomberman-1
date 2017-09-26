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

namespace boost
{
    namespace serialization
    {
        template <class archive>
        void serialize(archive &ar, Player &p, const unsigned int version)
        {
            unsigned int vers;

            ar & p.yPos;
            ar & p.xPos;
            vers = version;
        }

        template <class archive>
        void serialize(archive &ar, Wall &w, const unsigned int version)
        {
            unsigned int vers;

            ar & w.xPos;
            ar & w.yPos;
            // ar & w.isDestructable;
            // ar & w.VertexArrayID;
            // ar & w.vertexbuffer;
            // ar & w.wallTexture;
            // ar & w.elementBuffer;
            vers = version;
        }
    }
}

#endif
