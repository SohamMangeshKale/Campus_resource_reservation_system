#include "reservation_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

ReservationManager :: ReservationManager(){
	head = nullptr;
	nextReservationID = 1;
	}
	
ReservationManager::~ReservationManager() {
    Reservation* current = head;
    while (current != nullptr) {
        Reservation* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

//idhar create wala hai, use this

bool ReservationManager::createReservation(int resourceID, const std::string& studentName,int quantity, ResourceManager& rm, Waitlist& wl) {
    if (!validateRequest(resourceID, quantity, rm)) {
        return false;
    }
 
    Resource* r = rm.findResource(resourceID);
 
    if (r->availableUnits < quantity) {
		
        std::cout << "Not enough availability. Adding " << studentName << " to the waitlist for " << r->name << ".\n";
        wl.addToWaitlist(resourceID, studentName, quantity);
        return false;
    }
 
    rm.decreaseAvailability(resourceID, quantity);
    Reservation* newRes = new Reservation;
    newRes->reservationID = nextReservationID++;
    newRes->resourceID = resourceID;
    newRes->studentName = studentName;
    newRes->quantity = quantity;
 
    newRes->next = head;
    head = newRes;
 
    std::cout << "Reservation has been created, ID:" << newRes->reservationID << std::endl;
    return true;
}


bool ReservationManager::validateRequest(int resourceID, int quantity, ResourceManager& rm) const {
    if (quantity <= 0) {
        std::cout << "Invalid request.\n";
        return false;
    }
    Resource* r = rm.findResource(resourceID);
    if (r == nullptr) {
        std::cout << "Invalid request: resource ID " << resourceID << " does not exist.\n";
        return false;
    }
 
    return true;
}

bool ReservationManager::cancelReservation(int reservationID, ResourceManager& rm, HistoryStack& hist) {
    Reservation* current = head;
    Reservation* previous = nullptr;
 
	// list me dekhna hai, 0(n) 
    while (current != nullptr && current->reservationID != reservationID) {
        previous = current;
        current = current->next;
    }
 
    if (current == nullptr) {
        std::cout << "Reservation ID " << reservationID << " could not be found.\n";
        return false;
    }
 
    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    rm.increaseAvailability(current->resourceID, current->quantity);
 
    hist.push(*current); //save kiya copy badme keliye
 
    std::cout << "Reservation ID " << reservationID << " cancelled.\n";
 
    delete current;
    return true;
}

void ReservationManager::displayActiveReservations() const {
    if (head == nullptr) {
        std::cout << "No active reservations as of now.\n";
        return;
    }
 
    std::cout << "\n--- Active Reservations ---\n";
    Reservation* current = head;
    while (current != nullptr) {
        std::cout << "Reservation ID: " << current->reservationID<< " | Resource ID: " << current->resourceID<< " | Student: " << current->studentName<< " | Quantity: " << current->quantity << std::endl;
        current = current->next;
    }
}

int ReservationManager::getActiveCount() const {
    int count = 0;
    Reservation* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

Reservation* ReservationManager::findReservation(int reservationID) {
    Reservation* current = head;
	
    while (current != nullptr) {
        if (current->reservationID == reservationID) {
            return current;
        }
        current = current->next;
    }

    bool ReservationManager::loadReservationsFromFile(const std::string& filename,ResourceManager& rm, Waitlist& wl) {
    
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "No existing reservations file found (" << filename << ").\n";
            return false;
        }

        std::string line;
        int loaded = 0;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string resIDStr, studentName, qtyStr;

            std::getline(ss, resIDStr, ',');
            std::getline(ss, studentName, ',');
            std::getline(ss, qtyStr, ',');

            if (resIDStr.empty() || studentName.empty() || qtyStr.empty()) continue;

            int resourceID = std::stoi(resIDStr);
            int quantity = std::stoi(qtyStr);

            createReservation(resourceID, studentName, quantity, rm, wl);
            loaded++;
        }

        file.close();
        std::cout << "Loaded " << loaded << " existing reservation(s) from " << filename << ".\n";
        return true;
    }

    int ReservationManager::countReservationsForResource(int resourceID) const {
        int matches = 0;
        Reservation* current = head;
        while (current != nullptr) {
            if (current->resourceID == resourceID) {
                matches++;
            }
            current = current->next;
        }
        return matches;
    }
    return nullptr;
}