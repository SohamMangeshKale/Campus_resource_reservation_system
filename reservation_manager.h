#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H
 
 
 
#include "structures.h"
#include "resource_manager.h"
#include "waitlist.h"
#include "history_stack.h"
#include <string>
 
 
//idhar problem hai, maybe
class ReservationManager {
private:
    Reservation* head;
    int nextReservationID;
 
 
public:
    ReservationManager();
    ~ReservationManager();
 
    // possible or not
    bool validateRequest(int resourceID, int quantity, ResourceManager& rm) const;
 
    
    // If the resource doesn't have enough availability, the student is added to the waitlist instead
    //  linked list me dalna is done at the head. O(1)
	
    bool createReservation(int resourceID, const std::string& studentName, int quantity, ResourceManager& rm, Waitlist& wl);
 
	//linked list me se id nikal ne ka
    bool cancelReservation(int reservationID, ResourceManager& rm, HistoryStack& hist);
 
    //active wale, O(n)
    void displayActiveReservations() const;
 
    Reservation* findReservation(int reservationID);
 
    int getActiveCount() const;
    bool loadReservationsFromFile(const std::string& filename, ResourceManager& rm, Waitlist& wl);
    int countReservationsForResource(int resourceID) const;
    
    // Expected format per lineis resourceID,studentName,quantity
    // Each line is run through the normal createReservation() flow
    bool loadReservationsFromFile(const std::string& filename, ResourceManager& rm, Waitlist& wl);

    // Counts how many active reservations currently exist 
  // O(n) traversal.
    int countReservationsForResource(int resourceID) const;
};

#endif