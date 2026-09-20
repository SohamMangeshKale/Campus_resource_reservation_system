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
 
    // Attempts to create a reservation.
    // If the resource doesn't have enough availability, the student is added to the waitlist instead
    //  linked list me dalna is done at the head. O(1)
	
    bool createReservation(int resourceID, const std::string& studentName, int quantity, ResourceManager& rm, Waitlist& wl);
 
	//linked list me se id nikal ne ka
    bool cancelReservation(int reservationID, ResourceManager& rm, HistoryStack& hist);
 
    //active wale
    void displayActiveReservations() const;
 
    Reservation* findReservation(int reservationID);
 
    int getActiveCount() const;
};
 
 
#endif