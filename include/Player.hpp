#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Bomberman.hpp"
#include "camera.hpp"
#include "loader.hpp"
#include "Bomb.hpp"
#include "Destructible.hpp"

#define WALL 0.08f
#define PLAYER 0.1f
#define OFS_X 0.017f
#define OFS_Y -0.02f

class Player
{
public:
    Player();
	Player(std::list<Wall> walls, Bomb *bomb);
	~Player();
	void init();
	bool moveUp(); 
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	void transform();
	void player_callback(GLFWwindow* window);
	void draw();
    void setDestructible(Destructible destructible);
    Destructible getDestructible(void);
    void setDestructible01(Destructible destructible01);
    Destructible getDestructible01(void);
    
    GLfloat get_xPos(void) const;
    GLfloat get_yPos(void) const;
	void setWalls(std::list<Wall> walls);
    
    /* emsimang: experimental code*/
    GLuint getPVAO() const;
    GLuint getPUVO() const;
    GLuint getPEBO() const;
    GLuint getPTextureId() const;
    GLuint getProgramId() const;
    void operator=(const Player &p);
    void setCoordinates(GLfloat x, GLfloat y);
    void remove(std::list<int> removeWalls);
    /* emsimang: experimental code*/
    
private:
    Bomb *_bomb;
    Destructible _des, _des01;
	GLfloat xPos, yPos;
	GLuint texture_programID, pUVO, pVAO, pVBO, pEBO, pTextureId, programID;
	glm::mat4 _view;
    glm::mat4 _model;
    glm::mat4 _projection;
	unsigned int _modelLoc;
	unsigned int _vmodelLoc;
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec2> _uvbuffer;
	std::vector<glm::vec3> normals;
	int x;
	int y;
    bool load_result;
	std::list<Wall> walls;
    template <class archive> friend
    void boost::serialization::serialize(archive &ar, Player &p, const unsigned int version);
};

#endif
