#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H


#include "structures.h"
#include <string>


const int MAX_RESOURCES = 100;

class ResourceManager {
private:
	Resource resources[MAX_RESOURCES];
	int count;
	
public:
	ResourceManager();
	bool loadFromFile(const std::string& filename);
	void displayAllResources() const;	
	void displayAvailability(int resourceID) const;
	Resource* findResource(int resourceID);
	bool decreaseAvailability(int resourceID, int qty);
	bool increaseAvailability(int resourceID, int qty);
	int getCount() const;

	Resource getResourceAt(int index) const;
};



#endif		