ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H


#include "structures.h"
#inclucde <string>


const int MAX_RESOURCES = 100;

class ResourceManager {
private:
	Resource resources[MAX_RESOURCES];
	int count;
	
public:
	ResourcesManager();
	bool loadFormFile(const std::string& filename);
	void displayALLResources() const;	
	void displayAvailability(int resourceID) const;
	Resource* findResource(int resourceID);
	bool decreaseAvailability(int resourceID, int qty);
	bool increaseAvailability(int resourceID, int qty);
	int getCount() const;
};



#endif		