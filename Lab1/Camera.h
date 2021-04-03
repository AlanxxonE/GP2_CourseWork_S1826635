#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera(); //default constructor

	//method that initialises the camera
	//parameters: vec3 postion, float for the field of view, float for the aspect ratio, floats for the near and far clipping planes 
	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	//method that enables camera movements by assigning a new position to the current one
	void moveCamera(const glm::vec3& newPos)
	{
		this->pos = newPos;
	}

	//method that enables camera rotation by assigning a new value to the forward vector the camera is aming at
	void rotateCamera(const glm::vec3& newRot)
	{
		this->forward = newRot;
	}
	
	glm::vec3 GetPos()
	{
		return this->pos;
	}

	//method that gets a projection matrix of the camera
	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	inline glm::mat4 GetProjection() const
	{
		return projection;
	}

	inline glm::mat4 GetView() const
	{
		return glm::lookAt(pos, pos + forward, up);
	}

private:
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::mat4 projection;

};

