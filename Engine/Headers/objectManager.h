#pragma once
#include <object.h>
#include <memory>
#include <vector>
#include <map>


class objectManager
{
private:
	// ITEM TAG, LIST OF THAT ITEM
	std::map < std::string, std::vector<std::shared_ptr<object>>> objectMap;
	std::vector<std::shared_ptr<object>> m_objects;
	std::vector<std::shared_ptr<object>> objectsToAdd;


	size_t totalEntities = 0;
private:
	void removeObjects(std::vector<std::shared_ptr<object>>& objects);
public:
	objectManager();

	std::shared_ptr<object> addObject(shader shader, std::string& tag);
	std::vector<std::shared_ptr<object>>& getObjects();
	std::vector<std::shared_ptr<object>>& getObjects(std::string& tag);

	bool checkCollisions(std::shared_ptr<object> objOne, std::shared_ptr<object> objTwo);
	void resolveCollision(std::shared_ptr<object> objOne, std::shared_ptr<object> objTwo);
	void translateObj(float deltaTime, DIRECTION dir, std::shared_ptr<object> obj);
	void update();

};