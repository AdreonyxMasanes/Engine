#include <iostream>
#include <GLAD/include/glad/glad.h>
#include <OPENGL/glfw-3.4/include/GLFW/glfw3.h>
#include <GLM/glm-1.0.1-light/glm/glm.hpp>
#include <GLM/glm-1.0.1-light/glm/gtc/matrix_transform.hpp>
#include <GLM/glm-1.0.1-light/glm/gtc/type_ptr.hpp>
#include <vector>
#include <memory>

#include <texture.h>
#include <shader.h>
#include <vbo.h>
#include <vao.h>
#include <ebo.h>
#include <object.h>
#include <enums.h>



void framebufferSizeCallbackFunction(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void changeSelected(SELECTION_DIRECTION dir);

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const char* TITLE = "OPENGL SAMPLE";

std::vector<std::shared_ptr<object>> objects;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float totalFrames = 0.0f;
float lastKeyInputFrame = 0.0f;

bool isTransforming = false;

std::shared_ptr<object> selectedObject;


const GLfloat verticies[] =
{	// FRONT FACE
	-0.0f, -0.0f, 0.0f,			0.0f, 0.0f,
	 1.0f, -0.0f, 0.0f,			1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,			1.0f, 1.0f,

	 1.0f,  1.0f, 0.0f,			1.0f, 1.0f,
	-0.0f,  1.0f, 0.0f,			0.0f, 1.0f,
	-0.0f, -0.0f, 0.0f,			0.0f, 0.0f,

	// BACK FACE
	-0.0f, -0.0f, -0.5f,		0.0f, 0.0f,
	 1.0f, -0.0f, -0.5f,		1.0f, 0.0f,
	 1.0f,  1.0f, -0.5f,		1.0f, 1.0f,

	 1.0f,  1.0f, -0.5f,		1.0f, 1.0f,
	-0.0f,  1.0f, -0.5f,		0.0f, 1.0f,
	-0.0f, -0.0f, -0.5f,		0.0f, 0.0f,

	// TOP FACE
	-0.0f,  1.0f, -0.0f,		0.0f, 0.0f,
	 1.0f,  1.0f, -0.0f,		1.0f, 0.0f,
	 1.0f,  1.0f, -0.5f,		1.0f, 1.0f,

	 1.0f,  1.0f, -0.5f,		1.0f, 1.0f,
	-0.0f,  1.0f, -0.5f,		0.0f, 1.0f,
	-0.0f,  1.0f, -0.0f,		0.0f, 0.0f,

	// BOTTOM FACE
	-0.0f, -0.0f, -0.0f,		0.0f, 0.0f,
	 1.0f, -0.0f, -0.0f,		1.0f, 0.0f,
	 1.0f, -0.0f, -0.5f,		1.0f, 1.0f,

	 1.0f, -0.0f, -0.5f,		1.0f, 1.0f,
	-0.0f, -0.0f, -0.5f,		0.0f, 1.0f,
	-0.0f, -0.0f, -0.0f,		0.0f, 0.0f,

	// LEFT FACE
	-0.0f, -0.0f, -0.5f,		0.0f, 0.0f,
	-0.0f, -0.0f, -0.0f,		1.0f, 0.0f,
	-0.0f,  1.0f, -0.0f,		1.0f, 1.0f,

	-0.0f,  1.0f, -0.0f,		1.0f, 1.0f,
	-0.0f,  1.0f, -0.5f,		0.0f, 1.0f,
	-0.0f, -0.0f, -0.5f,		0.0f, 0.0f,

	// RIGHT FACE
	 1.0f, -0.0f, -0.0f,		0.0f, 0.0f,
	 1.0f, -0.0f, -0.5f,		1.0f, 0.0f,
	 1.0f,  1.0f, -0.5f,		1.0f, 1.0f,

	 1.0f,  1.0f, -0.5f,		1.0f, 1.0f,
	 1.0f,  1.0f, -0.0f,		0.0f, 1.0f,
	 1.0f, -0.0f, -0.0f,		0.0f, 0.0f,

};





int main()
{
	srand(time(NULL));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD FAILED TO INIT" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallbackFunction);

	shader shaderProgram("Resource Files/Shaders/Vertex/default.vert", "Resource Files/Shaders/Fragment/default.frag");
	vao VAO;
	VAO.bind();

	vbo VBO(verticies, sizeof(verticies));
	// USING INDICIES
	//ebo EBO(indicies, sizeof(indicies));
	
	// VBO, LAYOUT, COMPONENTS, TYPE, SIZE OF ONE VECTOR, OFFSET
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	texture crateTexture("Resource Files/Textures/CRATE.png");

	
	for (int i = 0; i < 2; i++)
	{
		std::shared_ptr<object> obj(new object(shaderProgram, i));
		if (i == 0)
		{
			obj->isSelected = true;
			selectedObject = obj;
		}
		objects.push_back(obj);

	}

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		totalFrames++;
		// per-frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		


		VAO.bind();
		for (std::shared_ptr<object> obj : objects)
		{
			// CHECKS ITS SELF. SHOULD MAKE MANAGER AND USE IDS TO PREVENT
			
			obj->draw();
		}

 		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	VAO.unbind();
	VAO.destroy();
	VBO.destroy();
	glfwTerminate();
	return 0;
}

void framebufferSizeCallbackFunction(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// TODO WHY DOESNT ONE GET SELECTED AND EVENTURALLY FRAMECOUNT WILL CRASH THE PROGRAM

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	
	// I AM SURE THIS IS NOT EFFICIENT
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (isTransforming)
		{
			selectedObject->translateObj(deltaTime, DIRECTION::DIRECTION_LEFT, objects);
		}
		else
		{
			changeSelected(SELECTION_DIRECTION::SELECTION_LEFT);
		}
		
	}

	// I AM SURE THIS IS NOT EFFICIENT
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (isTransforming)
		{
			selectedObject->translateObj(deltaTime, DIRECTION::DIRECTION_RIGHT, objects);
		}
		else
		{
			changeSelected(SELECTION_DIRECTION::SELECTION_RIGHT);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (isTransforming)
		{
			switch(selectedObject->state)
			{
				case TRANSFORM::TRANSFORM_SCALING:
				{
					selectedObject->scaleObj(deltaTime, DIRECTION::DIRECTION_UP);
				}
				break;
				case TRANSFORM::TRANSFORM_TRANSLATING:
				{
					selectedObject->translateObj(deltaTime, DIRECTION::DIRECTION_BACK, objects);
				}
				break;
			}
		}
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (isTransforming)
		{
			switch (selectedObject->state)
			{
				case TRANSFORM::TRANSFORM_SCALING:
				{
					selectedObject->scaleObj(deltaTime, DIRECTION::DIRECTION_DOWN);
				}
				break;
				case TRANSFORM::TRANSFORM_TRANSLATING:
				{
					selectedObject->translateObj(deltaTime, DIRECTION::DIRECTION_FORWARD, objects);
				}
				break;
			}
		}
		else
		{
			if (selectedObject->state == TRANSFORM::TRANSFORM_SCALING)
			{
				selectedObject->state = TRANSFORM::TRANSFORM_IDLE;
				isTransforming = false;
			}
			else
			{
				selectedObject->state = TRANSFORM::TRANSFORM_SCALING;
				isTransforming = true;
			}
		}
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (isTransforming)
		{
			selectedObject->translateObj(deltaTime, DIRECTION::DIRECTION_UP, objects);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (isTransforming)
		{
			selectedObject->translateObj(deltaTime, DIRECTION::DIRECTION_DOWN, objects);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		if (selectedObject->state == TRANSFORM::TRANSFORM_TRANSLATING)
		{
			selectedObject->state = TRANSFORM::TRANSFORM_IDLE;
			isTransforming = false;
		}
		else
		{
			selectedObject->state = TRANSFORM::TRANSFORM_TRANSLATING;
			isTransforming = true;
		}
	}
	// DEBUG XD
	/*
	switch (selectedObject->state)
	{
		case TRANSFORM_IDLE:
		{
			std::cout << "Current State: SELECTING" << std::endl;
		}
		break;

		case TRANSFORM_TRANSLATING:
		{
			std::cout << "Current State: TRANSLATING" << std::endl;
		}
		break;

		case TRANSFORM_SCALING:
		{
			std::cout << "Current State: SCALING" << std::endl;
		}
		break;

		case TRANSFORM_ROTATING:
		{
			std::cout << "Current State: ROTATING" << std::endl;
		}
		break;
	}
	*/
}

void changeSelected(SELECTION_DIRECTION dir)
{
	switch (dir)
	{
	case SELECTION_DIRECTION::SELECTION_RIGHT:
		{
			if (totalFrames - lastKeyInputFrame > 60)
			{
				lastKeyInputFrame, totalFrames = 0;
				for (int i = 0; i < objects.size(); i++)
				{
					if (objects[i]->isSelected == true)
					{
						if (i == objects.size() - 1)
						{
							objects[i]->isSelected = false;
							objects[0]->isSelected = true;
							selectedObject = objects[0];
						}
						else
						{
							objects[i]->isSelected = false;
							objects[i + 1]->isSelected = true;
							selectedObject = objects[i + 1];
						}
						break;
					}
				}
			}
		}
		break;

		case SELECTION_DIRECTION::SELECTION_LEFT:
		{
			if (totalFrames - lastKeyInputFrame > 60)
			{
				lastKeyInputFrame, totalFrames = 0;
				for (int i = 0; i < objects.size(); i++)
				{
					if (objects[i]->isSelected == true)
					{
						if (i == 0)
						{
							objects[i]->isSelected = false;
							objects[objects.size() - 1]->isSelected = true;
							selectedObject = objects[i];
						}
						else
						{
							objects[i]->isSelected = false;
							objects[i - 1]->isSelected = true;
							selectedObject = objects[i - 1];
						}
						// Breaks from loop after finding the selected one.
						break;
					}
				}
			}
		}
		break;
	}
}
