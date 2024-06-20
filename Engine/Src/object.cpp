#include "object.h"

//TODO: MAKE MANAGER
//TODO: PREVENT FROM SPAWNING INSIDE OF EACH OTHER
object::object(shader defaultShader, int ID)
{
	m_defaultShader = defaultShader;
	// MAKE INTO A VECTOR TODO:
	x = randomFloat(-2.0f, 2.0f);
	y = randomFloat(-2.0f, 2.0f);
	z = randomFloat(-2.0f, 2.0f);

	// MAKE INTO A VECTOR TODO:
	r = randomFloat(-0.5f, 0.5f);
	g = randomFloat(-0.5f, 0.5f);
	b = randomFloat(-0.5f, 0.5f);
	
	mass = randomFloat(0.0f, 5.0f);

	moveSpeed = randomFloat(1.0f, 2.5f);

	color = glm::vec3(r, g, b);
	selectedColor = color;
	id = ID;

}

object::object()
{
	// MAKE INTO A VECTOR TODO:
	x = randomFloat(-0.5f, 0.5f);
	y = randomFloat(-0.5f, 0.5f);
	z = randomFloat(-0.5f, 0.5f);

	// MAKE INTO A VECTOR TODO:
	r = randomFloat(-0.5f, 0.5f);
	g = randomFloat(-0.5f, 0.5f);
	b = randomFloat(-0.5f, 0.5f);

	mass = randomFloat(0.0f, 5.0f);

	color = glm::vec3(r, g, b);
	selectedColor = color;
}

void object::draw()
{
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	proj = glm::perspective(glm::radians(90.0f), (float)800/ (float)600, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, -0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(scale));
	model = glm::translate(model, glm::vec3(x, y, z));


	m_defaultShader.use();
	unsigned int modelUniLoc = glGetUniformLocation(m_defaultShader.ID, "model");
	glUniformMatrix4fv(modelUniLoc, 1, GL_FALSE, glm::value_ptr(model));

	unsigned int viewUniLoc = glGetUniformLocation(m_defaultShader.ID, "view");
	glUniformMatrix4fv(viewUniLoc, 1, GL_FALSE, glm::value_ptr(view));

	unsigned int projUniLoc = glGetUniformLocation(m_defaultShader.ID, "proj");
	glUniformMatrix4fv(projUniLoc, 1, GL_FALSE, glm::value_ptr(proj));

	unsigned int colorUniLoc = glGetUniformLocation(m_defaultShader.ID, "color");
	
	selection(colorUniLoc);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void object::scaleObj(float deltaTime, DIRECTION dir)
{
	float scalar = 0.1 * deltaTime;
	switch (dir)
	{
		case DIRECTION_UP:
		{
			scale += scalar;
		}
		break;

		case DIRECTION_DOWN:
		{
			scale -= scalar;
		}
		break;
	}
}

bool object::checkCollisions(std::shared_ptr<object> objTwo)
{
	return(
		x <= objTwo->x + 1.0f &&
		x + 1.0f >= objTwo->x &&
		y <= objTwo->y + 1.0f &&
		y + 1.0f >= objTwo->y &&
		z <= objTwo->z + 0.5f &&
		z + 0.5f >= objTwo->z
		);
}

float object::randomFloat(float a, float b)
{
	
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void object::selection(unsigned int colorLoc)
{
	if (isSelected)
	{
		if (selectedColor.r > 1.0f && selectedColor.g > 1.0f && selectedColor.b > 1.0f)
		{
			reversing = true;
		}
		else if (selectedColor.r < color.r && selectedColor.g < color.g && selectedColor.b < color.b)
		{
			reversing = false;
		}

		if (reversing)
		{
			selectedColor -= glm::vec3(0.01f, 0.01f, 0.01f);
		}
		else
		{
			selectedColor += glm::vec3(0.01f, 0.01f, 0.01f);
		}
		glUniform3fv(colorLoc, 1, glm::value_ptr(selectedColor));
	}
	else
	{
		glUniform3fv(colorLoc, 1, glm::value_ptr(color));
	}
}

void object::resolveCollision(std::shared_ptr<object> objTwo)
{
	float resitance = 0.5f;
	float massA = mass;
	float massB = objTwo->mass;

	velocity = (resitance * massB * (objTwo->velocity - velocity) + massA * velocity + massB * objTwo->velocity) / massA + massB;
	objTwo->velocity = (resitance * massA * (velocity - objTwo->velocity) + massA * velocity + massB * objTwo->velocity) / massA + massB;

}


void object::translateObj(float deltaTime, DIRECTION dir, std::vector<std::shared_ptr<object>>& objects)
{
	velocity = moveSpeed * deltaTime;
	switch (dir)
	{
		// STOP FROM GOING TO EDGES
		case DIRECTION_LEFT:
		{
			x -= velocity;
			for (std::shared_ptr<object> obj : objects)
			{
				if (id != obj->id)
				{
					if (checkCollisions(obj))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//x += velocity;
						//obj->x -= velocity;
						resolveCollision(obj);
						obj->translateObj(deltaTime, dir, objects);
					}
				}
			}
		}
		break;
		case DIRECTION_RIGHT:
		{
			x += velocity;
			for (std::shared_ptr<object> obj : objects)
			{
				if (id != obj->id)
				{
					if (checkCollisions(obj))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//x -= velocity;
						//obj->x += velocity;
						resolveCollision(obj);
						obj->translateObj(deltaTime, dir, objects);
					}
				}
			}
		}
		break;
		case DIRECTION_UP:
		{
			y += velocity;
			for (std::shared_ptr<object> obj : objects)
			{
				if (id != obj->id)
				{
					
					if (checkCollisions(obj))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//y -= velocity;
						//obj->y += velocity;
						resolveCollision(obj);
						obj->translateObj(deltaTime, dir, objects);
					}
				}
			}

		}
		break;
		case DIRECTION_DOWN:
		{
			y -= velocity;
			for (std::shared_ptr<object> obj : objects)
			{
				if (id != obj->id)
				{
					
					if (checkCollisions(obj))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//y += velocity;
						//obj->y -= velocity;
						resolveCollision(obj);
						obj->translateObj(deltaTime, dir, objects);
					}
				}
			}
		}
		break;
		case DIRECTION_FORWARD:
		{
			z += velocity;
			for (std::shared_ptr<object> obj : objects)
			{
				if (id != obj->id)
				{
					if (checkCollisions(obj))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//z -= velocity;
						//obj->z += velocity;
						resolveCollision(obj);
						obj->translateObj(deltaTime, dir, objects);
					}
				}
			}
		}
		break;
		case DIRECTION_BACK:
		{
			z -= velocity;
			for (std::shared_ptr<object> obj : objects)
			{
				if (id != obj->id)
				{
					if (checkCollisions(obj))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//z += velocity;
						//obj->z -= velocity;
						resolveCollision(obj);
						obj->translateObj(deltaTime, dir, objects);
					}
				}
			}
		}
		break;
	}
}
