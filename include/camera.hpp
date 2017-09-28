#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Bomberman.hpp"

class Camera 
{
	private:
		glm::vec3 _pos;
    	glm::vec3 _front;
    	glm::vec3 _up;
		glm::quat _orient;
    
    //=================================================
        glm::mat4 _view;
        glm::mat4 _model;
        glm::mat4 _projection;
        unsigned int _modelLoc;
        float _cameraSpeed;
    float _currentFrame;
    float _deltaTime;
    float _lastFrame;
    GLFWwindow *_window;
    //=================================================
		Camera();

	public:
        Camera(const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up, GLFWwindow *window);
		Camera(Camera const & target);
		Camera &operator =(Camera const & target);
		~Camera();

		const glm::vec3 &getPosition(void) const;
		const glm::vec3 &getCameraUp(void) const;
		const glm::vec3 &getCameraFront(void) const;
		const glm::quat &getOrientation(void) const;
        void  processKeyInput();
        void cameraTimeLogic();
		glm::mat4 look(void) const;
		void perspectiveView(GLuint shadersID);
		void cameraFunction(GLuint shadersID);
        glm::mat4 cameraRotate(glm::mat4 model);
		void translate(const glm::vec3 &v);
		void translate(float x, float y, float z);
		void rotate(float angle, const glm::vec3 &axis);
		void rotate(float angle, float x, float y, float z);
		void yaw(float angle);
		void pitch(float angle);
		void roll(float angle);
};

#endif
