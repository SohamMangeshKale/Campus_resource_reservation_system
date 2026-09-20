#ifndef STRUCTURES_H
#define STRUCTURES_H
 
#include <string>
 
//Both were happy with this
struct Resource {
    int id;
    std::string name;
    int totalUnits;
    int availableUnits;
};
 

struct Reservation {
    int reservationID;
    int resourceID;
    std::string studentName;
    int quantity;
    Reservation* next;
};
 
//ek entry ruki hai, using queue
struct WaitlistEntry {
    int resourceID;
    std::string studentName;
    int quantity;
};


 
#endif
 