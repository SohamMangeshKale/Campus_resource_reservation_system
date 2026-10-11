#include "resource_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

ResourceManager::ResourceManager() {
	count = 0;
}	
bool ResourceManager::loadFromFile(const std::string& filename) {
	std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: couldn't open file" << filename << std::endl;
        return false;
    }
	
	std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (count >= MAX_RESOURCES) break;
 
        std::stringstream ss(line);
        std::string idStr, name, totalStr;
 
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, totalStr, ',');
 
        if (idStr.empty() || name.empty() || totalStr.empty()) continue;
		
		
		Resource r;
        r.id = std::stoi(idStr);
        r.name = name;
        r.totalUnits = std::stoi(totalStr);
        r.availableUnits = r.totalUnits;
 
        resources[count] = r;
        count++;
    }
 
    file.close();
    return true;
}


void ResourceManager::displayAllResources() const {
    if (count == 0) {
        std::cout << "No, resouces isn't loading.\n";
        return;
    }
    std::cout << "\n--- All Resources ---\n";
    for (int i = 0; i < count; i++) {
        std::cout << "ID: " << resources[i].id << " | Name: " << resources[i].name << " | Total: " << resources[i].totalUnits << " | Available: " << resources[i].availableUnits << std::endl;
    }
}


void ResourceManager::displayAvailability(int resourceID) const {
    for (int i = 0; i < count; i++) {
        if (resources[i].id == resourceID) {
            std::cout << resources[i].name << " has " << resources[i].availableUnits << " / " << resources[i].totalUnits << " units available.\n";
            return;
        }
    }
    std::cout << "Resource ID " << resourceID << " not found.\n";
}
 
Resource* ResourceManager::findResource(int resourceID) {
    for (int i = 0; i < count; i++) {
        if (resources[i].id == resourceID) {
            return &resources[i];
        }
    }
    return nullptr;
}
 
bool ResourceManager::decreaseAvailability(int resourceID, int qty) {
    Resource* r = findResource(resourceID);
    if (r == nullptr) return false;
    if (r->availableUnits < qty) return false;
    r->availableUnits -= qty;
    return true;
}
 
bool ResourceManager::increaseAvailability(int resourceID, int qty) {
    Resource* r = findResource(resourceID);
    if (r == nullptr) return false;
    r->availableUnits += qty;
    if (r->availableUnits > r->totalUnits) {
        r->availableUnits = r->totalUnits;
    }
    return true;
}
 
int ResourceManager::getCount() const {
    return count;
}
 
Resource ResourceManager::getResourceAt(int index) const {
    if (index < 0 || index >= count) {
        Resource empty = {-1, "INVALID", 0, 0};
        return empty;
    }
    return resources[index];
}