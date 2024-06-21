#include "objectManager.h"

objectManager::objectManager()
{

}

std::shared_ptr<object> objectManager::addObject(shader shader, std::string& tag)
{
	std::shared_ptr<object> o = std::shared_ptr<object>(new object(shader, totalEntities++, tag));
	objectsToAdd.push_back(o);
	return o;
}

void objectManager::removeObjects(std::vector<std::shared_ptr<object>>& objects)
{
	objects.erase(std::remove_if(begin(objects), end(objects), [](std::shared_ptr<object> o) {return o->shouldBeRemoved; }), objects.end());
}

std::vector<std::shared_ptr<object>>& objectManager::getObjects()
{
	// All entities
	return m_objects;
}

std::vector<std::shared_ptr<object>>& objectManager::getObjects(std::string& tag)
{
	// return specific objects
	return objectMap[tag];
}

void objectManager::update()
{
	for (auto& o : objectsToAdd)
	{
		m_objects.push_back(o);
		objectMap[o->m_tag].push_back(o);
	}
	
	removeObjects(m_objects);

	for (auto & pair : objectMap)
	{
		removeObjects(pair.second);
	}
	objectsToAdd.clear();
}


bool objectManager::checkCollisions(std::shared_ptr<object> objOne, std::shared_ptr<object> objTwo)
{
	return(
		objOne->x <= objTwo->x + 1.0f &&
		objOne->x + 1.0f >= objTwo->x &&
		objOne->y <= objTwo->y + 1.0f &&
		objOne->y + 1.0f >= objTwo->y &&
		objOne->z <= objTwo->z + 0.5f &&
		objOne->z + 0.5f >= objTwo->z
		);
}

void objectManager::resolveCollision(std::shared_ptr<object> objOne, std::shared_ptr<object> objTwo)
{
	float resitance = 0.0f;
	float massA = objOne->mass;
	float massB = objTwo->mass;
	//objOne->velocity = (resitance * massB * (objTwo->velocity - objOne->velocity) + massA * objOne->velocity + massB * objTwo->velocity) / (massA + massB);
	objTwo->velocity = (resitance * massA * (objOne->velocity - objTwo->velocity) + massA * objOne->velocity + massB * objTwo->velocity) / (massA + massB);

}


void objectManager::translateObj(float deltaTime, DIRECTION dir, std::shared_ptr<object> obj)
{
	obj->velocity = obj->moveSpeed * deltaTime;
	switch (dir)
	{
			// STOP FROM GOING TO EDGES
		case DIRECTION_LEFT:
		{
			obj->x -= obj->velocity;
			for (std::shared_ptr<object> objTwo : m_objects)
			{
				if (obj->id != objTwo->id)
				{
					if (checkCollisions(obj, objTwo))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//x += velocity;
						//obj->x -= velocity;
						resolveCollision(obj, objTwo);
						translateObj(deltaTime, dir, objTwo);
						obj->velocity = 0;
						objTwo->velocity = 0;
					}
				}
			}
		}
		break;
		case DIRECTION_RIGHT:
		{
			obj->x += obj->velocity;
			for (std::shared_ptr<object> objTwo : m_objects)
			{
				if (obj->id != objTwo->id)
				{
					if (checkCollisions(obj, objTwo))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//x -= velocity;
						//obj->x += velocity;
						resolveCollision(obj, objTwo);
						translateObj(deltaTime, dir, objTwo);
						obj->velocity = 0;
						objTwo->velocity = 0;
					}
				}
			}
		}
		break;
		case DIRECTION_UP:
		{
			obj->y += obj->velocity;
			for (std::shared_ptr<object> objTwo : m_objects)
			{
				if (obj->id != objTwo->id)
				{

					if (checkCollisions(obj, objTwo))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//y -= velocity;
						//obj->y += velocity;
						resolveCollision(obj, objTwo);
						translateObj(deltaTime, dir, objTwo);
						obj->velocity = 0;
						objTwo->velocity = 0;
					}
				}
			}

		}
		break;
		case DIRECTION_DOWN:
		{
			obj->y -= obj->velocity;
			for (std::shared_ptr<object> objTwo : m_objects)
			{
				if (obj->id != objTwo->id)
				{

					if (checkCollisions(obj, objTwo))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//y += velocity;
						//obj->y -= velocity;
						resolveCollision(obj, objTwo);
						translateObj(deltaTime, dir, objTwo);
						obj->velocity = 0;
						objTwo->velocity = 0;
					}
				}
			}
		}
		break;
		case DIRECTION_FORWARD:
		{
			obj->z += obj->velocity;
			for (std::shared_ptr<object> objTwo : m_objects)
			{
				if (obj->id != objTwo->id)
				{
					if (checkCollisions(obj, objTwo))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//z -= velocity;
						//obj->z += velocity;
						resolveCollision(obj, objTwo);
						translateObj(deltaTime, dir, objTwo);
						obj->velocity = 0;
						objTwo->velocity = 0;
					}
				}
			}
		}
		break;
		case DIRECTION_BACK:
		{
			obj->z -= obj->velocity;
			for (std::shared_ptr<object> objTwo : m_objects)
			{
				if (obj->id != objTwo->id)
				{
					if (checkCollisions(obj, objTwo))
					{
						// PREVENT MOVING INSIDE
						//std::cout << "Collison Detected" << std::endl;
						//z += velocity;
						//obj->z -= velocity;
						resolveCollision(obj, objTwo);
						translateObj(deltaTime, dir, objTwo);
						obj->velocity = 0;
						objTwo->velocity = 0;
					}
				}
			}
		}
		break;
	}
	
}