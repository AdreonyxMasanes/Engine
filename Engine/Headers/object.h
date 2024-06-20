#pragma once
#include <random>

#include <GLAD/include/glad/glad.h>
#include <OPENGL/glfw-3.4/include/GLFW/glfw3.h>

#include <GLM/glm-1.0.1-light/glm/glm.hpp>
#include <GLM/glm-1.0.1-light/glm/gtc/matrix_transform.hpp>
#include <GLM/glm-1.0.1-light/glm/gtc/type_ptr.hpp>

#include <enums.h>
#include "shader.h"

class object
{
public:

	// TESTING NEW BRANCH
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	float r, g, b, x, y, z;
	// change to isVERB TODO:
	// CHANGE TO ENUMS ACTUALLY TODO:
	TRANSFORM state = TRANSFORM::TRANSFORM_IDLE;
	bool isSelected = false;
	float moveSpeed = 1.5f;
	float velocity = 0;
	float scale = 0.2f;
	int id;
	float mass;



public:
	object(shader defualtShader, int ID);
	object();
	void translateObj(float deltaTime, DIRECTION dir, std::vector<std::shared_ptr<object>>& objects);
	void draw();
	void scaleObj(float deltaTime, DIRECTION dir);
	
private:
	float randomFloat(float min, float max);
private:
	glm::vec3 color;
	glm::vec3 selectedColor;
	bool reversing = false;
	shader m_defaultShader;
	void selection(unsigned int colorLoc);
	bool checkCollisions(std::shared_ptr<object> objTwo);
	void resolveCollision(std::shared_ptr<object> objTwo);
};