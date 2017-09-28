#include "Camera.hpp"

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up, GLFWwindow *window) : _pos(pos), _front(front), _up(up), _window(window)
{
    _deltaTime = 0.0f;
    _lastFrame = 0.0f;
}

Camera::Camera(Camera const & target)
{
	*this = target;
	return;
}

Camera	&	Camera::operator=(Camera const & target)
{
	if (this != &target)
		*this = target;
	return *this;
}

Camera::~Camera()
{
}

const glm::vec3	&	Camera::getPosition(void) const
{
	return this->_pos;
}

const glm::vec3 &	Camera::getCameraUp(void) const
{
	return this->_up;
}

const glm::vec3 &	Camera::getCameraFront(void) const
{
	return this->_front;
}

const glm::quat	&	Camera::getOrientation(void) const
{
	return this->_orient;
}

glm::mat4	Camera::look(void) const
{
	return glm::translate(glm::mat4_cast(_orient), _pos);
}

void    Camera::perspectiveView(GLuint shadersID)
{
    _model = glm::translate(_model, glm::vec3(-1.0f,  2.0f, -1.0f));
    _model = glm::rotate(_model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    _projection = glm::perspective(glm::radians(30.0f), (float)WIDTH / (float) HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shadersID, "projection"), 1, GL_FALSE, &_projection[0][0]);
    
    _modelLoc = glGetUniformLocation(shadersID, "model");
    glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
}

void    Camera::cameraFunction(GLuint shadersID)
{
    _view = glm::lookAt(_pos, _pos + _front, _up);
    glUniformMatrix4fv(glGetUniformLocation(shadersID, "view"), 1, GL_FALSE, &_view[0][0]);
    _model = cameraRotate(_model);
    _modelLoc = glGetUniformLocation(shadersID, "model");
    glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
}

glm::mat4 Camera::cameraRotate(glm::mat4 model)
{
    _model = model;
    return _model;
}

void Camera::processKeyInput()
{
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
    
    _cameraSpeed = 0.5 * _deltaTime;
    if (glfwGetKey(_window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        _pos += _cameraSpeed * _front;
    if (glfwGetKey(_window, GLFW_KEY_KP_SUBTRACT ) == GLFW_PRESS)
        _pos -= _cameraSpeed * _front;
}

void Camera::cameraTimeLogic()
{
    // per-frame time logic
    _currentFrame = glfwGetTime();
    _deltaTime = _currentFrame - _lastFrame;
    _lastFrame = _currentFrame;
}

void		Camera::translate(const glm::vec3 &v)
{
	_pos += v * _orient;
}

void		Camera::translate(float x, float y, float z)
{
	_pos += glm::vec3(x, y, z) * _orient;
}

void		Camera::rotate(float angle, const glm::vec3 &axis)
{
	_orient *= glm::angleAxis(angle, axis * _orient);
}

void		Camera::rotate(float angle, float x, float y, float z)
{
	_orient *= glm::angleAxis(angle, glm::vec3(x, y, z) * _orient);
}

void		Camera::yaw(float angle)
{
	rotate(angle, 0.0f, 1.0f, 0.0);
}

void		Camera::pitch(float angle)
{
	rotate(angle, 1.0f, 0.0f, 0.0f);
}

void		Camera::roll(float angle)
{
	rotate(angle, 0.0f, 0.0f, 1.0f);
}
