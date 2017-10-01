#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Bomberman.hpp"
#include "serialize.hpp"
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
	Player(std::vector<Wall> walls, Bomb *bomb);
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
    void setPlayerLife(int life);
    int getPlayerLife(void);
    void setPlayerScore(/*Enemy enemy*/);
    int getPlayerScore(void);
    void set_P_origin(void);
    void refresh();
    
    GLfloat get_xPos(void) const;
    GLfloat get_yPos(void) const;
    bool	get_isdead(void) const;
    void	set_isdead(bool death);
    void 	bomb_colision(GLfloat bx, GLfloat by);
	void setWalls(std::vector<Wall> walls);
    GLuint getPVAO() const;
    GLuint getPUVO() const;
    GLuint getPVBO() const;
	GLuint getPEBO() const;
    GLuint getPProgramId() const;
    GLuint getPTextureId() const;
	GLuint getProgramId() const;
    Player & operator=(const Player &p);
    void setCoordinates(GLfloat x, GLfloat y);
    void remove(std::vector<int> removeWalls);
	int printVector();
	void vectorToMat4();
	void mat4ToVector();
	void printMatrix(std::string s);
	std::vector<float> getModelV() const;
	void restorePosition(float x, float y);
	glm::mat4 getView() const;
	glm::mat4 getModel() const;
	glm::mat4 getProjection() const;
	unsigned int getModelLoc() const;
	unsigned int getVmodelLoc() const;
	std::vector<glm::vec3> getVertices() const;
	std::vector<glm::vec2> getUvbuffer() const;
	std::vector<glm::vec3> getNormals() const;
	int getX() const;
	int getY() const;
	std::vector<Wall> getWalls() const;

private:
    Bomb *_bomb;
    Destructible _des;
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
	int _life;
	int _score;
    bool load_result;
    bool isdead;
	std::vector<Wall> walls;
	std::vector<float> _modelV;
    template <class archive> friend
    void boost::serialization::serialize(archive &ar, Player &p, const unsigned int version);
};

#endif
