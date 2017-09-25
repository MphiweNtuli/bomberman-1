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
        //     // ar & p.texture_programID;
        //     // ar & p.pUVO;
        //     // ar & p.pVAO;
        //     // ar & p.pVBO;
        //     // ar & p.pEBO;
        //     // ar & p.pTextureId;
        //     // ar & p.programID;
        //     // ar & p._modelLoc;
        //     // ar & p._vmodelLoc;

        //     // ar & p._vertices;
        //     // ar & p._uvbuffer;
        //     // ar & p.normals;
            
        //     // ar & p.x;
        //     // ar & p.y;
        //     // ar & p.walls;
        }

        template <class archive>
        void serialize(archive &ar, Wall &w, const unsigned int version)
        {
            ar & w.xPos;
            ar & w.yPos;
            // ar & w.isDestructable;
            // ar & w.VertexArrayID;
            // ar & w.vertexbuffer;
            // ar & w.wallTexture;
            // ar & w.elementBuffer;
        }
    }
}

#endif
